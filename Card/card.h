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

FILE * cards;

typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);
#endif 