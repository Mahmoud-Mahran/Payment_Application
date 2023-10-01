/*************************************************************************************************************/
/*                                              Includes                                                     */
/*************************************************************************************************************/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "card.h"
/*************************************************************************************************************/
/*                                           Define Macros                                                   */
/*************************************************************************************************************/
#ifndef NULL
#define	NULL	            	( (void *)0 )
#endif
#define	CHAR_NULL	              ( '\0' )
#define CARD_DATA_NOK                -1
#define TEST_CARD_HOLDER_NAME         0
#define BUFFER_LENGTH                 200
#define MAX_PAN                       19
#define MIN_PAN                       16
/*###########################################################################################################*/
/*                                             Functions                                                     */
/*###########################################################################################################*/
/*************************************************************************************************************/
/* @FuncName : getCardExpiryDate Function                           @Written by : Mahmoud Mahran             */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : Take the card expiry date and test it for valid formatting(DD/MM)                  */
/* 2- Function Input                                                                                         */
/*               @param : cardData             @ref ST_cardData_t     struct                                 */
/* 3- Function Return                                                                                        */
/*               @return Error status of the card module                                                     */
/*                (WRONG_EXP_DATE) : Expiry date length or format error.                                     */
/*                (CARD_OK) : Expiry date is correctly formatted.                                            */
/*************************************************************************************************************/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{ 
    FILE *cards = fopen("Card\\cards.txt", "r");
	/*      counter for comas      */
	uint8_t Local_u8ComaCounter = 0;
	EN_cardError_t FuncRet = 0;
	if (cards != NULL){
		/*        buffer to store user input        */
		char Local_charBuffer[BUFFER_LENGTH] = {0};
		/*        buffer to store the input Expiry Date      */
		char Local_charBufferExpiry[BUFFER_LENGTH] = {0};
		/*        getting input        */
		fgets(Local_charBuffer, BUFFER_LENGTH, cards);
		/*        scanning the input string for the expiry date        */
		for(int i = 0; i < strlen(Local_charBuffer); i++){
			/*        copy any chars after the second coma        */
			if(Local_u8ComaCounter == 2){
				strcpy(Local_charBufferExpiry, &Local_charBuffer[i]);
				break;
			}
			/*        increase the coma counter         */
			if(Local_charBuffer[i] == ',') Local_u8ComaCounter++;
		}
		/*        input length check        */
		if(Local_charBufferExpiry == 0 || strlen(Local_charBufferExpiry) != 6) {
			/*        return error state        */
			FuncRet =  WRONG_EXP_DATE;
		} else {
			/*        input format check        */
			if(isdigit(Local_charBufferExpiry[0]) == 0 || isdigit(Local_charBufferExpiry[1]) == 0 || isdigit(Local_charBufferExpiry[3]) == 0 || isdigit(Local_charBufferExpiry[4]) == 0){
				/*        return error state        */
				FuncRet =  WRONG_EXP_DATE;
			}
			if(Local_charBufferExpiry[2] != '/'){
				/*        return error state        */
				FuncRet =  WRONG_EXP_DATE;
			}
			if(FuncRet != WRONG_EXP_DATE){
				/*        store input in cardData if all checks are passed safely and return card ok        */
				strcpy(cardData->cardExpirationDate, Local_charBufferExpiry);
				FuncRet =  CARD_OK;
			}
		}
		/*        return final state        */
		return FuncRet;
		/*        close the file        */
	    fclose(cards);
	} else {
		/*        print file opening error        */
		printf("Unable to open file.\n");
	}
}
/*************************************************************************************************************/
/* @FuncName : getCardPAN Function  @Written by : Mohamed Yehia El-Greatly                                   */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : Takes the the card PAN and check it if matches the requires                        */
/*                        Stores it into card data                                                           */
/* 2- Function Input                                                                                         */
/*               @param : cardData       @ref ST_cardData_t  struct                                          */
/* 3- Function Return                                                                                        */
/*               @return Error status of the card module                                                     */
/*                (CARD_OK) : The function done successfully                                                 */
/*                (WRONG_PAN) : If the PAN more less than 16 or more than 19, If not a number                */
/*                (CARD_DATA_NOK) : If the card data pointer point to NULL                                   */
/*************************************************************************************************************/
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
    EN_cardError_t retFunc = CARD_OK;         /* Initialize the function return by the card error state */
    char loopCounterLocal = -1;               /* Initialize the counter used in every loop in this function */
    char bufferLocal[BUFFER_LENGTH];          /* Uesd to save line from the cards file */
    char panLenghtLocal = 0;                  /* Used as index of PAN array */

    if (cardData != NULL)                     /* Check if the pointer of card data not equal to NULL */
    {
        fopen_s(&cards,"cards.txt", "r");     /* To open and read file data , save pointer to this file in cards pointer */
        fgets(bufferLocal, BUFFER_LENGTH, cards); /* Read one line from the file as string and save it in bufferLocal array */
        while (bufferLocal[++loopCounterLocal] != ',') /* the ',' used to split the line , " Name , PAN , Expired date "*/
        { 
            //Do Nothing                      /* Get the start of PAN in the buffer */
        }
        while (bufferLocal[++loopCounterLocal] != ',') /* The start of PAN */
        {                                     /* Check if there is no numbers , check if there is no more numbers than the max PAN */
            if (bufferLocal[loopCounterLocal] >= '0' && bufferLocal[loopCounterLocal] <= '9' && panLenghtLocal < MAX_PAN)
            {
                cardData->primaryAccountNumber[panLenghtLocal++] = bufferLocal[loopCounterLocal]; /* Save the PAN in card data array */
                primaryAccountNumber[panLenghtLocal] = '\0'; /* End of string in the PAN array */
            }
            else if (buffer[loopCounterLocal] == ' ') /* Ignore any space */
            {
                //Do Nothing
            }
            else                              /* Check if any character found or there is numbers more than the max PAN */
            {
                retFunc = WRONG_PAN;          /* Return WRONG_PAN */
                cardData->primaryAccountNumber[0] = '\0'; /* Delete old data */
            }
        }
        if (panLenghtLocal < MIN_PAN )        /* Check if the numbers found in the buffer less than the min PAN */
        {
            retFunc = WRONG_PAN;              /* Return WRONG_PAN */
            cardData->primaryAccountNumber[0] = '\0'; /* Delete old data */
        }
    }
    else 
    {
        retFunc = CARD_DATA_NOK;              /* If the card pointer to data equal to NULL */
    }

    return retFunc;                           /* Return the card error state */
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
    fopen_s(&cards, "cards.txt", "r");
    fgets(buffer, BUFFER_LENGTH, cards);
    //printf("%s", buffer);
    // scanf("%[^\n]s",cardData->cardHolderName);
    //unsigned nameLength = strlen(cardData->cardHolderName);
    int i = 0;
    int nameSize = 0;
    int spaces = 0;
    while (buffer[i] != ',')
    {
        if (isalpha(buffer[i++]))
            nameSize++;
        if (buffer[i] == ' ')
            spaces++;
    }

    //printf("%d \n%d\n", nameSize, spaces);
    nameSize += spaces;
    if (nameSize >= 20 && nameSize < 25)
    {
        strcpy_s(cardData->cardHolderName, nameSize, buffer);
        return CARD_OK;
    }
    return WRONG_NAME;

#endif // TEST_CARD_HOLDER_NAME
}