/*###########################################################################################################*/
/* Author :                                 Mohamed Yehia El-Greatly                                         */
/* File Name :                                     terminal.c                                                */
/* Version :                                        V1.0.0                                                   */
/* Date :                                         28 Sep 2023                                                */
/*###########################################################################################################*/

/*************************************************************************************************************/
/*                                              Includes                                                     */
/*************************************************************************************************************/
#include <stdint.h>
#include "terminal.h"
#include "..\Card\card.h"
/*************************************************************************************************************/
/*                                           Define Macros                                                   */
/*************************************************************************************************************/
#ifndef NULL
#define	NULL	            	( (void *)0 )
#endif
#define	CHAR_NULL	              ( '\0' )
#define TERMINAL_DATA_NOK            -1
#define BUFFER_LENGTH                200
/*###########################################################################################################*/
/*                                             Functions                                                     */
/*###########################################################################################################*/
/*************************************************************************************************************/
/* @FuncName : setMaxAmount Function  @Written by : Mohamed Yehia El-Greatly                                 */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : Takes the maximum allowed amount (Transaction max amount is a float number)        */
/*                        Stores it into terminal data                                                       */
/* 2- Function Input                                                                                         */
/*               @param : termData       @ref ST_terminalData_t  struct                                      */
/*               @param : maxAmount      @ref float                                                          */
/* 3- Function Return                                                                                        */
/*               @return Error status of the terminal module                                                 */
/*                (TERMINAL_OK) : The function done successfully                                             */
/*                (INVALID_MAX_AMOUNT) : if the max amount less than (negative number) or equal to 0         */
/*                (TERMINAL_DATA_NOK) : If the terminal data pointer point to NULL                           */
/*************************************************************************************************************/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	EN_terminalError_t retFunc = TERMINAL_OK;     /* Initialize the function return by the terminal error state */
	if (termData != NULL)                         /* Check if the pointer of terminal data not equal to NULL */
	{
		if (maxAmount > 0)                        /* Check if the max amount not qual negative or zero number */
		{
			termData->maxTransAmount = maxAmount; /* Store the max amount of the terminal */
			
		}
		else
		{
			retFunc = INVALID_MAX_AMOUNT;         /* If the max amount less or equal to 0 */
		}
    }
	else
	{
		retFunc = TERMINAL_DATA_NOK;              /* If the terminal pointer to data equal to NULL */
	}
	return retFunc;                               /* Return the terminal error state */
}/* End of setMaxAmount */
/*************************************************************************************************************/
/* @FuncName : getTransactionAmount Function                        @Written by : Mahmoud Mahran             */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : -Get transaction amount and saves it into terminal data.                           */
/*                        -Validates entered amount and returns arror state.                                 */
/* 2- Function Input                                                                                         */
/*               @param : termData             @ref ST_terminalData_t     struct                             */
/* 3- Function Return                                                                                        */
/*               @return Error status of the terminal module                                                 */
/*                (INVALID_AMOUNT) : Amount is less than or equal to 0.                                      */
/*                (TERMINAL_OK) : Amount entered is valid.                                                   */
/*************************************************************************************************************/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData){
	/*       error state      */
	EN_terminalError_t FuncRet = 0;
	/*      file pointer      */
	FILE *term_fptr;
	/*        open file    */
	term_fptr = fopen("Terminal\\placeHolder.txt", "r");
	/*     check that the file opened successfully     */
	if(term_fptr != NULL){
		/*     buffer to store input from file      */
		char Local_charBuffer[BUFFER_LENGTH] = {0};
		/*     the input transaction amount         */
		int32_t Local_u32TransAmount = 0;
		/*         get input from file              */
		fgets(Local_charBuffer, BUFFER_LENGTH, term_fptr);
		/*         convert to integer               */
		Local_u32TransAmount = atoi(Local_charBuffer);
		/*     check that the amount is valid       */
		if(Local_u32TransAmount <= 0 ){
			/*   error state   */
			FuncRet = INVALID_AMOUNT;
		} else {
			termData->transAmount = (float)Local_u32TransAmount;
			/*   error state   */
			FuncRet = TERMINAL_OK;
		}
		/*     close the file   */
		fclose(term_fptr);
	} else {
		printf("Unable to open terminal input file.\n");
	}
	return FuncRet;
}
/*************************************************************************************************************/
/* @FuncName : isBelowMaxAmount Function                            @Written by : Mahmoud Mahran             */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : Compares the transaction amount with the terminal max allowed amount.              */
/* 2- Function Input                                                                                         */
/*               @param : termData             @ref ST_terminalData_t     struct                             */
/* 3- Function Return                                                                                        */
/*               @return Error status of the terminal module                                                 */
/*                (EXCEED_MAX_AMOUNT) : Amount is larger than the terminal max allowed amount.               */
/*                (TERMINAL_OK) : Amount is below max amount.                                                */
/*************************************************************************************************************/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData){
	EN_terminalError_t FuncRet = 0;
	/*     check that the amount is below max amount       */
	if(termData->transAmount <= termData->maxTransAmount ){
		/*   error state   */
		FuncRet = EXCEED_MAX_AMOUNT;
	} else {
		/*   error state   */
		FuncRet = TERMINAL_OK;
	}
	return FuncRet;
}

