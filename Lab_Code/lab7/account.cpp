/*
 *  account.cpp  -  account data operations
 *  GenAI Token Top-Up Station  (Fall 2025)
 *  Hongmei WANG: hwangfy@connect.ust.hk
 */

#include "utils.h"
#include <cstring>
#include <iostream>
using namespace std;

Account* newAccount(long id, const char* name) {

    /*
     * TODO 1: Initialize a new account
     * 1. Dynamically allocate an Account object and assign the supplied id & name.
     * 2. Set balance to 0.
     * 3. Set pkgList, rechargeHistoryList and consumeList to nullptr.
     * 4. Return the pointer to the new account.
     */
    

}

bool topUpAccount(Account* acc, int modelId, int amount, const char* modelName) {
    if (!acc || amount <= 0) return false;

    /* Generate order ID */
    static int orderCounter = 1000;
    char orderId[ORDER_ID_MAX_LEN];
    snprintf(orderId, ORDER_ID_MAX_LEN, "ORD%d", orderCounter++);

    /* create and insert new token package */
    TopupTokenPkg* pkg = newTokenPkg(orderId, amount, modelId, modelName);
    if (!pkg) return false;
    insertPkg(acc, pkg);

    /* recharge history (independent allocation) */
    TopupTokenPkg* historyPkg = newTokenPkg(orderId, amount, modelId, modelName);
    historyPkg->next = acc->rechargeHistoryList;
    acc->rechargeHistoryList = historyPkg;

    return true;
}

