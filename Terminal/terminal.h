/*###########################################################################################################*/
/* Author :                                 Mohamed Yehia El-Greatly                                         */
/* File Name :                                     terminal.h                                                */
/* Version :                                        V1.0.0                                                   */
/* Date :                                         28 Sep 2023                                                */
/*###########################################################################################################*/
/* @Description  :                                                                                           */
/*                is an interface between the user and the our software application,                         */
/*                 consists of hardware part (KayPad) + software module                                      */
/*                                                                                                           */
/* Terminal main features  :   - Verify the card data and the user inputs.                                   */
/*                             - Ask for the amount and PIN number.                                          */
/*                             - Verify the maximum amount and the PIN number.                               */
/*                             - Send card data and the transaction amount to the bank server.               */
/*###########################################################################################################*/
/* @Features  :                                                                                              */
/*                  -  getTransactionDate()                                                                  */
/*                  -  getTransactionAmount()                                                                */
/*                  -  setMaxAmount()                                                                        */
/*                  -  isCardExpired()                                                                       */
/*                  -  isBelowMaxAmount()                                                                    */
/*                  -  isValidCardPAN()                                                                      */
/*###########################################################################################################*/
/* The Architect Give The APIs  :                                                                            */
/*                   1-  The Name of Function                                                                */
/*                   2-  What is the input                                                                   */
/*                   3-  Return Type  "Error State"                                                          */
/*                   4-  Object Like Macros                                                                  */
/*###########################################################################################################*/

/*************************************************************************************************************/
/*                                  Guard for calling one time in .c files                                   */
/*************************************************************************************************************/

#ifndef TERMINAL_H_
#define TERMINAL_H_
#include "../Card/card.h"
#include <stdint.h>
/*************************************************************************************************************/
/*                                       Define New Data Type                                                */
/*************************************************************************************************************/
typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;
/*************************************************************************************************************/
/*                                       Define New ERROR STATE                                              */
/*************************************************************************************************************/
typedef enum EN_terminalError_t
{
	TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

/*************************************************************************************************************/
/*                                            Define APIs                                                    */
/*************************************************************************************************************/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount);
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData);
/*************************************************************************************************************/
/*                                            The   End                                                      */
/*************************************************************************************************************/
#endif /* TERMINAL_H_ */
/*###########################################################################################################*/
