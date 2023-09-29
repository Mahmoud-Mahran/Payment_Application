/*###########################################################################################################*/
/* Author :                                 Mohamed Yehia El-Greatly                                         */
/* File Name :                                     terminal.c                                                */
/* Version :                                        V1.0.0                                                   */
/* Date :                                         28 Sep 2023                                                */
/*###########################################################################################################*/

/*************************************************************************************************************/
/*                                              Includes                                                     */
/*************************************************************************************************************/
#include "terminal.h"
/*************************************************************************************************************/
/*                                           Define Macros                                                   */
/*************************************************************************************************************/
#define	NULL	            	( (void *)0 )
#define TERMINAL_DATA_NOK            -1
/*************************************************************************************************************/
/* @FuncName : setMaxAmount Function                             @Written by : Mohamed Yehia El-Greatly      */
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
/*************************************************************************************************************/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	EN_terminalError_t retFunc = TERMINAL_OK;     /* Initialize the function return by the terminal error state */
	if (termData != NULL)                         /* Check if the terminal data not equal NULL */
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
		retFunc = TERMINAL_DATA_NOK;              /* If the terminal data pointer equal to NULL */
	}
	return retFunc;                               /* Return the terminal error state */
}/* End of setMaxAmount */