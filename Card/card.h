#pragma once
/ ###########################################################################################################/
/* Author :                                 Mohamed Yehia El-Greatly                                         */
/* File Name :                                     terminal.h                                                */
/* Version :                                        V1.0.0                                                   */
/* Date :                                         28 Sep 2023                                                */
/###########################################################################################################/
/* @Description  :                                                                                           */
/*                Terminal is an interface between the user and our software application,                    */
/*                consists of a hardware part (KayPad) and a software module.                                */
/*                                                                                                           */
/* Terminal main features  :   - Verify the card data and the user inputs.                                   */
/*                             - Ask for the amount and PIN number.                                          */
/*                             - Verify the maximum amount and the PIN number.                               */
/*                             - Send card data and the transaction amount to the bank server.               */
/###########################################################################################################/
/*@Features  :                                                                                               */
/*                  -  getTransactionDate()                                                                  */
/*                  -  getTransactionAmount()                                                                */
/*                  -  setMaxAmount()                                                                        */
/*                  -  isCardExpired()                                                                       */
/*                  -  isBelowMaxAmount()                                                                    */
/*                  -  isValidCardPAN()                                                                      */
/###########################################################################################################/
/*  The Architect Give The APIs                                                                              */
/*                   1-  The Name of Function                                                                */
/*                   2-  What is the input                                                                   */
/*                   3-  Return Type  "Error State"                                                          */
/*                   4-  Object Like Macros                                                                  */
/########################################################################################################### /