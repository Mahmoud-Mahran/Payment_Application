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
/*************************************************************************************************************/
/* @FuncName : getCardExpiryDate Function                           @Written by : Mahmoud Mahran             */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : Take the card expiry date and test it for valid formatting(DD/MM)                  */
/* 2- Function Input                                                                                         */
/*               @param : cardData             @ref ST_cardData_t     struct                                 */
/* 3- Function Return                                                                                        */
/*               @return Error status of the card module                                                     */
/*                (ACCOUNT_NOT_FOUND) : The PAN doesn't exist.                                               */
/*                (SERVER_OK) : PAN exists in db.                                                            */
/*************************************************************************************************************/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{ 
    FILE *cards = fopen("Card\\card_inputs.txt", "r");
	if (cards != NULL){
		/*        buffer to store user input        */
		char Local_charBuffer[BUFFER_LENGTH] = {0};
		//printf("Enter Card Expiry Date: ");
		for(int i = 0; i < 10; i++){
			/*        getting user input        */
			fgets(Local_charBuffer, bufferLength, cards);
			printf("input: %s\n", Local_charBuffer);
			/*        input length check        */
			if(Local_charBuffer == 0 || strlen(Local_charBuffer) != 6) {
				/*        return error state        */
				return WRONG_EXP_DATE;
			} else {
				/*        input format check        */
				if(isdigit(Local_charBuffer[0]) == 0 || isdigit(Local_charBuffer[1]) == 0 || isdigit(Local_charBuffer[3]) == 0 || isdigit(Local_charBuffer[4]) == 0){
					/*        return error state        */
					return WRONG_EXP_DATE;
				}
				if(Local_charBuffer[2] != '/'){
					/*        return error state        */
					return WRONG_EXP_DATE;
				}
				/*        store input in cardData if all checks are passed safely and return card ok        */
				strcpy(cardData->cardExpirationDate, Local_charBuffer);
				return CARD_OK;
			}
		}
		/*        close the file        */
		fclose(ED_fptr);
	} else {
		/*        print file opening error        */
		printf("Unable to open file.\n");
	}
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