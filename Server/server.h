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
