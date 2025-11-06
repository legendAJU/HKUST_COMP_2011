/* Header file for utility functions and data structures */
#ifndef UTILS_H
#define UTILS_H

/* ----------  Include Files  ---------- */
#include <iostream>
#include <string>

/* ----------  Constants  ---------- */
#define MAX_ACCOUNT        20 /* max number of accounts */
#define MAX_MODEL          15 /* max number of models */
#define MAX_PKG_TOTAL      100 /* max total token packages per account */
#define NAME_MAX_LEN       20 /* max length for names */
#define ORDER_ID_MAX_LEN   20   /* max length for order ID */
#define CONSUME_ID_MAX_LEN 20  /* max length for consumption ID */

/* ----------  Data Structures  ---------- */
/* The struct defines the GenAI Model. Model table is a dynamic array indexed by the model ID and stored in model.cpp.*/
struct Model {
    int modelId; /*model ID*/
    char name[NAME_MAX_LEN]; /*model name*/
    int pricePerToken; /*price per token in HKD*/
};

/* The struct defines the node representing one top-up order — contains orderId, modelId, modelName, remaining tokens (amount), and next pointer. */
struct TopupTokenPkg {
    char orderId[ORDER_ID_MAX_LEN]; /*order ID*/
    int amount; /*token amount*/
    int modelId; /*model ID*/
    char modelName[NAME_MAX_LEN];   /*model name*/
    TopupTokenPkg* next; /*pointer to next package*/
};

/* The struct defines the node for comsumption records — contains consumeId, modelId, modelName, token amount consumed, and next pointer. */
struct ConsumptionRecord {
    char consumeId[CONSUME_ID_MAX_LEN]; /*consumption ID string*/
    int modelId; /*model ID*/
    char modelName[NAME_MAX_LEN];       /*model name*/
    int amount; /*token amount consumed*/
    ConsumptionRecord* next; /*pointer to next record*/
};

/* The struct defines the node for account — contains account ID, total token balance. For each account,you need to maintain a singly-linked list of nodes of top-up token packages, a singly-linked list of nodes of top-up history records, and a singly-linked list of nodes of consumption history records.*/
struct Account {
    long id; /*account ID*/
    char name[NAME_MAX_LEN]; /*account name*/
    int balance; /*total token balance*/
    TopupTokenPkg* pkgList; /*pointer to token packages*/
    TopupTokenPkg* rechargeHistoryList; /*pointer to complete top-up history*/
    ConsumptionRecord* consumeList; /*pointer to consumption records*/
};

/* ----------  Model Functions  ---------- */
Model* getModelTable(); /* Returns pointer to static model table */
int getModelCount(); /* Returns total model count */
int getModelPrice(int modelId); /* Returns token price for given model ID */
int validateAndConvertTopUp(int modelId, int hkdAmount, int* tokenAmount); /* Validates and converts top-up amount */

/* ----------  Token Station Functions  ---------- */
TopupTokenPkg* newTokenPkg(const char orderId[], int amount, int modelId, const char* modelName); /* Creates a new token package node */
void insertPkg(Account* acc, TopupTokenPkg* pkg); /* Inserts a token package at the tail of the account's package list */
TopupTokenPkg* removePkgTail(Account* acc); /* Removes the tail (oldest) token package from the account's package list */
int consumeTokens(Account* acc, int request, int modelId);  /* Consumes tokens from the account in first-in-first-out (FIFO) manner for a specific model */
void viewRechargeHistory(const Account* acc); /* Views recharge history of the account */
void viewConsumptionHistory(const Account* acc); /* Views consumption history of the account */

/* ----------  Account Functions  ---------- */
Account* newAccount(long id, const char* name); /* Creates a new account */
void releaseAccount(Account* acc); /* Releases all memory associated with the account */
bool topUpAccount(Account* acc, int modelId, int amount, const char* modelName); /* Tops up tokens to the account for a specific model */
int getTokenBalance(Account* acc, int modelId); /* Gets the token balance for a specific model in the account */
int calculateTopUpCost(int tokenAmount, int modelId, Model* modelTable); /* Calculates the cost for a top-up request */

/* ----------  Console Functions  ---------- */
void line(char c, int len); /* Prints a line of specified character and length */
void header(const std::string& title); /* Prints a formatted header */
bool pause(); /* Pauses the program and waits for user input */
void showWelcome(int accCnt); /* Displays welcome message with current account count */
void showHelp(); /* Displays help information */
void showMainMenu(); /* Displays the main menu */
void showGoodbye(Account* accList[], int accCount); /* Displays goodbye message and summary */

/* ----------  Input Functions  ---------- */
int readInt(const std::string& prompt, int low, int high); /* Reads an integer input within a specified range */

/* ----------  Account Management Functions  ---------- */
void createNewAccount(Account* accList[], int& count, int maxAcc); /* Creates a new account and adds it to the account list */
int selectAccount(Account* accList[], int accCount); /* Allows user to select an account from the list */
void viewAccountDetails(Account* accList[], int accCount, Model* modelTable, int modelCnt); /* Views details of a selected account */
void showAllAccounts(Account* accList[], int accCount); /* Displays all registered accounts */
void deleteAccountFromList(Account* accList[], int& accCount); /* Deletes an account from the account list */
void topUpTokens(Account* accList[], int accCount, Model* modelTable, int modelCnt); /* Tops up tokens for a specific account */
void runConsumptionRound(Account* accList[], int accCount, Model* modelTable, 
                        int modelCnt, int& roundCounter); /* Runs a token consumption round for a selected account */
void printBalanceByModel(Account* acc, Model* modelTable, int mCnt); /* Prints token balance by model for the account */
int pickModel(Model* modelTable, int mCnt);  /* Allows user to pick a model from the model table */

#endif // UTILS_H