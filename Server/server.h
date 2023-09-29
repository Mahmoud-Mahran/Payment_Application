/*************************************************************************************************************/
/* Author :                             Mahmoud Ahmed Mohamed Mahran                                         */
/* Description :                               server.h                                                      */
/*************************************************************************************************************/
/* Version :V1.0.0                                                                                           */
/* Date :     29 Sep 2023                                                                                    */
/*************************************************************************************************************/
/*###########################################################################################################*/
/* @Description  :                                                                                           */
/*   *The server module is the backend of the system that handles the database and processes transactions    */
/*     after making the necessary checks.                                                                    */
/*   *The server also saves all transaction data and it's final state in the database                        */
/*###########################################################################################################*/
/* Server main features : - Verify that the card isn't stolen or invalid by checking the associated account. */
/*                        - Verify that the transaction amount doesn't exceed the current balance.           */
/*                        - Shows the user why the transaction couldn't be processed.                        */
/*                        - Process the transaction if it passed all system checks.                          */
 /*                       - Save transaction data and final state.                                           */
/*                        - Update account balance if the transaction was processed successfully.            */
/*###########################################################################################################*/
/*@Features  :                                                                                               */
/*                  -  recieveTransactionData()                                                              */
/*                  -  isValidAccount()                                                                      */
/*                  -  isBlockedAccount()                                                                    */
/*                  -  isAmountAvailable()                                                                   */
/*                  -  saveTransaction()                                                                     */
/*                  -  listSavedTransactions()                                                               */
/*###########################################################################################################*/
/*************************************************************************************************************/
/*  The Architect Give The APIs                                                                              */
/*                   1-  The Name of Function                                                                */
/*                   2-  What is the input                                                                   */
/*                   3-  Return Type  "Error State"                                                          */
/*                   4-  Object Like Macros                                                                  */
/*************************************************************************************************************/
//////////////////////////////////////////////Header File Guard////////////////////////////////////////////////
#ifndef SERVER_H
#define SERVER_H
/////////////////////////////////////////////Data Types////////////////////////////////////////////////////////


typedef struct ST_transaction_t
{
     ST_cardData_t cardHolderData;
     ST_terminalData_t terminalData;
     EN_transState_t transState;
     uint32_t transactionSequenceNumber;
}ST_transaction;

typedef struct ST_accountsDB_t
{
     float balance;
     EN_accountState_t state;
     uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

typedef enum EN_transState_t
{
     APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transStat_t;

typedef enum EN_accountState_t
{
     RUNNING,
     BLOCKED
}EN_accountState_t;
//////////////////////////////////////////Error States///////////////////////////////////////////////////////


typedef enum EN_serverError_t 
{
     SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t ;

///////////////////////////////////////////Function Prototypes////////////////////////////////////////////////
EN_transState_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
void listSavedTransactions(void);

//////////////////////////////////////End Of File/////////////////////////////////////////////////////////////
#endif