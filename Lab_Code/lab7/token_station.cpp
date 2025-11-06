/*
 *  token_station.cpp  -  token package linked list operations
 *  GenAI Token Top-Up Station  (Fall 2025)
 *  Hongmei WANG: hwangfy@connect.ust.hk
 *  -----------------------------------------
 */

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "utils.h"
using namespace std;



/* Calculate top-up cost in HKD for a specific model */
int calculateTopUpCost(int tokenAmount, int modelId, Model* modelTable) {
    if (!modelTable || modelId < 1 || modelId > getModelCount()) return 0;

   /*
     * TODO 2: Compute the total HKD cost for the requested token amount.
     * Return the total HKD cost
     */
    return getModelPrice(modelId) * tokenAmount;
}


/* ----------  create a token package node  ---------- */
TopupTokenPkg* newTokenPkg(const char orderId[], int amount, int modelId, const char* modelName) {

    /*
     * TODO 3: Allocate and initialize a new TopupTokenPkg node.
     * 1. Dynamically allocate a TopupTokenPkg object.
     * 2. Copy orderId and modelName into their respective fields
     *    (use strncpy to avoid buffer overflow and ensure null-termination).
     * 3. Set amount, modelId, and next (nullptr).
     * 4. Return the pointer to the new node.
     */
    TopupTokenPkg* newTokenPkg = new TopupTokenPkg;
    strncpy(newTokenPkg->orderId,orderId,ORDER_ID_MAX_LEN);
    newTokenPkg->amount = amount;
    newTokenPkg->modelId = modelId;
    strncpy(newTokenPkg->modelName,modelName,NAME_MAX_LEN);
    newTokenPkg->next = nullptr;
    return newTokenPkg;
}


/* ----------  tail-insert into account list  ---------- */
void insertPkg(Account* acc, TopupTokenPkg* pkg) {
    if (!acc || !pkg) return;

    /*
     * TODO 4: Insert pkg at the head or tail of acc->pkgList and update balance.
     */
    //insert at tail
    if(acc->pkgList == nullptr) 
    {
        acc->pkgList = pkg;
        acc->balance += pkg->amount;
        return;
    }
    TopupTokenPkg* pkgList = acc->pkgList;
    while(pkgList != nullptr)
    {
        //cout<<"--------------------------------Updateing! ----------------------------"<<endl;
        if(pkgList->next == nullptr)
        {
            
            //cout<<"Total account balance is "<< acc->balance<<endl;
            //cout<<"Total pkg amount is "<< pkg->amount<<endl;
            pkgList->next = pkg;
            acc->balance += pkg->amount;
            break;
            //cout<<"Now total account balance is " << acc->balance<<endl;
        }
        pkgList = pkgList->next;
    }

}

/* ----------  consume tokens (FIFO, model-specific, do not delete nodes)  ---------- */
int consumeTokens(Account* acc, int request, int modelId) {
    if (!acc || request <= 0) return 0;
    /* Define the consumed variable to track the total tokens consumed so far */
    int consumed = 0; 

    /* 
    * TO DO 5: consume in first-in-first-out (FIFO) order, and only reduce amount but not delete nodes 
    * Return the total number of tokens actually consumed.
    * Tips: traverse the linked list, and reduce the amount of each package node
    *       until the request is fully satisfied or no more tokens available
    */
   TopupTokenPkg* pkgList = acc->pkgList;
   while(pkgList != nullptr)
   {    
    if(pkgList->modelId == modelId)
    {
        if(consumed > request)
        {
            break;
        }
        else
        {
            int token_consumed_value = (pkgList->amount > (request - consumed))? (request-consumed):pkgList->amount;
            pkgList->amount -= token_consumed_value;
            consumed += token_consumed_value;
            acc->balance -= token_consumed_value;
        }
    }
    pkgList = pkgList->next;
   }
   return consumed;


}

/* Calculate token balance for a specific model */
int getTokenBalance(Account* acc, int modelId) {
    if (!acc) return 0;

    /*
     * TODO 6: Sum all tokens in acc->pkgList that belong to modelId.
     * 1. Traverse the entire pkgList.
     * 2. Accumulate the amount field for every node where modelId matches.
     * 3. Return the total.
     */
    int amount = 0;
    TopupTokenPkg* pkgList = acc->pkgList;
    while(pkgList != nullptr)
    {
        if(pkgList->modelId == modelId) amount += pkgList->amount;
        if(pkgList->next == nullptr) break;
        pkgList = pkgList->next;
    }
    return amount;
}


/* ----------  release entire list  ---------- */
void releaseAccount(Account* acc) {
    if (!acc) return;
    TopupTokenPkg* curr = acc->pkgList;
    while (curr) {
        TopupTokenPkg* next = curr->next;
        delete curr;
        curr = next;
    }
    acc->pkgList = nullptr;
    acc->balance = 0;

    /* release consumption records */
    ConsumptionRecord* cRec = acc->consumeList;
    while (cRec) {
        ConsumptionRecord* next = cRec->next;
        delete cRec;
        cRec = next;
    }
    acc->consumeList = nullptr;
}
