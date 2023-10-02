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
	/*      counter for comas      */
	uint8_t Local_u8ComaCounter = 0;
	EN_cardError_t FuncRet;
	if (cards != NULL){
            Local_u8ComaCounter = 0;
		/*        buffer to store user input        */
		char* Local_charBuffer = buffer;
		/*        buffer to store the input Expiry Date      */
		char Local_charBufferExpiry[BUFFER_LENGTH] = {0};
		/*        getting input        */
		//fgets(Local_charBuffer, BUFFER_LENGTH, cards);
		/*        scanning the input string for the expiry date        */
		for(int i = 0; i < strlen(Local_charBuffer); i++){
			/*        copy any chars after the second coma        */
			if(Local_u8ComaCounter == 2){
				strcpy(Local_charBufferExpiry, &Local_charBuffer[i]);
				Local_charBufferExpiry[(strlen(Local_charBufferExpiry)-2)] = '\0';
				break;
			}
			/*        increase the coma counter         */
			if(Local_charBuffer[i] == ',') Local_u8ComaCounter++;
		}
		/*        input length check        */
		if(Local_charBufferExpiry == 0 || strlen(Local_charBufferExpiry) != 5) {
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
    char * bufferLocal = buffer;          /* Uesd to save line from the cards file */
    char panLenghtLocal = 0;                  /* Used as index of PAN array */

    if (cardData != NULL)                     /* Check if the pointer of card data not equal to NULL */
    {
        while (bufferLocal[++loopCounterLocal] != ',') /* the ',' used to split the line , " Name , PAN , Expired date "*/
        {
            //Do Nothing                      /* Get the start of PAN in the buffer */
        }
        while (bufferLocal[++loopCounterLocal] != ',') /* The start of PAN */
        {                                     /* Check if there is no numbers , check if there is no more numbers than the max PAN */
            if (bufferLocal[loopCounterLocal] >= '0' && bufferLocal[loopCounterLocal] <= '9' && panLenghtLocal < MAX_PAN)
            {
                cardData->primaryAccountNumber[panLenghtLocal++] = bufferLocal[loopCounterLocal]; /* Save the PAN in card data array */
                cardData->primaryAccountNumber[panLenghtLocal] = '\0'; /* End of string in the PAN array */
            }
            else if (bufferLocal[loopCounterLocal] == ' ') /* Ignore any space */
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


/*************************************************************************************************************/
/* @FuncName : getCardHolderName Function  @Written by : Mohamed Mansour                                     */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : Takes the the card Holder Name and check it if matches the requires                */
/*                        Stores it into card data                                                           */
/* 2- Function Input                                                                                         */
/*               @param : cardData       @ref ST_cardData_t  struct                                          */
/* 3- Function Return                                                                                        */
/*               @return Error status of the card module                                                     */
/*                (CARD_OK) : The function done successfully                                                 */
/*                (WRONG_NAME) : If the Name less than 20 or more than 24, If not alpha                      */
/*************************************************************************************************************/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
    char* localBuffer;

    #ifndef TEST_CARD_HOLDER_NAME
    unsigned int size = 0;
    fopen_s(&cards, "cards.txt", "r");
    fgets(buffer, BUFFER_LENGTH, cards);
    localBuffer = buffer;
    #endif // TEST_CARD_HOLDER_NAME
    #ifdef TEST_CARD_HOLDER_NAME
    localBuffer = testBuffer;
    #endif
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

    nameSize += spaces;
    if (nameSize >= 20 && nameSize < 25)
    {
        for(int i = 0 ; i < nameSize ; i++)
            cardData->cardHolderName[i] = buffer[i];

        return CARD_OK;
    }
    return WRONG_NAME;


}
