/*
 *  lab7.cpp  -  main program
 *  GenAI Token Top-Up Station  (Fall 2025)
 *  Hongmei WANG: hwangfy@connect.ust.hk
 */


#include <iostream>
#include "utils.h"
using namespace std;

int main() {
    /* ----------  load models  ----------*/
    Model* modelTable = getModelTable();
    int modelCnt = getModelCount();

    /* ----------  initialize accounts  ----------*/
    Account* accList[MAX_ACCOUNT]; /* pointer array for accounts */
    int accCount = 0;               /* current account count */

    /* ----------  main interaction loop  ----------*/
    showWelcome(accCount);
    showHelp();

    int round = 0, opt = 1;

    while (opt != 0) {  
        showMainMenu();
        opt = readInt("  Your choice: ", 0, 6);

        if (opt == 0) {
            break;  /* Exit the program if user chooses 0 */
        }

        switch (opt) {
        case 1:  /* Create a new account */
            createNewAccount(accList, accCount, MAX_ACCOUNT);
            break;
        case 2:  /* View account details */
            viewAccountDetails(accList, accCount, modelTable, modelCnt);
            break;
        case 3:  /* Token top-up */
            topUpTokens(accList, accCount, modelTable, modelCnt);
            break;
        case 4:  /* Run a consumption round */
            runConsumptionRound(accList, accCount, modelTable, modelCnt, round);
            break;
        case 5:  /* Show all accounts */
            showAllAccounts(accList, accCount);
            break;
        case 6:  /* Delete an account */
            deleteAccountFromList(accList, accCount);
            break;
        }

        /* Check if user wants to continue */
        if (!pause()) {
            break;  /* Exit the program if user chooses 0 */
        }
    }

    /* ----------  cleanup and exit  ----------*/
    showGoodbye(accList, accCount);
    return 0;
}
