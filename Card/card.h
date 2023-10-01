/*###########################################################################################################*/
/* Author :                                    Mohamed Mansour								        	     */
/* File Name :                                     Card.h											         */
/* Version :                                        V1.0.0                                                   */
/* Date :                                         28 Sep 2023                                                */
/*###########################################################################################################*/
/* @Description  :                                                                                           */
/*                Card id used to get the card data and ensure that there is,                                */
/*                no wrong data entered such name, expired date, pan									     */
/*                                                                                                           */
/* Card main features  :       - Ask for Card data.                                                          */
/*                             - Test the input data.                                                        */
/*                             - Store the input data									                     */
/*###########################################################################################################*/
/*@Features  :                                                                                               */
/*                  -  getCardHolderName()                                                                   */
/*                  -  getCardExpiryDate()                                                                   */
/*                  -  getCardPAN()                                                                          */
/*###########################################################################################################*/
#ifndef CARD_H
#define CARD_H
#include <stdio.h>
#include <stdlib.h>
#define MAX_PAN                       19
#define MIN_PAN                       16
#define BUFFER_LENGTH                 200
#define TEST_BUFFER_LENGTH            50

FILE* cards ;
char buffer[BUFFER_LENGTH];
char testBuffer[50];
typedef struct ST_cardData_t
{
    unsigned char cardHolderName[25];
    unsigned char  primaryAccountNumber[20];
    unsigned char  cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);
#endif
