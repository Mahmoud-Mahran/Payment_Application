#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "card.h"
//#define TEST_CARD_HOLDER_NAME
#define bufferLength 50

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{

}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{

}
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{

    unsigned int size = 0;

#ifdef TEST_CARD_HOLDER_NAME
    FILE* cards;
    char buffer[bufferLength];
    unsigned int count = 1;
    cards = fopen("cards.txt", "r");
    FILE*  expec ;
    expec = fopen("Expected.txt","r");
    char exp[bufferLength];
    printf("Tester Name : mohamed mansour\nFunction Name: getCardHolderName\n");
    while(fgets(buffer, bufferLength, cards))
    {
        unsigned siz = strlen(buffer);
        fgets(exp, bufferLength, expec);
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
#endif

#ifndef TEST_CARD_HOLDER_NAME


    scanf("%[^\n]s",cardData->cardHolderName);
    unsigned nameLength = strlen(cardData->cardHolderName);
    for(int i = 0 ; i < nameLength ; i++)
        if(isalpha(cardData->cardHolderName[i]) )
            size++;
    if(size >= 20 && size < 25)
        return CARD_OK;


#endif // TEST_CARD_HOLDER_NAME
    return WRONG_NAME;
}
