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
#include <stdint.h>
#include <String.h>
#include "..\Card\card.h"
#include "..\Terminal\terminal.h"
#include "server.h"
/*########################################### Define Macros ################################################*/
#ifndef NULL
#define	NULL	            	( (void *)0 )
#endif
#define BUFFER_LENGTH                200
#define	CHAR_NULL	              ( '\0' )
#define SERVER_DATA_NOK              -1
#define MAX_TRANSACTIONS              4
/*##########################################TRANSACTIONS DB#################################################*/
ST_transaction_t transactionsDB[255] = {0};
static unsigned char limitOfTransaction = MAX_TRANSACTIONS;
static fpos_t db_pos;
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
EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    EN_transState_t FuncRet = 0;
    /*     temp account reference to get the account info in        */
    static ST_accountsDB_t Local_uddtAccountReference = {0.0, -1, " "};
    /*     check that the account exists        */
    if(isValidAccount(&transData->cardHolderData, &Local_uddtAccountReference) != ACCOUNT_NOT_FOUND)
    {
        /*     check that amount is available        */
        if(isBlockedAccount(&Local_uddtAccountReference) != BLOCKED_ACCOUNT)
        {
            /*     check that the account is running        */
            if(isAmountAvailable(&transData->terminalData, &Local_uddtAccountReference) != LOW_BALANCE)
            {
                if(limitOfTransaction > 0)
                {
                    //////update file//////////
                    /*      database file pointer      */
                    FILE *accounts_fptr;
                    /*      open file      */
                    fopen_s(&accounts_fptr, "Server\\accountsDB.txt", "r");
                    //fsetpos(accounts_fptr, &db_pos);
                    /*      buffer to store the line to write to the file      */
                    char Local_charBuffer[BUFFER_LENGTH] = {0};
                    /*      format the line to write to the file      */
                    sprintf_s(Local_charBuffer, 100, "%f,%d,%s", Local_uddtAccountReference.balance, Local_uddtAccountReference.state, Local_uddtAccountReference.primaryAccountNumber);
                    /*      write to  file      */
                    fputs(Local_charBuffer, accounts_fptr);
                    /*         update transaction state       */
                    transData->transState = APPROVED;
                    /*         error state                    */
                    FuncRet = APPROVED;
                    fclose(accounts_fptr);
                }
                else
                {
                    transData->transState =  INTERNAL_SERVER_ERROR;
                    /*         error state                    */
                    FuncRet = INTERNAL_SERVER_ERROR;
                }
            }
            else
            {
                /*         update transaction state       */
                transData->transState = DECLINED_INSUFFECIENT_FUND;
                /*         error state                    */
                FuncRet = DECLINED_INSUFFECIENT_FUND;
            }
        }
        else
        {
            /*         update transaction state       */
            transData->transState = DECLINED_STOLEN_CARD;
            /*         error state                    */
            FuncRet = DECLINED_STOLEN_CARD;
        }
    }
    else
    {
        /*         update transaction state       */
        transData->transState =  FRAUD_CARD;
        /*         error state                    */
        FuncRet = FRAUD_CARD;
    }
    if (saveTransaction(transData) == SAVING_FAILED)
    {
        FuncRet = INTERNAL_SERVER_ERROR;

    }
    if(FuncRet == APPROVED)
    {
        printf("Previous balance:%0.2f\n", Local_uddtAccountReference.balance);
        /*            update balance           */
        Local_uddtAccountReference.balance -= transData->terminalData.transAmount;
        printf("New balance:%.2f\n", Local_uddtAccountReference.balance);
        printf("########################\n\n");
    }
    return FuncRet;
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
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
    ST_accountsDB_t* account = accountRefrence;
    /*      return state      */
    EN_serverError_t FuncRet = SERVER_OK;
    /*      database file pointer      */
    FILE *accounts_fptr;
    /*      open file      */
    fopen_s(&accounts_fptr, "Server\\accountsDB.txt", "r");
    /*      confirm that the file opened successfully      */
    if(accounts_fptr != NULL)
    {
        /*      buffer to store lines from the file      */
        char Local_charBuffer[BUFFER_LENGTH] = {0};
        /*      variable to store pan from file      */
        char Local_charPAN[BUFFER_LENGTH] = {0};
        /*      variable to store state from file      */
        EN_accountState_t Local_charState = 0;
        /*      variable to store balance from file      */
        float Local_floatBalance = 0.0;
        /*      temp buffer used for balance float conversion     */
        char Local_charTempBuff[BUFFER_LENGTH] = {0};
        uint8_t Local_u8ComaCounter;
        /*       loop through the accounts db       */
        int i = 0;
        int k = 0;
        int j = 0;
        for(i = 0; i < 10; i++)
        {
            fgetpos(accounts_fptr, &db_pos);
            /*      read line from file      */
            fgets(Local_charBuffer, BUFFER_LENGTH, accounts_fptr);
            int num = strlen(Local_charBuffer);
            Local_u8ComaCounter = 0;
            /*      loop throgh the line to parse DB vars     */
            for(k= 0; k < num; k++)
            {
                /*      reached 1st coma      */
                if(Local_u8ComaCounter == 1)
                {
                    /*      copy the balance string to a temp buffer      */
                    for(j = 0; j < (k - 1); j++)
                    {
                        Local_charTempBuff[j] = Local_charBuffer[j];
                    }
                    /*     get account state      */
                    Local_charState = Local_charBuffer[k-1] - '0';
                }
                /*      copy PAN      */
                if(Local_charBuffer[k] == '"')
                {
                    strcpy_s(Local_charPAN, BUFFER_LENGTH, &Local_charBuffer[k+1]);
                    /*      remove '"' from end of PAN and replace it with a null char     */
                    Local_charPAN[strlen(Local_charPAN)-2] = '\0';
                    break;
                }
                /*      increase coma counter      */
                if(Local_charBuffer[k] == ',') Local_u8ComaCounter++;
            }
            /*      get the account balance by converting the temp buffer to float      */
            Local_floatBalance = (float)atof(Local_charTempBuff);
            /*       check for a matching pan number      */
            accountRefrence = account;
            if(strcmp(cardData->primaryAccountNumber, Local_charPAN) == 0)
            {
                /*      store account data in the reference if the account was found */
                accountRefrence->balance = Local_floatBalance;
                accountRefrence->state = Local_charState;
                strcpy_s(accountRefrence->primaryAccountNumber, strlen(Local_charPAN)+1, Local_charPAN);
                /*      error state      */
                FuncRet =  SERVER_OK;
                /*        break from the loop if the pan was found in the DB          */
                break;
            }
            else
            {
                accountRefrence = NULL;
                /*      error state      */
                FuncRet =  ACCOUNT_NOT_FOUND;
            }
        }
        fclose(accounts_fptr);
        /*      return error state      */
        return FuncRet;
    }
    else
    {
        printf("Unable to open file.\n");
    }
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
void listSavedTransactions(void)
{
    int i = 0;
    /*      array of state strings to display accoring to the transaction state enum      */
    char Local_charTransStates[5][50] = {"APPROVED", "DECLINED_INSUFFECIENT_FUND", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "INTERNAL_SERVER_ERROR"};
    /*      print all saved (non zero) transactions      */
    while(transactionsDB[i].transactionSequenceNumber != 0)
    {
        printf("#########################\n");
        printf("Transaction Sequence Number: %d\n", transactionsDB[i].transactionSequenceNumber);
        printf("Transaction Date: %s\n", transactionsDB[i].terminalData.transactionDate);
        printf("Transaction Amount: %f\n", transactionsDB[i].terminalData.transAmount);
        printf("Transaction State: %s\n", Local_charTransStates[transactionsDB[i].transState]);
        printf("Terminal Max Amount: %f\n", transactionsDB[i].terminalData.maxTransAmount);
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
/* @FuncName : saveTransaction Function  @Written by : Mohamed Yehia El-Greatly                              */
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
    char indexlocal = MAX_TRANSACTIONS - limitOfTransaction;
    if (transData != NULL)
    {
        if (limitOfTransaction > 0)
        {
            limitOfTransaction--;
            /* Store transaction Sequence Number */
            transactionsDB[indexlocal].transactionSequenceNumber = indexlocal + 1 ;
            /* Store cardHolder Data */
            transactionsDB[indexlocal].cardHolderData = transData->cardHolderData;
            /* Store transaction State */
            transactionsDB[indexlocal].transState = transData->transState;
            /* Store transaction Date */
            transactionsDB[indexlocal].terminalData = transData->terminalData;
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
    listSavedTransactions();
    return retFunc;                             /* Return the server error state */
}
/*************************************************************************************************************/
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
    return accountRefrence->state == RUNNING ? SERVER_OK : BLOCKED_ACCOUNT;
}
