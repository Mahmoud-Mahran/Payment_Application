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
/*************************************************************************************************************/
void getTransactionDateTest(void)
{
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
