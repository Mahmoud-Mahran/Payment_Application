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
	ST_transaction_t transactions[5] = { 0 };
	//APPROVED
	strcpy_s(transactions[0].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[0].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[0].cardHolderData.primaryAccountNumber, 20,  "6821541302248965");
	transactions[0].terminalData.maxTransAmount = 20000.0;
	strcpy_s(transactions[0].terminalData.transactionDate, 11, "02/10/2023");
	transactions[0].terminalData.transAmount = 100.0;
	transactions[0].transState = 0;
	transactions[0].transactionSequenceNumber = 5;
	//DECLINED_INSUFFECIENT_FUND
	strcpy_s(transactions[1].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[1].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[1].cardHolderData.primaryAccountNumber, 20, "9293770170676345");
	transactions[1].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[1].terminalData.transactionDate, 11, "16/01/2023");
	transactions[1].terminalData.transAmount = 15000.0;
	transactions[1].transState = 0;
	transactions[1].transactionSequenceNumber = 6;
	//DECLINED_STOLEN_CARD
	strcpy_s(transactions[2].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[2].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[2].cardHolderData.primaryAccountNumber, 20, "4001060271215928");
	transactions[2].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[2].terminalData.transactionDate, 11, "16/01/2023");
	transactions[2].terminalData.transAmount = 1500.0;
	transactions[2].transState = 0;
	transactions[2].transactionSequenceNumber = 7;
	//FRAUD_CARD
	strcpy_s(transactions[3].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[3].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[3].cardHolderData.primaryAccountNumber, 20, "5847596847589658");
	transactions[3].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[3].terminalData.transactionDate, 11, "16/01/2023");
	transactions[3].terminalData.transAmount = 1500.0;
	transactions[3].transState = 0;
	transactions[3].transactionSequenceNumber = 8;
	//INTERNAL_SERVER_ERROR
	strcpy_s(transactions[4].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[4].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[4].cardHolderData.primaryAccountNumber, 20, "5847596847589658");
	transactions[4].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[4].terminalData.transactionDate, 11, "16/01/2023");
	transactions[4].terminalData.transAmount = 1500.0;
	transactions[4].transState = 0;
	transactions[4].transactionSequenceNumber = 256;
	char transaction_errors[5][30] = { {"APPROVED"}, {"DECLINED_INSUFFECIENT_FUND"}, {"DECLINED_STOLEN_CARD"}, {"FRAUD_CARD"}, {"INTERNAL_SERVER_ERROR"}};
	for(int i = 0; i < 5; i++){
		printf("\##########################\n");
		printf("Tester Name: Mahmoud Mahran\n");
		printf("Function Name: recieveTransactionData\n");
		printf("Test Case %d:\n", (i+1) );
		printf("Input Data: transaction data\n");
		printf("Expected Result: %s\n", transaction_errors[i]);
		printf("Actual Result: %s\n", transaction_errors[recieveTransactionData(&transactions[i])]);
		printf("\##########################\n");
	}
}
void isValidAccountTest(void){
	ST_cardData_t testCard1 = { "Mahmoud Ahmed Mohamed", "6821541302248965", "05/29"};
	ST_cardData_t testCard2 = { "Mahmoud Ahmed Mohamed", "5847596847589658", "05/25"};
	ST_accountsDB_t accReference;
	printf("\##########################\n");
	printf("Tester Name: Mahmoud Mahran\n");
	printf("Function Name: isValidAccount\n");
	printf("Test Case 1:\n");
	printf("Input Data: cardHolderData, accountReference\n");
	printf("Expected Result: SERVER_OK\n" );
	if(isValidAccount(&testCard1, &accReference) == SERVER_OK){
		printf("Actual Result: SERVER_OK\n");
	} else if(isValidAccount(&testCard1, &accReference) == ACCOUNT_NOT_FOUND) {
		printf("Actual Result: ACCOUNT_NOT_FOUND\n");
	}
	printf("\##########################\n");
	printf("Tester Name: Mahmoud Mahran\n");
	printf("Function Name: isValidAccount\n");
	printf("Test Case 2:\n");
	printf("Input Data: cardHolderData, accountReference\n");
	printf("Expected Result: ACCOUNT_NOT_FOUND\n");
	if(isValidAccount(&testCard2, &accReference) == SERVER_OK){
		printf("Actual Result: SERVER_OK\n");
	} else if(isValidAccount(&testCard2, &accReference) == ACCOUNT_NOT_FOUND) {
		printf("Actual Result: ACCOUNT_NOT_FOUND\n");
	}
	printf("\##########################\n");
}
void isBlockedAccountTest(void){
	ST_accountsDB_t accRefrence1 = {10000.0, RUNNING, "5847596847589658"};
	ST_accountsDB_t accRefrence2 = {10000.0, BLOCKED, "5847596847589658"};

	printf("\##########################\n");
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
	printf("\##########################\n");
	printf("Tester Name: Mahmoud Mahran\n");
	printf("Function Name: isBlockedAccount\n");
	printf("Test Case 2:\n");
	printf("Input Data: accountReference\n");
	printf("Expected Result: BLOCKED_ACCOUNT\n");
	if(isBlockedAccount(&accRefrence2) == SERVER_OK){
		printf("Actual Result: SERVER_OK\n");
	} else if(isBlockedAccount(&accRefrence2) == BLOCKED_ACCOUNT) {
		printf("Actual Result: BLOCKED_ACCOUNT\n");
	}
	printf("\##########################\n");
}
void isAmountAvailableTest(void){
	ST_terminalData_t testTerm1 = { 500.0, 4000.0, "02/10/2023" };
	ST_terminalData_t testTerm2 = { 2000.0, 4000.0, "02/10/2023" };
	ST_accountsDB_t accReference1 = { 5000.0, 1, "5847596847589658" };
	ST_accountsDB_t accReference2 = { 1000.0, 1, "5847596847589658" };
	printf("\##########################\n");
	printf("Tester Name: Mahmoud Mahran\n");
	printf("Function Name: isAmountAvailable \n");
	printf("Test Case 1:\n");
	printf("Input Data: termData, accountRefrence\n");
	printf("Expected Result: SERVER_OK\n");
	if (isAmountAvailable(&testTerm1, &accReference1) == LOW_BALANCE) {
		printf("Actual Result: LOW_BALANCE\n");
	}
	else if (isAmountAvailable(&testTerm1, &accReference1) == SERVER_OK) {
		printf("Actual Result: SERVER_OK\n");
	}
	printf("\##########################\n");

	printf("\##########################\n");
	printf("Tester Name: Mahmoud Mahran\n");
	printf("Function Name: isAmountAvailable \n");
	printf("Test Case 2:\n");
	printf("Input Data: termData, accountRefrence\n");
	printf("Expected Result: LOW_BALANCE\n");
	if (isAmountAvailable(&testTerm2, &accReference2) == LOW_BALANCE) {
		printf("Actual Result: LOW_BALANCE\n");
	}
	else if (isAmountAvailable(&testTerm1, &accReference2) == SERVER_OK) {
		printf("Actual Result: SERVER_OK\n");
	}
	printf("\##########################\n");
}
void saveTransactionTest(void){
	ST_transaction_t transactions[5] = { 0 };

	//APPROVED
	strcpy_s(transactions[0].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[0].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[0].cardHolderData.primaryAccountNumber, 20, "6388761453882991");
	transactions[0].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[0].terminalData.transactionDate, 11, "02/10/2023");
	transactions[0].terminalData.transAmount = 100;
	transactions[0].transState = APPROVED;
	transactions[0].transactionSequenceNumber = 5;
	//DECLINED_INSUFFECIENT_FUND
	strcpy_s(transactions[1].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[1].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[1].cardHolderData.primaryAccountNumber, 20, "67710983163214064");
	transactions[1].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[1].terminalData.transactionDate, 11, "16/01/2023");
	transactions[1].terminalData.transAmount = 15000;
	transactions[1].transState = DECLINED_INSUFFECIENT_FUND;
	transactions[1].transactionSequenceNumber = 6;
	//DECLINED_STOLEN_CARD
	strcpy_s(transactions[2].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[2].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[2].cardHolderData.primaryAccountNumber, 20, "6371701407503227");
	transactions[2].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[2].terminalData.transactionDate, 11, "16/01/2023");
	transactions[2].terminalData.transAmount = 1500;
	transactions[2].transState = DECLINED_STOLEN_CARD;
	transactions[2].transactionSequenceNumber = 7;
	//FRAUD_CARD
	strcpy_s(transactions[3].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[3].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[3].cardHolderData.primaryAccountNumber, 20, "5847596847589658");
	transactions[3].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[3].terminalData.transactionDate, 11, "16/01/2023");
	transactions[3].terminalData.transAmount = 1500;
	transactions[3].transState = FRAUD_CARD;
	transactions[3].transactionSequenceNumber = 8;
	//INTERNAL_SERVER_ERROR
	strcpy_s(transactions[4].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[4].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[4].cardHolderData.primaryAccountNumber, 20, "5847596847589658");
	transactions[4].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[4].terminalData.transactionDate, 11, "16/01/2023");
	transactions[4].terminalData.transAmount = 1500;
	transactions[4].transState = INTERNAL_SERVER_ERROR;
	transactions[4].transactionSequenceNumber = 256;
	for (int i = 0; i < 5; i++) {
		printf("\##########################\n");
		printf("Tester Name: Mahmoud Mahran\n");
		printf("Function Name: saveTransaction\n");
		printf("Test Case %d:\n", (i + 1));
		printf("Input Data: transaction data\n");
		printf("Expected Result: SERVER_OK\n");
		printf("Actual Result: %d(0 for server ok)\n", saveTransaction(&transactions[i]));
		printf("\##########################\n");
	}
}
void listSavedTransactionsTest(void){
	ST_transaction_t transactions[5] = { 0 };
	ST_transaction_t my_transactionsDB[6] = { 0 };
	//APPROVED
	strcpy_s(transactions[0].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[0].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[0].cardHolderData.primaryAccountNumber, 20, "6821541302248965");
	transactions[0].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[0].terminalData.transactionDate, 11, "02/10/2023");
	transactions[0].terminalData.transAmount = 100;
	transactions[0].transState = 0;
	transactions[0].transactionSequenceNumber = 5;
	//DECLINED_INSUFFECIENT_FUND
	strcpy_s(transactions[1].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[1].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[1].cardHolderData.primaryAccountNumber, 20, "9293770170676345");
	transactions[1].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[1].terminalData.transactionDate, 11, "16/01/2023");
	transactions[1].terminalData.transAmount = 15000;
	transactions[1].transState = 0;
	transactions[1].transactionSequenceNumber = 6;
	//DECLINED_STOLEN_CARD
	strcpy_s(transactions[2].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[2].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[2].cardHolderData.primaryAccountNumber, 20, "4001060271215928");
	transactions[2].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[2].terminalData.transactionDate, 11, "16/01/2023");
	transactions[2].terminalData.transAmount = 1500;
	transactions[2].transState = 0;
	transactions[2].transactionSequenceNumber = 7;
	//FRAUD_CARD
	strcpy_s(transactions[3].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[3].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[3].cardHolderData.primaryAccountNumber, 20, "5847596847589658");
	transactions[3].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[3].terminalData.transactionDate, 11, "16/01/2023");
	transactions[3].terminalData.transAmount = 1500;
	transactions[3].transState = 0;
	transactions[3].transactionSequenceNumber = 8;
	//INTERNAL_SERVER_ERROR
	strcpy_s(transactions[4].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[4].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[4].cardHolderData.primaryAccountNumber, 20, "5847596847589658");
	transactions[4].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[4].terminalData.transactionDate, 11, "16/01/2023");
	transactions[4].terminalData.transAmount = 1500;
	transactions[4].transState = 0;
	transactions[4].transactionSequenceNumber = 9;
	ST_transaction_t transactionsDB[5] = { 0 };
	for (int j = 0; j < 5; j++) {
		/* Store transaction Sequence Number */
		transactionsDB[j].transactionSequenceNumber = transactions[j].transactionSequenceNumber;
		/* Store cardHolder Data */
		transactionsDB[j].cardHolderData = transactions[j].cardHolderData;
		/* Store transaction State */
		transactionsDB[j].transState = transactions[j].transState;
		/* Store transaction Date */
		transactionsDB[j].terminalData = transactions[j].terminalData;
	}
	printf("\##########################\n");
	printf("Tester Name: Mahmoud Mahran\n");
	printf("Function Name: listSavedTransactions \n");
	printf("Test Case 1:\n");
	printf("Input Data: void\n");
	printf("Expected Result: transactions db printed on console\n");
	printf("Actual Result:\n");
	listSavedTransactions();
	printf("\##########################\n");
}


//void main(void){
//	//recieveTransactionDataTest();
//	//isValidAccountTest();
//	//isAmountAvailableTest();
//	//isBlockedAccountTest();
//	saveTransactionTest();
//	listSavedTransactionsTest();
//}








