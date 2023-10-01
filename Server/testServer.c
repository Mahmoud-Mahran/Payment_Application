/*###########################################################################################################*/
/* Author :                                     Mahmoud Mahran                                               */
/* File Name :                                    testServer.c                                               */
/* Version :                                        V1.0.0                                                   */
/* Date :                                         1 Oct 2023                                                 */
/*###########################################################################################################*/
void recieveTransactionDataTest(void){
	ST_transaction_t transactions[5];
	
	//APPROVED
	strcpy_s(transactions[0].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[0].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[0].cardHolderData.primaryAccountNumber, 20, "5847596847589658");
	transactions[0].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[0].terminalData.transactionDate, 11, "16/01/2023");
	transactions[0].terminalData.transAmount = 1500;
	transactions[0].transState = 0;
	transactions[0].transactionSequenceNumber = 69;
	//DECLINED_INSUFFECIENT_FUND
	strcpy_s(transactions[1].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[1].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[1].cardHolderData.primaryAccountNumber, 20, "5847596847589658");
	transactions[1].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[1].terminalData.transactionDate, 11, "16/01/2023");
	transactions[1].terminalData.transAmount = 15000;
	transactions[1].transState = 0;
	transactions[1].transactionSequenceNumber = 69;
	//DECLINED_STOLEN_CARD
	strcpy_s(transactions[2].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[2].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[2].cardHolderData.primaryAccountNumber, 20, "5847596847589658");
	transactions[2].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[2].terminalData.transactionDate, 11, "16/01/2023");
	transactions[2].terminalData.transAmount = 1500;
	transactions[2].transState = 0;
	transactions[2].transactionSequenceNumber = 69;
	//FRAUD_CARD 
	strcpy_s(transactions[3].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[3].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[3].cardHolderData.primaryAccountNumber, 20, "5847596847589658");
	transactions[3].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[3].terminalData.transactionDate, 11, "16/01/2023");
	transactions[3].terminalData.transAmount = 1500;
	transactions[3].transState = 0;
	transactions[3].transactionSequenceNumber = 69;
	//INTERNAL_SERVER_ERROR
	strcpy_s(transactions[4].cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transactions[4].cardHolderData.cardHolderName, 25, "Mahmoud Ahmed Mohamed");
	strcpy_s(transactions[4].cardHolderData.primaryAccountNumber, 20, "5847596847589658");
	transactions[4].terminalData.maxTransAmount = 20000;
	strcpy_s(transactions[4].terminalData.transactionDate, 11, "16/01/2023");
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
	
}
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void saveTransactionTest(void);
void listSavedTransactionsTest(void);











