/*###########################################################################################################*/
/* Author :                                     Mahmoud Mahran                                               */
/* File Name :                                     server.c                                                  */
/* Version :                                        V1.0.0                                                   */
/* Date :                                         29 Sep 2023                                                */
/*###########################################################################################################*/

/*************************************************************************************************************/
/*                                              Includes                                                     */
/*************************************************************************************************************/
#include "server.h"
#include "..\Card\card.h"
#include "..\Terminal\terminal.h"
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



