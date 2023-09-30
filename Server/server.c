/*###########################################################################################################*/
/* Author :                                     Mahmoud Mahran                                               */
/* File Name :                                     server.c                                                  */
/* Version :                                        V1.0.0                                                   */
/* Date :                                         29 Sep 2023                                                */
/*###########################################################################################################*/

/*************************************************************************************************************/
/*                                              Includes                                                     */
/*************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "..\Card\card.h"
#include "..\Terminal\terminal.h"
/*############################################ ACCOUNTS DB #################################################*/
#include "accountDB.h"
/*########################################### Define Macros ################################################*/
#define	NULL	            	( (void *)0 )
#define	CHAR_NULL	              ( '\0' )
#define SERVER_DATA_NOK              -1
/*##########################################TRANSACTIONS DB#################################################*/
ST_transaction transactionsDB[255] = {0};
static unsigned char limitOfTransaction = 255;
/*###########################################################################################################*/
/*                                             Functions                                                     */
/*###########################################################################################################*/
/*************************************************************************************************************/
/* @FuncName : recieveTransactionData Function                   @Written by : Mahmoud Mahran                */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : Take all transactions' data, validate the data (details and availability)          */
/*                        & update the database with the new balance.                                        */
/* 2- Function Input                                                                                         */
/*               @param : transData      @ref ST_transaction_t   struct                                      */
/* 3- Function Return                                                                                        */
/*               @return Error status of the server module                                                   */
/*                (APPROVED) : The function completed successfully.                                          */
/*                (INTERNAL_SERVER_ERROR) : Transaction can't be saved.                                      */
/*                (FRAUD_CARD) : the account does not exist.                                                 */
/*                (DECLINED_INSUFFECIENT_FUND) : Amount is not available.                                    */
/*                (DECLINED_STOLEN_CARD) : account blocked.                                                  */
/*************************************************************************************************************/
EN_transState_t recieveTransactionData(ST_transaction_t *transData){
	/*     temp account reference to get the account info in        */
	ST_accountsDB_t Local_uddtAccountReference;
	/*     check that the account exists        */
	if(isValidAccount(&transdata->cardHolderData, &Local_uddtAccountReference) != ACCOUNT_NOT_FOUND){
		/*     check that amount is available        */
		if(isAmountAvailable(&transdata->terminalData, &Local_uddtAccountReference) != LOW_BALANCE){
			/*     check that the account is running        */
			if(isBlockedAccount(&Local_uddtAccountReference) != BLOCKED_ACCOUNT){
				/*     check that the transaction was saved and update balance       */
				if(saveTransaction(transdata) != SAVING_FAILED){
					return APPROVED;
				} else {
					return INTERNAL_SERVER_ERROR
				}
			} else {
				return DECLINED_STOLEN_CARD;
			}
		} else {
			return DECLINED_INSUFFECIENT_FUND;
		}
	} else {
		return FRAUD_CARD;
	}
}
/*************************************************************************************************************/
/* @FuncName : isValidAccount Function                           @Written by : Mahmoud Mahran                */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : Take card data & validate if the account related to this card exists or not.       */
/* 2- Function Input                                                                                         */
/*               @param : cardData             @ref ST_cardData_t     struct                                 */
/*               @param : accountRefrence      @ref ST_accountsDB_t   struct                                 */
/* 3- Function Return                                                                                        */
/*               @return Error status of the server module                                                   */
/*                (ACCOUNT_NOT_FOUND) : The PAN doesn't exist.                                               */
/*                (SERVER_OK) : PAN exists in db.                                                            */
/*************************************************************************************************************/
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence){
	/*       loop through the accounts db       */
	for(int i = 0; i < 255; i++){
		/*       check for a matching pan number      */
		if(strcmp(cardData->primaryAccountNumber, accountDB[i].primaryAccountNumber) == 0){
			/*      store account data in the reference if the account was found */
			accountRefrence->balance = accountDB[i].balance;
			accountRefrence->state = accountDB[i].state;
			accountRefrence->primaryAccountNumber = accountDB[i].primaryAccountNumber;
			return SERVER_OK;
		}
	}
	/*      return error state if the loop finished and the account wasn't found      */
	return ACCOUNT_NOT_FOUND;
}
/*************************************************************************************************************/
/* @FuncName : listSavedTransactions Function                     @Written by : Mahmoud Mahran               */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : prints all transactions found in the transactions DB.                              */
/* 2- Function Input                                                                                         */
/*                      void                                                                                 */
/* 3- Function Return                                                                                        */
/*               @return void                                                                                */
/*************************************************************************************************************/
void listSavedTransactions(void){
	int i = 0;
	/*      array of state strings to display accoring to the transaction state enum      */
	char Local_charTransStates[5][] = {"APPROVED", "DECLINED_INSUFFECIENT_FUND", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "INTERNAL_SERVER_ERROR"};
	/*      print all saved (non zero) transactions      */
	while(transactionsDB[i] != 0){
		printf("#########################\n");
		printf("Transaction Sequence Number: %d\n", transactionsDB[i].transactionSequenceNumber); 
		printf("Transaction Date: %s\n", transactionsDB[i].terminalData.transactionDate);
		printf("Transaction Amount: %f\n", transactionsDB[i].terminalData.transAmount);
		printf("Transaction State: %s\n", Local_charTransStates[transactionsDB[i].transState]);
		printf("Terminal Max Amount: %d\n", transactionsDB[i].terminalData.maxTransAmount);
		printf("Cardholder Name: %s\n", transactionsDB[i].cardHolderData.cardHolderName);
		printf("PAN: %s\n", transactionsDB[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n", transactionsDB[i].cardHolderData.cardExpirationDate);
		printf("#########################\n");
		i++;
	}
}
/*************************************************************************************************************/
/* @FuncName : isAmountAvailable Function  @Written by : Mohamed Yehia El-Greatly                            */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : Takes terminal data and a reference to the account                                 */
/*                        check if the account has a sufficient amount to withdraw or not                    */
/* 2- Function Input                                                                                         */
/*               @param : termData       @ref ST_terminalData_t  struct                                      */
/*               @param : accountRefrence      @ref ST_accountsDB_t    struct                                */
/* 3- Function Return                                                                                        */
/*               @return Error status of the terminal module                                                 */
/*                (SERVER_OK) : The function done successfully                                               */
/*                (LOW_BALANCE) : If the transaction amount greater than the balance                         */
/*                (SERVER_DATA_NOK) : If the server data pointer point to NULL                               */
/*************************************************************************************************************/
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	EN_terminalError_t retFunc = SERVER_OK;     /* Initialize the function return by the server error state */
	if (termData != NULL && accountRefrence != NULL) /* Check if the pointer of account data and terminal data not equal to NULL */
	{
		if (termData->transAmount > accountRefrence->balance) /* Check if the transaction amount greater than the balance or not */
		{
			retFunc = LOW_BALANCE;              /* Return LOW_BALANCE if true */
		}
		else
		{
			//Do nothing                        /* Return SERVER_OK if false */
		}
	}
	else
	{
		retFunc = SERVER_DATA_NOK;              /* Return SERVER_DATA_NOK If the account pointer or terminal pointer equal to NULL */
	} 
	return retFunc;                             /* Return the server error state */
}
/*************************************************************************************************************/
/* @FuncName : saveTransaction Function  @Written by : Mohamed Yehia El-Greatly                            */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : Check if number of transaction exceed the limit machine's transactions             */
/*                        Update the account balanceand store all transaction data(Any type of transaction)  */
/* 2- Function Input                                                                                         */
/*               @param : termData       @ref ST_terminalData_t  struct                                      */
/*               @param : accountRefrence      @ref ST_accountsDB_t    struct                                */
/* 3- Function Return                                                                                        */
/*               @return Error status of the terminal module                                                 */
/*                (SERVER_OK) : The function done successfully                                               */
/*                (SAVING_FAILED) : If number of transaction exceed the limit machine transaction            */
/*                (SERVER_DATA_NOK) : If the server data pointer point to NULL                               */
/*************************************************************************************************************/
EN_serverError_t saveTransaction(ST_transaction_t * transData)
{
	EN_terminalError_t retFunc = SERVER_OK;     /* Initialize the function return by the server error state */
	if (transData != NULL)
	{
		if (limitOfTransaction > 0)
		{
			limitOfTransaction--;
			
			if (transData->transState == APPROVED)
			{
				/* Update the account balance */
				/* account balance - transData->terminalData->transAmount */
			}
			/* Store transactionSequenceNumber */
			transData->transactionSequenceNumber; 
			/* Store transState */
			transData->transState;
			/* Store transactionDate */
			transData->terminalData->transactionDate[];
		}
		else
		{
			retFunc = SAVING_FAILED;
		}
	}
	else
	{
		retFunc = SERVER_DATA_NOK;
	}
	return retFunc;                             /* Return the server error state */
}