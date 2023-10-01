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
    testFile = fopen("test_name.txt", "r");
    expectedResultsFile = fopen("Expected.txt","r");
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
void getCardExpiryDateTest(void) {}
void getCardPANTest(void) {}
