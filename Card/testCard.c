/*###########################################################################################################*/
/* Author :                                 Mohamed Mansour                                                  */
/* File Name :                                     testCard.c                                                */
/* Version :                                        V1.0.0                                                   */
/* Date :                                          1 oct 2023                                                */
/*###########################################################################################################*/

/*************************************************************************************************************/
/*                                              Includes                                                     */
/*************************************************************************************************************/
#include "card.h"
/*************************************************************************************************************/


/*************************************************************************************************************/
/* @FuncName : getCardHolderNameTest Function @Written by : Mohamed Mansour                                  */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : used to test getCardHolderName function, take the input from testNames file        */
/* 2- Function Input                                                                                         */
/*               Void                                                                                        */
/* 3- Function Return                                                                                        */
/*               Void                                                                                        */
/*************************************************************************************************************/

#define NUMBER_OF_TEST_CASES   4

void getCardHolderNameTest(void)
{

    FILE* testFile;                 /*test cases file pointer */
    unsigned int count = 1;         /*test cases counter*/
    FILE*  expectedResultsFile ;    /*Expected results file pointer */
    ST_cardData_t testCard = {"","", ""};
    char expectedResultBuffer[TEST_BUFFER_LENGTH];
    testFile = fopen("test_name.txt", "r");    /*opens testName file */

    expectedResultsFile = fopen("Expected.txt","r"); /*opens Expected results file */
    int i = 0;
    printf("Tester Name : mohamed mansour \nFunction Name: getCardHolderName \n");
    while(i < NUMBER_OF_TEST_CASES)
    {
        i++;

        fgets(expectedResultBuffer, TEST_BUFFER_LENGTH, expectedResultsFile); /* get a line from the Expected result file to be printed*/
        fgets(testBuffer, TEST_BUFFER_LENGTH, testFile);                      /* get a line from the Test file to be checked by getCArdHolderName function*/
        printf("test case : %d \nInput Data:%s Expected Result : %s ",count++,testBuffer,expectedResultBuffer);
        if(getCardHolderName(&testCard) == CARD_OK)       /*call getCardHolderName and check the validation of the name*/
        {

            printf("Actual Result: : CARD_OK \n");
        }
        else
            printf("Actual Result: : WRONG_NAME \n");


    }
    fclose(testFile);                                       /*close testfile*/
    fclose(expectedResultsFile);                            /*close expectedResultsFile*/
}


/*************************************************************************************************************/
/* @FuncName : getCardExpiryDateTest Function @Written by : Mohamed Mansour                                  */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : used to test getCardExpiryDateTest function, take the input from cards file    */
/* 2- Function Input                                                                                         */
/*               Void                                                                                        */
/* 3- Function Return                                                                                        */
/*               Void                                                                                        */
/*************************************************************************************************************/
void getCardExpiryDateTest(void)
{
    FILE* testExpiryDateFile;
    FILE* ecpectedExpiryDateResultsFile;
    ST_cardData_t testCard = {"","",""};
    testExpiryDateFile =  fopen("cards.txt","r");
    cards =testExpiryDateFile ;
    ecpectedExpiryDateResultsFile =  fopen("Expected_ExpiryDate.txt","r");
    char i = 0;
    unsigned char count = 0;
    char loopCounterLocal=0;
    char ecpectedExpiryDateResults[50];
    printf("Tester Name : mohamed mansour\nFunction Name: getCardExpiryDate\n");
    while(i < NUMBER_OF_TEST_CASES + 1 )

    {
        i++;
        fgets(ecpectedExpiryDateResults, TEST_BUFFER_LENGTH, ecpectedExpiryDateResultsFile);
        fgets(buffer, BUFFER_LENGTH, testExpiryDateFile);

        printf("test case : %d\nInput Data:",count++);
        loopCounterLocal = -1;
        while (buffer[++loopCounterLocal] != ',') /* the ',' used to split the line , " Name , PAN , Expired date "*/
        {
            //Do Nothing
        }
        while (buffer[++loopCounterLocal] != ',')
        {
                                                        /* Get the start of Expired date in the buffer */
        }
        while (buffer[++loopCounterLocal] != ',')       /* The start of Expired date */
        {
          printf("%c",buffer[loopCounterLocal]);
        }

        printf("\nExpected Result : %s",ecpectedExpiryDateResults);
        if(getCardExpiryDate(&testCard) == CARD_OK)
        {

            printf("Actual Result: : CARD_OK");
        }
        else
            printf("Actual Result: : WRONG_DATE");
        printf("\n");


    }
}


/*************************************************************************************************************/
/* @FuncName : getCardPANTest Function @Written by : Mohamed Mansour                                         */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : used to test getCardPANTest function, take the input from cards file               */
/* 2- Function Input                                                                                         */
/*               Void                                                                                        */
/* 3- Function Return                                                                                        */
/*               Void                                                                                        */
/*************************************************************************************************************/
void getCardPANTest(void)
{
    FILE* testPanFile;
    FILE* ecpectedPanResultsFile;
    enum EN_cardError_t error ;
    ST_cardData_t testCard = {"","",""};
    testPanFile =  fopen("cards.txt","r");
    ecpectedPanResultsFile =  fopen("Expected_pan.txt","r");
    char i = 0;
    unsigned char count = 0;
    char loopCounterLocal=0;
    char ecpectedPanResults[50];
    printf("Tester Name : mohamed mansour\nFunction Name: getCardPAN\n");
    while(i < NUMBER_OF_TEST_CASES + 1)
    {
        i++;
        fgets(ecpectedPanResults, TEST_BUFFER_LENGTH, ecpectedPanResultsFile);
        fgets(buffer, BUFFER_LENGTH, testPanFile);
        error = getCardPAN(&testCard);
        printf("test case : %d\nInput Data:",count++);
        loopCounterLocal = -1;
        while (buffer[++loopCounterLocal] != ',') /* the ',' used to split the line , " Name , PAN , Expired date "*/
        {
            //Do Nothing                      /* Get the start of PAN in the buffer */
        }
        while (buffer[++loopCounterLocal] != ',') /* The start of PAN */
        {
            printf("%c",buffer[loopCounterLocal]);
        }
        printf("\nExpected Result : %s",ecpectedPanResults);
        if(getCardPAN(&testCard) == CARD_OK)
        {

            printf("Actual Result: : CARD_OK");
        }
        else
            printf("Actual Result: : WRONG_NAME");
        printf("\n");


    }

}
