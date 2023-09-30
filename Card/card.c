#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "card.h"
//#define TEST_CARD_HOLDER_NAME
#define bufferLength 200

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
    FILE* cards;
    cards = fopen("cards.txt","r");
    char buffer[bufferLength];
    fgets(buffer,bufferLength,cards);
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