/*************************************************************************************************************/
/* @FuncName : isValidCardPAN Function @Written by : Mohamed Yehia El-Greatly                                */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : Check if the PAN is a Luhn number or not.                                          */
/* 2- Function Input                                                                                         */
/*               @param : cardData       @ref ST_cardData_t  struct                                          */
/* 3- Function Return                                                                                        */
/*               @return Error status of the terminal module                                                 */
/*                (TERMINAL_OK) : The function done successfully                                             */
/*                (INVALID_MAX_AMOUNT) : if the max amount less than (negative number) or equal to 0         */
/*                (TERMINAL_DATA_NOK) : If the terminal data pointer point to NULL                           */
/*************************************************************************************************************/
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	EN_terminalError_t retFunc = TERMINAL_OK;     /* Initialize the function return by the terminal error state */
	char loopCounterLocal = 0;                    /* Initialize the counter used in every loop in this function */
	char LuhnNumberLocal = 0;                     /* Used to save the Luhn Number of the origin PAN */
	char tempLocal = 0;                           /* Used to save the result of multibly by 2*/
	char sumLocal = 0;                            /* Used in Luhn algorithm and saving the final result */
	if (cardData != NULL)                         /* Check if the pointer of card data not equal to NULL */
	{
		while (cardData->primaryAccountNumber[loopCounterLocal] != CHAR_NULL) /* This loop to count the number of PAN */
		{
			loopCounterLocal++;
			if (loopCounterLocal == MAX_PAN+1)    /* Check if this string doesn't have NULL character */
			{
				break;                            /* Break to prevent the infinity loop */
			}
			else
			{
				/* Do Nothing*/                   /* Normal count ( less than or equal the max PAN )*/
			}
		}
		if (loopCounterLocal >= MIN_PAN && loopCounterLocal <= MAX_PAN) /* PAN range between 16 & 19 numbers */
		{
			LuhnNumberLocal = cardData->primaryAccountNumber[loopCounterLocal - 1]; /* Save the given Luhn number */
			loopCounterLocal -= 2;                /* Start the Luhn algorithm from the next digit to the luhn number */
			while (loopCounterLocal >= 0)         /* Loop fron the right side to the left side so at the end the counter will be negative */
			{
				tempLocal = cardData->primaryAccountNumber[loopCounterLocal] * 2; /* The first digit next the given Luhn digit is the even digit (every even digit multibly by 2)*/
				if (tempLocal >= 10)              /* After multibly by 2 if the result more than or equal to 10 */
				{
					tempLocal = 1 + (tempLocal % 10); /* Add the digit 1 + the next digit */
				}
				else
				{
					/* Do Nothing*/               /* Numbers from 0 to 4 multibly by 2 */
				}
				sumLocal = sumLocal + tempLocal;  /* Add the result to the old and save it for the next digits */
				if ( (loopCounterLocal-1) >= 0)   /* The next digit to the even one is odd, Check if the loop counter still positive */
				{
					loopCounterLocal--;           /* Move to the odd digit */
					sumLocal = sumLocal + cardData->primaryAccountNumber[loopCounterLocal]; /* Add the odd to the past result */
					loopCounterLocal--;           /* Move to the next */
				}
				else
				{
					loopCounterLocal --;          /* If the loop counter equal to zero that's mean the end */
				}
			}
			sumLocal = 10 - (sumLocal % 10);      /* The final step to calculate the Luhn number is to subtract the mod by 10 of the summation by 10 */
			if (LuhnNumberLocal == sumLocal)      /* Check if the givien Luhn number is equal to the calculated one */
			{
				retFunc = TERMINAL_OK;            /* Return TERMINAL_OK if true */
			}
			else
			{
				retFunc = INVALID_CARD;           /* Return INVALID_CARD if false */
			}
		}
		else
		{
			retFunc = INVALID_CARD;               /* Return INVALID_CARD if the PAN less than 16 or more than 19 number */   
		}
	}
	else
	{
		retFunc = TERMINAL_DATA_NOK;              /* If the card pointer to data equal to NULL */
	}
	return retFunc;                               /* Return the terminal error state */
}/* End of isValidCardPAN */



EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{

#ifdef TEST_getTransactionDate
    uint8_t count = 0;
    FILE* transDate;
    uint8_t buffer[BUFFER_LENGTH];
    uint8_t expectedResult[BUFFER_LENGTH];
    fopen_s(&transDate,"transdates.txt", "r");
    FILE*  transDateEcpecRes ;
    transDateEcpecRes = fopen("Expected.txt","r");
    unsigned char validDate = 1;
    printf("Tester Name : mohamed mansour\nFunction Name: getTransactionDate\n");
    while(fgets(buffer, BUFFER_LENGTH, transDate))
    {
        unsigned siz = strlen(buffer);
        fgets(expectedResult, BUFFER_LENGTH, transDateEcpecRes);
        printf("test case : %d\nInput Data:%s\nExpected Result : %s",count++,buffer,expectedResult);
        printf("\n");
        for(int i = 0 ; i < siz;i++)
        {
            //2/5
            if(i == 2 || i == 5)
               continue;
            if(!isdigit(buffer[i]))
                 validDate = 0;

        }
        if(validDate)
            printf("Actual Result: : TERMINAL_OK");
        else

            printf("Actual Result: : WRONG_DATE ");



        printf("\n");


    }
      printf("finished\n");
    fclose(transDate);
    fclose(transDateEcpecRes);

#endif
#ifndef TEST_getTransactionDate
    time_t t = time(NULL);
    struct tm tm;
    localtime_s(&tm,&t);
    int year = tm.tm_year + 1900;
    int month = tm.tm_mon + 1;
    int day = tm.tm_mday;
    unsigned int index = 9;
    while(year )
    {
        termData->transactionDate[index--] = year%10 + '0';
        year /= 10;
    }

    //termData->transactionDate[index--] =  '0';
    index = 5;
    termData->transactionDate[index--] = '/';
    while(month)
    {
        termData->transactionDate[index--] = month%10 + '0';
        month /= 10;
    }

    index = 2;
    termData->transactionDate[index--] = '/';
    while(day)
    {
        termData->transactionDate[index--] = day%10 + '0';
        day /= 10;
    }

#endif
return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
    time_t t = time(NULL);
    struct tm tm;
    localtime_s(&tm,&t);
    int transYear = tm.tm_year + 1900;
    int transMonth = tm.tm_mon + 1;
    int cardMonth = (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0');
    int cardYear  = (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');
    if(((transMonth <= cardMonth) && (transYear <= cardYear)) || (transYear < cardYear))
        return TERMINAL_OK;
    return EXPIRED_CARD;

}
