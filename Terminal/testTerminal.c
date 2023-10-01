/*###########################################################################################################*/
/* Author :                                 Mohamed Yehia El-Greatly                                         */
/* File Name :                                     testTerminal.c                                                */
/* Version :                                        V1.0.0                                                   */
/* Date :                                         28 Sep 2023                                                */
/*###########################################################################################################*/

/*************************************************************************************************************/
/*                                              Includes                                                     */
/*************************************************************************************************************/
#include "terminal.h"
#include "..\Card\card.h"
/*************************************************************************************************************/
void getTransactionDateTest(void)
{
	ST_terminalData_t termData = { 0,0,"1/12/2022" };
	printf("Tester Name : Mohamed Yehia \n");
	printf("Function Name : getTransactionDate \n");
	printf("Input Data : ST_terminalData_t termData \n");
	printf("Test Case : old date %s , should update from system time  \n", termData.transactionDate);
	printf("Expected Result : %d ( 0 mean TERMINAL_OK and 1 mean WRONG_DATE ) , because it take the date from system \n", TERMINAL_OK );
	printf("Actual Result : %d  \n", getTransactionDate(&termData));
	printf("New date : %s \n", termData.transactionDate);
}
void isCardExpriedTest(void)
{
	char counterLocal = 0;
	ST_terminalData_t termData = { 0,0,"01/10/2023" };
	ST_cardData_t cardData[4] = { {0,0," "},{0,0,"1/10"},{0,0,"01/10"},{0,0,"02/10"},{0,0,"30/09"} };
	resultsExpected[0] = EXPIRED_CARD; resultsExpected[1] = EXPIRED_CARD; resultsExpected[2] = TERMINAL_OK;
	for (counterLocal = 0; counterLocal < 3; counterLocal++)
	{
		results[counterLocal] = isCardExpired(&cardData[counterLocal], &termData);
		printf("Tester Name : Mohamed Yehia \n");
		printf("Function Name : isCardExpired \n");
		printf("Input Data : ST_cardData_t cardData and ST_terminalData_t termData \n");
		printf("Test Case %d : Terminal date = %s ,Expired date = %s \n", counterLocal + 1, termData.transactionDate, cardData[counterLocal].cardExpirationDate);
		printf("Expected Result : %d ( 0 mean TERMINAL_OK and 2 mean EXPIRED_CARD \n", resultsExpected[counterLocal]);
		printf("Actual Result : %d  \n", results[counterLocal]);
	}
	
}
void getTransactionAmountTest(void)
{
	ST_terminalData_t termData = { 500.0,0,0 };
	EN_terminalError_t result = getTransactionAmount(&termData));
	printf("Tester Name : Mohamed Yehia \n");
	printf("Function Name : getTransactionAmount \n");
	printf("Input Data : ST_terminalData_t termData \n");
	printf("Test Case : old transaction amount %f , should update from user input  \n", termData.transAmount);
	printf("Expected Result : ( 0 mean TERMINAL_OK and 4 mean INVALID_AMOUNT ) , related to user input");
	printf("Actual Result : %d \n", result);
	printf("New date : %s \n", termData.transAmount);

}

void isBelowMaxAmountTest(void)
{
	ST_terminalData_t termData[3];
	EN_terminalError_t results[3];
	EN_terminalError_t resultsExpected[3];
	char counterLocal = 0;

	termData[0].maxTransAmount = 1000.0;termData[0].transAmount = 1000.0;resultsExpected[0] = TERMINAL_OK;
	termData[1].maxTransAmount = 500.0;termData[1].transAmount = 1000.0;resultsExpected[1] = EXCEED_MAX_AMOUNT;
	termData[2].maxTransAmount = 1000.0;termData[2].transAmount = 500.0;resultsExpected[2] = TERMINAL_OK;
	
	for (counterLocal = 0; counterLocal < 3; counterLocal++)
	{
		results[counterLocal] = isBelowMaxAmount(&termData[counterLocal]);
		printf("Tester Name : Mohamed Yehia \n");
		printf("Function Name : isBelowMaxAmountTest \n");
		printf("Input Data : ST_terminalData_t termData \n");
		printf("Test Case %d : maxTransAmount = %f ,transAmount = %f \n",counterLocal+1, termData[counterLocal].maxTransAmount , termData[counterLocal].transAmount);
		printf("Expected Result : %d ( 0 mean TERMINAL_OK and 5 mean EXCEED_MAX_AMOUNT \n", resultsExpected[counterLocal]);
		printf("Actual Result : %d  \n", results[counterLocal]);
	}
}
void setMaxAmountTest(void)
{
	char counterLocal = 0;
	ST_terminalData_t termData[3];
	EN_terminalError_t results[3];
	EN_terminalError_t resultsExpected[3];
	float maxAmount[3] = { 5000.0,-1541.5,0 };
	resultsExpected[0] = TERMINAL_OK; resultsExpected[1] = INVALID_MAX_AMOUNT;resultsExpected[2] = INVALID_MAX_AMOUNT;
	for (counterLocal = 0; counterLocal < 3; counterLocal++)
	{
		results[counterLocal] = setMaxAmount(&termData[counterLocal], maxAmount[counterLocal]);
		printf("Tester Name : Mohamed Yehia \n");
		printf("Function Name : setMaxAmountTest \n");
		printf("Input Data : ST_terminalData_t termData and float maxAmount \n");
		printf("Test Case %d : maxAmount = %f \n", counterLocal + 1, maxAmount[counterLocal]);
		printf("Expected Result : %d ( 0 mean TERMINAL_OK and 6 mean INVALID_MAX_AMOUNT \n", resultsExpected[counterLocal]);
		printf("Actual Result : %d  \n", results[counterLocal]);
	}
}
void isValidCardPANTest(void)
{
	ST_cardData_t cardData[3] = { {0,"01234567891011128",0},
								  {0,"01234567891011129",0},
								  {0,"01234011129",0}};
	EN_terminalError_t results[3];
	EN_terminalError_t resultsExpected[3] = { TERMINAL_OK ,INVALID_CARD ,INVALID_CARD };
	char counterLocal = 0;
	for (counterLocal = 0; counterLocal < 3; counterLocal++)
	{
		results[counterLocal] = isValidCardPAN(&cardData[counterLocal]);
		printf("Tester Name : Mohamed Yehia \n");
		printf("Function Name : isValidCardPAN \n");
		printf("Input Data : ST_cardData_t cardData \n");
		printf("Test Case %d : primaryAccountNumber = %s \n", counterLocal + 1, maxAmount[counterLocal]);
		printf("Expected Result : %d ( 0 mean TERMINAL_OK and 3 mean INVALID_CARD \n", resultsExpected[counterLocal]);
		printf("Actual Result : %d  \n", results[counterLocal]);
	}

}

void main(void)
{
	getTransactionDateTest();
	isCardExpriedTest();
	isBelowMaxAmountTest();
	setMaxAmountTest();
	isValidCardPANTest();
}
=======
    ST_terminalData_t termData=  {
    0.0,
    0.0,
    "22/10/2022"}
    //print
    strcpy_s(termData.transactionDate,10,"22/05/2022");
    getTransactionDate(&termData);
    //print

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
}
