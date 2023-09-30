/*************************************************************************************************************/
/*                                              Includes                                                     */
/*************************************************************************************************************/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "card.h"
/*************************************************************************************************************/
/*                                           Define Macros                                                   */
/*************************************************************************************************************/
#define	NULL	            	( (void *)0 )
#define	CHAR_NULL	              ( '\0' )
#define CARD_DATA_NOK                -1
#define TEST_CARD_HOLDER_NAME         0
#define BUFFER_LENGTH                 200
#define MAX_PAN                       19
#define MIN_PAN                       16
/*###########################################################################################################*/
/*                                             Functions                                                     */
/*###########################################################################################################*/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{

}
/*************************************************************************************************************/
/* @FuncName : getCardPAN Function  @Written by : Mohamed Yehia El-Greatly                                   */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : Takes the maximum allowed amount (Transaction max amount is a float number)        */
/*                        Stores it into terminal data                                                       */
/* 2- Function Input                                                                                         */
/*               @param : cardData       @ref ST_cardData_t  struct                                          */
/* 3- Function Return                                                                                        */
/*               @return Error status of the terminal module                                                 */
/*                (CARD_OK) : The function done successfully                                                 */
/*                (WRONG_PAN) : If the PAN more less than 16 or more than 19, If not a number                */
/*                (CARD_DATA_NOK) : If the card data pointer point to NULL                                   */
/*************************************************************************************************************/
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
    EN_cardError_t retFunc = CARD_OK;         /* Initialize the function return by the card error state */
    char loopCounterLocal = -1;                   /* Initialize the counter used in every loop in this function */
    char bufferLocal[BUFFER_LENGTH];
    char panLenghtLocal = 0;
    if (cardData != NULL)
    {
        fopen_s(&cards,"cards.txt", "r");
        fgets(bufferLocal, BUFFER_LENGTH, cards);
        while (bufferLocal[++loopCounterLocal] != ',')
        { 
            //Do Nothing
        }
        while (bufferLocal[++loopCounterLocal] != ',')
        {
            if (bufferLocal[loopCounterLocal] >= '0' && bufferLocal[loopCounterLocal] <= '9' && panLenghtLocal < MAX_PAN)
            {
                cardData->primaryAccountNumber[panLenghtLocal++] = bufferLocal[loopCounterLocal];
                if (panLenghtLocal == MAX_PAN)
                {
                    primaryAccountNumber[panLenghtLocal] = '\0';
                }
                else
                {
                    //Do Nothing
                }
            }
            else if (buffer[loopCounterLocal] == ' ')
            {
                //Do Nothing
            }
            else
            {
                retFunc = WRONG_PAN;
            }
        }
    }
    else
    {
        retFunc = CARD_DATA_NOK;
    }
}
/*************************************************************************************************************/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{

    unsigned int size = 0;

#if TEST_CARD_HOLDER_NAME      ==       1
    FILE* cards;
    char buffer[BUFFER_LENGTH];
    unsigned int count = 1;
    cards = fopen("cards.txt", "r");
    FILE*  expec ;
    expec = fopen("Expected.txt","r");
    char exp[BUFFER_LENGTH];
    printf("Tester Name : mohamed mansour\nFunction Name: getCardHolderName\n");
    while(fgets(buffer, BUFFER_LENGTH, cards))
    {
        unsigned siz = strlen(buffer);
        fgets(exp, BUFFER_LENGTH, expec);
        printf("test case : %d\nInput Data:%s\nExpected Result : %s",count++,buffer,exp);
        printf("\n");
        if(siz >=20 && siz < 25)
        {

            printf("Actual Result: : CARD_OK");
        }
        else
            printf("Actual Result: : WRONG_NAME");
        printf("\n");
        fclose(cards);

    }

#elif TEST_CARD_HOLDER_NAME    ==     0
    FILE* cards;
    cards = fopen("cards.txt","r");
    char buffer[BUFFER_LENGTH];
    fgets(buffer, BUFFER_LENGTH,cards);
    // scanf("%[^\n]s",cardData->cardHolderName);
    //unsigned nameLength = strlen(cardData->cardHolderName);
    int i = 0;
    int count = 0 ;
    while(buffer[i++] != ',')
    {
        if(!isalpha(buffer[i]) && buffer[i] != ' ')
            return WRONG_NAME;
        else
            count++;
    }

    if(count >= 20 && count <25)
    {
        int i = 0;
        while(count >= 0)
        {
            cardData->cardHolderName[i] = buffer[i];
            count--;
        }
        return CARD_OK;

    }
    return WRONG_NAME;

#endif // TEST_CARD_HOLDER_NAME
}