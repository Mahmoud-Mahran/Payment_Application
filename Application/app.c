#include "app.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"


/*************************************************************************************************************/
/* @FuncName : appStart Function @Written by : Mohamed Mansour and Mohamed Yehia El-Greatly                                         */
/*************************************************************************************************************/
/* 1- Function Description                                                                                   */
/*               @brief : used to stert the whole process simulated as the terminal device and server        */
/* 2- Function Input                                                                                         */
/*               Void                                                                                        */
/* 3- Function Return                                                                                        */
/*               Void                                                                                        */
/*************************************************************************************************************/
void appStart()
{
    /*declare card, terminal and server objects*/
    ST_cardData_t card = {"","",""};
    ST_terminalData_t terminal = {0.0,0.0,""};

     ST_cardData_t cardHolderData;
     ST_terminalData_t terminalData;
     EN_transState_t transState;
     uint32_t transactionSequenceNumber;

    ST_transaction_t transaction={card,terminal,0,0};
    EN_transState_t transError = -1 ;
    unsigned char flagProcess = 0;    /*used to start the process if = 1 then start the process*/
    //printf("Enter 1 to Start the Process: ");
    /////////////////////////////////////////////////////////////////////////////////////
    /**Set the Max Amount of the terminal**/
    if(setMaxAmount(&terminal,MAX_AMOUNT)== TERMINAL_OK)
    {
        printf("Maximum Amount of this machine: %d \n\n",MAX_AMOUNT);
    }
    else
    {
        printf("Maximum Amount is not Valid the machine will use the default = 5000.0 \n\n");
    }
    while(1)
    {

        /**Get the card holder Name**/
        if(getCardHolderName(&card) == CARD_OK)
        {
            printf("Card Holder Name: %s , ",card.cardHolderName);
            flagProcess= 1;
        }
        else
        {
            printf("\n Wrong name \n");
            flagProcess = 0;
        }

        /**Get the card Expiry Date**/
        if(getCardExpiryDate(&card) == CARD_OK && flagProcess == 1)
        {
            printf("Card Expired Date: %s , ",card.cardExpirationDate);
            flagProcess = 1;
        }
        else if (flagProcess == 1)
        {
            printf("\n Card is Expired \n");
            flagProcess = 0;
        }

        /**Get the card PAN**/
        if(getCardPAN(&card)== CARD_OK && flagProcess == 1)
        {
            printf("Card PAN: %s\n",card.primaryAccountNumber);
            flagProcess = 1;
        }
        else if (flagProcess == 1)
        {
            printf("\n Card PAN is Wrong \n");
            flagProcess = 0;
        }
        //printf("\n%s\n",card.primaryAccountNumber);
        //printf("\n%d\n",isValidCardPAN(&card));
        /**Check if the Card PAN is Valid**/
        if(isValidCardPAN(&card)== TERMINAL_OK && flagProcess == 1)
        {
            printf("Card PAN has correct Luhn Number\n");
            flagProcess = 1;
        }
        else if (flagProcess == 1)
        {
            printf("\nInvalid Card PAN or has wrong Luhn Number\n");
            flagProcess = 0;
        }

        /**Get the Transaction Date**/
        if(getTransactionDate(&terminal)== TERMINAL_OK && flagProcess == 1)
        {
            printf("Transaction Date: %s \n",terminal.transactionDate);
            flagProcess = 1;
        }
        else if (flagProcess == 1)
        {
            printf("\n Transaction Date is not Valid \n");
            flagProcess = 0;
        }

        /**Check if the card is Expired or not**/
        if(isCardExpired(&card,&terminal)== TERMINAL_OK && flagProcess == 1)
        {
            flagProcess = 1;
        }
        else if (flagProcess == 1)
        {
            printf("\n Card is Expired \n");
            flagProcess = 0;
        }

        /**Get the Transaction Amount**/
        if( flagProcess == 1 && getTransactionAmount(&terminal)== TERMINAL_OK )
        {
            flagProcess = 1;
        }
        else if (flagProcess == 1)
        {
            printf("\n Transaction Amount is not Valid\n");
            flagProcess = 0;
        }


        /**Check if the Amount Excedded the maximum Amount of the terminal**/
        if(isBelowMaxAmount(&terminal)== TERMINAL_OK &&  flagProcess == 1)
        {
            flagProcess = 1;
            transaction.cardHolderData=card;
            transaction.terminalData=terminal;

            transError = recieveTransactionData(&transaction);

        }
        else if (flagProcess == 1)
        {
            printf("\n Maximum Amount Excedded \n");
            flagProcess = 0;
        }

        /**Check if the Account is Valid or Not**/


        if(transError == APPROVED &&  flagProcess == 1)
        {
            flagProcess = 1;
            //listSavedTransactions();
        }
        else if (transError == FRAUD_CARD &&  flagProcess == 1)
        {
            printf("\n Account Does not Exist \n");
            flagProcess = 0;
        }
        else if (transError == DECLINED_INSUFFECIENT_FUND  &&  flagProcess == 1)
        {
            printf("\n Amount is not available \n");
            flagProcess = 0;
        }
        else if (transError == DECLINED_STOLEN_CARD &&  flagProcess == 1)
        {
            printf("\n DECLINED_STOLEN_CARD \n");
            flagProcess = 0;
        }
        else if (transError == INTERNAL_SERVER_ERROR &&  flagProcess == 1 )
        {
            printf("\n  Transaction can't be saved \n");
            flagProcess = 0;
        }
        flagProcess = 0;
        printf("****************End Process**************\n");
        printf("To continue press 1 to stop press 0 : " );
        scanf(" %d",&flagProcess);

        if(flagProcess == 0)
        {
            break;
        }
        printf("\n");
    }
}

/******************************************************///////////////




