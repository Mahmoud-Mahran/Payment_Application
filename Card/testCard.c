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
void getCardHolderNameTest(void)
{
#define TEST_CARD_HOLDER_NAME
    FILE* testFile;
    unsigned int count = 1;
    FILE*  expectedResultsFile ;
    ST_cardData_t testCard = {"","", ""};
    char expectedResultBuffer[TEST_BUFFER_LENGTH];
    fopen_s(&testFile, "test_name.txt", "r");
    fopen_s(&expectedResultsFile, "Expected.txt","r");
    int i = 0;
    printf("Tester Name : mohamed mansour\nFunction Name: getCardHolderName\n");
    while(i < 3)
    {
        i++;
        //unsigned siz = strlen(buffer);
        fgets(expectedResultBuffer, TEST_BUFFER_LENGTH, expectedResultsFile);
        // printf("expected: %s\n",expectedResultBuffer);
        fgets(testBuffer, TEST_BUFFER_LENGTH, testFile);
        //   printf("****%s***\n",testBuffer);
        printf("test case : %d\nInput Data:%s\nExpected Result : %s",count++,testBuffer,expectedResultBuffer);
        //printf("\n");
        if(getCardHolderName(&testCard) == CARD_OK)
        {

            printf("Actual Result: : CARD_OK");
        }
        else
            printf("Actual Result: : WRONG_NAME");
        printf("\n");


    }
    fclose(testFile);
    fclose(expectedResultsFile);
}
void getCardExpiryDateTest(void)
{
    FILE* testExpiryDateFile;
    FILE* ecpectedExpiryDateResultsFile;
    ST_cardData_t testCard = {"","",""};
    fopen_s(&testExpiryDateFile, "cards.txt","r");
    cards = testExpiryDateFile ;
    fopen_s(&ecpectedExpiryDateResultsFile, "Expected_ExpiryDate.txt","r");
    char i = 0;
    unsigned char count = 0;
    char loopCounterLocal=0;
    char ecpectedExpiryDateResults[50];
    printf("Tester Name : mohamed mansour\nFunction Name: getCardExpiryDate\n");
    while(i < 5)
    {
        i++;
        //unsigned siz = strlen(buffer);
        fgets(ecpectedExpiryDateResults, TEST_BUFFER_LENGTH, ecpectedExpiryDateResultsFile);
        // printf("expected: %s\n",expectedResultBuffer);
        fgets(buffer, BUFFER_LENGTH, testExpiryDateFile);

        //   printf("****%s***\n",testBuffer);
        printf("test case : %d\nInput Data:",count++);
        loopCounterLocal = -1;
        while (buffer[++loopCounterLocal] != ',') /* the ',' used to split the line , " Name , PAN , Expired date "*/
        {
            //Do Nothing                      /* Get the start of PAN in the buffer */
        }
        while (buffer[++loopCounterLocal] != ',') /* The start of PAN */
        {

        }
        while (buffer[++loopCounterLocal] != ',')
        {
          printf("%c",buffer[loopCounterLocal]);
        }

        printf("\nExpected Result : %s",ecpectedExpiryDateResults);
        //printf("\n");
        if(getCardExpiryDate(&testCard) == CARD_OK)
        {

            printf("Actual Result: : CARD_OK");
        }
        else
            printf("Actual Result: : WRONG_DATE");
        printf("\n");


    }
}
void getCardPANTest(void)
{
    FILE* testPanFile;
    FILE* ecpectedPanResultsFile;
    enum EN_cardError_t error ;
    ST_cardData_t testCard = {"","",""};
    fopen_s(&testPanFile, "cards.txt", "r");
    fopen_s(&ecpectedPanResultsFile, "Expected_pan.txt","r");
    char i = 0;
    unsigned char count = 0;
    char loopCounterLocal=0;
    char ecpectedPanResults[50];
    printf("Tester Name : mohamed mansour\nFunction Name: getCardPAN\n");
    while(i < 5)
    {
        i++;
        //unsigned siz = strlen(buffer);
        fgets(ecpectedPanResults, TEST_BUFFER_LENGTH, ecpectedPanResultsFile);
        // printf("expected: %s\n",expectedResultBuffer);
        fgets(buffer, BUFFER_LENGTH, testPanFile);
        error = getCardPAN(&testCard);
        //   printf("****%s***\n",testBuffer);
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
        //printf("\n");
        if(getCardPAN(&testCard) == CARD_OK)
        {

            printf("Actual Result: : CARD_OK");
        }
        else
            printf("Actual Result: : WRONG_NAME");
        printf("\n");


    }

}
