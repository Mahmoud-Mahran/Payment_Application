/*###########################################################################################################*/
/* Author :                                     Mahmoud Mahran                                               */
/* File Name :                                    testServer.c                                               */
/* Version :                                        V1.0.0                                                   */
/* Date :                                         1 Oct 2023                                                 */
/*###########################################################################################################*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "server.h"
void recieveTransactionDataTest(void){
	ST_transaction_t transactions[5];
	
	//APPROVED
	strcpy(transactions[0].cardHolderData.cardExpirationDate,  "05/25");
	strcpy(transactions[0].cardHolderData.cardHolderName,  "Mahmoud Ahmed Mohamed");
	strcpy(transactions[0].cardHolderData.primaryAccountNumber,  "5847596847589658");
	transactions[0].terminalData.maxTransAmount = 20000;
	strcpy(transactions[0].terminalData.transactionDate, "16/01/2023");
	transactions[0].terminalData.transAmount = 1500;
	transactions[0].transState = 0;
	transactions[0].transactionSequenceNumber = 69;
	//DECLINED_INSUFFECIENT_FUND
	strcpy(transactions[1].cardHolderData.cardExpirationDate, "05/25");
	strcpy(transactions[1].cardHolderData.cardHolderName,  "Mahmoud Ahmed Mohamed");
	strcpy(transactions[1].cardHolderData.primaryAccountNumber, "5847596847589658");
	transactions[1].terminalData.maxTransAmount = 20000;
	strcpy(transactions[1].terminalData.transactionDate, "16/01/2023");
	transactions[1].terminalData.transAmount = 15000;
	transactions[1].transState = 0;
	transactions[1].transactionSequenceNumber = 69;
	//DECLINED_STOLEN_CARD
	strcpy(transactions[2].cardHolderData.cardExpirationDate, "05/25");
	strcpy(transactions[2].cardHolderData.cardHolderName, "Mahmoud Ahmed Mohamed");
	strcpy(transactions[2].cardHolderData.primaryAccountNumber, "5847596847589658");
	transactions[2].terminalData.maxTransAmount = 20000;
	strcpy(transactions[2].terminalData.transactionDate, "16/01/2023");
	transactions[2].terminalData.transAmount = 1500;
	transactions[2].transState = 0;
	transactions[2].transactionSequenceNumber = 69;
	//FRAUD_CARD 
	strcpy(transactions[3].cardHolderData.cardExpirationDate, "05/25");
	strcpy(transactions[3].cardHolderData.cardHolderName, "Mahmoud Ahmed Mohamed");
	strcpy(transactions[3].cardHolderData.primaryAccountNumber, "5847596847589658");
	transactions[3].terminalData.maxTransAmount = 20000;
	strcpy(transactions[3].terminalData.transactionDate, "16/01/2023");
	transactions[3].terminalData.transAmount = 1500;
	transactions[3].transState = 0;
	transactions[3].transactionSequenceNumber = 69;
	//INTERNAL_SERVER_ERROR
	strcpy(transactions[4].cardHolderData.cardExpirationDate, "05/25");
	strcpy(transactions[4].cardHolderData.cardHolderName, "Mahmoud Ahmed Mohamed");
	strcpy(transactions[4].cardHolderData.primaryAccountNumber, "5847596847589658");
	transactions[4].terminalData.maxTransAmount = 20000;
	strcpy(transactions[4].terminalData.transactionDate, "16/01/2023");
	transactions[4].terminalData.transAmount = 1500;
	transactions[4].transState = 0;
	transactions[4].transactionSequenceNumber = 69;
	char transaction_errors[5][30] = { {"APPROVED"}, {"DECLINED_INSUFFECIENT_FUND"}, {"DECLINED_STOLEN_CARD"}, {"FRAUD_CARD"}, {"INTERNAL_SERVER_ERROR"}};
	for(int i = 0; i < 5; i++){
		printf("Tester Name: Mahmoud Mahran\n");
		printf("Function Name: recieveTransactionData\n");
		printf("Test Case %s:\n", (i+1) );
		printf("Input Data: transaction data\n");
		printf("Expected Result: %s\n", transaction_errors[i]);
		printf("Actual Result: %s\n", transaction_errors[recieveTransactionData(&transactions[i])]);
	}	
}
void isValidAccountTest(void){
	ST_cardData_t testCard1 = { "Mahmoud Ahmed Mohamed", "5847596847589658", "05/29"};
	ST_cardData_t testCard2 = { "Mahmoud Ahmed Mohamed", "1254254786654789", "05/25"};
	ST_accountsDB_t *accReference = NULL;
	
	printf("Tester Name: Mahmoud Mahran\n");
	printf("Function Name: isValidAccount\n");
	printf("Test Case 1:\n");
	printf("Input Data: cardHolderData, accountReference\n");
	printf("Expected Result: SERVER_OK\n" );
	if(isValidAccount(&testCard1, accReference) == SERVER_OK){
		printf("Actual Result: SERVER_OK\n");
	} else if(isValidAccount(&testCard1, accReference) == ACCOUNT_NOT_FOUND) {
		printf("Actual Result: ACCOUNT_NOT_FOUND\n");
	}
		
	printf("Tester Name: Mahmoud Mahran\n");
	printf("Function Name: isValidAccount\n");
	printf("Test Case 2:\n");
	printf("Input Data: cardHolderData, accountReference\n");
	printf("Expected Result: ACCOUNT_NOT_FOUND\n");
	if(isValidAccount(&testCard2, accReference) == SERVER_OK){
		printf("Actual Result: SERVER_OK\n");
	} else if(isValidAccount(&testCard1, accReference) == ACCOUNT_NOT_FOUND) {
		printf("Actual Result: ACCOUNT_NOT_FOUND\n");
	}
}
void isBlockedAccountTest(void){
	ST_accountsDB_t accRefrence1 = {10000.0, RUNNING, "5847596847589658"};
	ST_accountsDB_t accRefrence2 = {10000.0, BLOCKED, "5847596847589658"};
	
	
	printf("Tester Name: Mahmoud Mahran\n");
	printf("Function Name: isBlockedAccount \n");
	printf("Test Case 1:\n");
	printf("Input Data: accountReference\n");
	printf("Expected Result: SERVER_OK\n");
	if(isBlockedAccount(&accRefrence1) == SERVER_OK){
		printf("Actual Result: SERVER_OK\n");
	} else if(isBlockedAccount(&accRefrence1) == BLOCKED_ACCOUNT) {
		printf("Actual Result: BLOCKED_ACCOUNT\n");
	}
		
	printf("Tester Name: Mahmoud Mahran\n");
	printf("Function Name: isValidAccount\n");
	printf("Test Case 2:\n");
	printf("Input Data: accountReference\n");
	printf("Expected Result: SERVER_OK\n");
	if(isBlockedAccount(&accRefrence2) == SERVER_OK){
		printf("Actual Result: SERVER_OK\n");
	} else if(isBlockedAccount(&accRefrence2) == BLOCKED_ACCOUNT) {
		printf("Actual Result: BLOCKED_ACCOUNT\n");
	}
}
void isAmountAvailableTest(void){
	
}
void saveTransactionTest(void);
void listSavedTransactionsTest(void);


void main(void){
	recieveTransactionDataTest();
	isValidAccountTest();
	isBlockedAccountTest();
}








