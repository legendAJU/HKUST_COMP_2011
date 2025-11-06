/*
 *  cli_helpers.cpp  -  command-line interface helpers
 *  GenAI Token Top-Up Station  (Fall 2025)
 *  Hongmei WANG: hwangfy@connect.ust.hk
 */

#include "utils.h"
#include <iostream>
#include <limits>
#include <cstring>
using namespace std;

/* ----------  Formatting helpers  ---------- */
void line(char c, int len) { cout << string(len, c) << '\n'; }
void header(const string& title) {
    line('=', 60);
    cout << "  " << title << '\n';
    line('=', 60);
}

/* ----------  Pause and continue?  ---------- */
bool pause() {
    int choice = readInt("  Continue? (1=Return to Main Menu, 0=Exit Program): ", 0, 1);
    return choice == 1;
}

/* ----------  Welcome and help  ---------- */
void showWelcome(int accCnt) {
    header("GenAI Token Top-Up Station");
    cout << "  Current registered accounts: " << accCnt << "\n";
    cout << "  System ready!\n\n";
}

/* ----------  Quick help info  ---------- */
void showHelp() {
    header("Quick Help");
    cout << "  - Create accounts and manage token balances.\n"
         << "  - Top-up tokens for specific AI models.\n"
         << "  - Check balances and consume tokens.\n"
         << "  - Delete accounts.\n";
}

/* ----------  Display menus  ---------- */
void showMainMenu() {
    cout << "\n  ============  Main Menu  ============\n";
    cout << "  1) Create new account\n";
    cout << "  2) View account details\n";
    cout << "  3) Top-up tokens\n";
    cout << "  4) Run consumption round\n";
    cout << "  5) Show all accounts\n";
    cout << "  6) Delete account\n";
    cout << "  0) Exit\n";
    cout << "  ====================================\n";
}

/* ----------  Exit and cleanup  ---------- */
void showGoodbye(Account* accList[], int accCount) {
    cout << "\n";
    header("Thank you for using Token Top-Up Station!");
    cout << "  Total accounts managed: " << accCount << "\n";
    
    // release storage
    for (int i = 0; i < accCount; ++i) {
        releaseAccount(accList[i]);
        delete accList[i];
    }
    
    cout << "  Goodbye!\n";
}

/* ----------  input  ---------- */
int readInt(const std::string& prompt, int low, int high) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= low && val <= high) return val;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid! Please enter a number between "
             << low << " and " << high << ".\n";
    }
}

/* ----------  account management  ---------- */

/*---------- create new account ----------*/
void createNewAccount(Account* accList[], int& count, int maxAcc) {
    if (count >= maxAcc) { 
        cout << "  Account pool full! Maximum " << maxAcc << " accounts allowed.\n"; 
        return; 
    }
    
    long id;
    char name[NAME_MAX_LEN];

    cout << "\n  =============  Create New Account  =============\n";

    /* ---------- 1. Enter and validate an 8-digit numeric ID. ---------- */
    while (true) {
        cout << "  Student ID (8 digits): ";
        if (!(cin >> id)) {          
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input. Please enter 8 digits.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (id < 10000000L || id > 99999999L) { 
            cout << "  ID must be exactly 8 digits.\n";
            continue;
        }
        break;
    }

    /* Check for duplicate names */
    for (int i = 0; i < count; ++i) {
        if (accList[i]->id == id) {
            cout << "  Error: Account ID " << id << " already exists!\n";
            return;
        }
    }

    /* ---------- 2. Enter and validate a non-empty name. ---------- */
    while (true) {
        cout << "  Name ( please do not longer than " << NAME_MAX_LEN << " characters): ";
        cin.getline(name, NAME_MAX_LEN);

        // Only clear if getline fails (e.g., buffer overflow).
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Input too long. Please re-enter.\n";
            continue;
        }

        bool onlySpace = true;
        for (int i = 0; name[i] != '\0'; ++i) {
            if (!isspace(static_cast<unsigned char>(name[i]))) {
                onlySpace = false;
                break;
            }
        }

        if (name[0] == '\0' || onlySpace) {
            cout << "  Name cannot be empty. Please re-enter.\n";
            continue;
        }

        break;
    }

    /* ---------- 3. create Account ---------- */
    accList[count] = newAccount(id, name);
    if (accList[count] != nullptr) {
        ++count;
        cout << "  Success! Account created for " << name << " (ID: " << id << ")\n";
    } else {
        cout << "  Error: Failed to create account!\n";
    }

}

/* ----------  select account from list  ---------- */
int selectAccount(Account* accList[], int accCount) {
    if (accCount == 0) {
        cout << "  No accounts available!\n";
        return -1;
    }
    
    cout << "\n  =============  Select Account  =============\n";
    for (int i = 0; i < accCount; ++i) {
        cout << "    " << (i + 1) << ") " << accList[i]->name 
             << " (ID: " << accList[i]->id << ")\n";
    }
    
    int choice = readInt("  Your choice: ", 1, accCount);
    return choice - 1;  /* Convert to array index */
}

/* ----------  view account details  ---------- */
void viewAccountDetails(Account* accList[], int accCount, Model* modelTable, int modelCnt) {
    int accIndex = selectAccount(accList, accCount);
    if (accIndex < 0) return;
    
    Account* acc = accList[accIndex];
    cout << "\n  =============  Account Details  =============\n";
    cout << "  Name: " << acc->name << "\n";
    cout << "  Account ID: " << acc->id << "\n";
    cout << "  Total Balance: " << acc->balance << " tokens\n";
    cout << "\n  Token Balance by Model:\n";
    
    printBalanceByModel(acc, modelTable, modelCnt);

    /* Show recharge history */
    viewRechargeHistory(acc);

    /* Show consumption history */
    viewConsumptionHistory(acc);
}

/* ----------  show all accounts  ---------- */
void showAllAccounts(Account* accList[], int accCount) {
    cout << "\n  =============  All Accounts Overview  =============\n";
    if (accCount == 0) {
        cout << "  No accounts registered yet.\n";
        return;
    }
    
    for (int i = 0; i < accCount; ++i) {
        cout << "\n  " << (i + 1) << ". Account: " << accList[i]->name 
             << " (ID: " << accList[i]->id << ")\n";
        cout << "     Total Balance: " << accList[i]->balance << " tokens\n";
        
        /* Show model-wise balances */
        cout << "     Model Balances:\n";
        Model* modelTable = getModelTable();
        int modelCnt = getModelCount();
        
        for (int j = 0; j < modelCnt; ++j) {
            int balance = getTokenBalance(accList[i], modelTable[j].modelId);
            printf("       %2d) %-20s : %6d tokens", 
                   modelTable[j].modelId, 
                   modelTable[j].name, 
                   balance);
            
            if (balance == 0) {
                cout << " (empty)";
            }
            cout << "\n";
        }
        
        if (i < accCount - 1) {
            cout << "  " << string(55, '-') << "\n";
        }
    }
    
    cout << "\n  ==================================================\n";
}

/* ----------  delete account  ---------- */
void deleteAccountFromList(Account* accList[], int& accCount) {
    int accIndex = selectAccount(accList, accCount);
    if (accIndex < 0) return;
    
    cout << "   Delete account " << accList[accIndex]->name; 
    cout << "  Please confirm (1=Yes, 0=No): ";

    int confirm = readInt("", 0, 1);
    
    if (confirm == 1) {
        releaseAccount(accList[accIndex]);
        
        // Shift remaining accounts left
        for (int i = accIndex; i < accCount - 1; ++i) {
            accList[i] = accList[i + 1];
        }
        accCount--;
        
        cout << "\n  Account deleted successfully!\n";
    } else {
        cout << "\n  Account deletion cancelled.\n";
    }
}

/* ----------  token top-up  ---------- */
void topUpTokens(Account* accList[], int accCount, Model* modelTable, int modelCnt) {
    int accIndex = selectAccount(accList, accCount);
    if (accIndex < 0) return;
    
    Account* acc = accList[accIndex];
    cout << "\n  =============  Top-Up Tokens  =============\n";
    cout << "  Account: " << acc->name << " (Current balance: " << acc->balance << ")\n";

    /* ----------  show available models  ---------- */
    cout << "\n  Available models:\n";
    for (int i = 0; i < modelCnt; ++i) {
        cout << "    " << modelTable[i].modelId << ") " << modelTable[i].name 
             << " (Price: " << modelTable[i].pricePerToken << " per token)\n";
    }
    
    int modelId = readInt("  Select model ID: ", 1, modelCnt);
    int tokenAmount = readInt("  Enter token amount to top-up (1-100000): ", 1, 100000);

    /* ----------  validate and convert top-up amount to token count  ---------- */
    int amount = 0;
    int hkdAmount = calculateTopUpCost(tokenAmount, modelId, modelTable); /* calculate HKD amount */

    /* ----------  request confirmation  ---------- */
    cout << "  Confirm top-up of " << tokenAmount << " tokens for model " << modelId 
         << " (Total: " << hkdAmount << " HKD)? (1=Yes, 0=No): ";
    int confirm = readInt("", 0, 1);

    if (confirm == 0) {
        cout << "  Top-up cancelled.\n";
        return;
    }

    amount = tokenAmount;

    /* ----------  create token package and add to account  ---------- */
    if (topUpAccount(acc, modelId, amount, modelTable[modelId - 1].name)) {
        cout << "  Success! Added " << amount << " tokens for model " << modelId << "\n";
        cout << "  New balance: " << acc->balance << " tokens\n";
    } else {
        cout << "  Error: Failed to top-up tokens!\n";
    }
}

/* ----------  add consumption record  ---------- */
void addConsumptionRecord(Account* acc, int modelId, const char* modelName, int amount) {
    if (!acc || amount <= 0) return;
    static int consumeCounter = 10000;
    ConsumptionRecord* rec = new ConsumptionRecord;
    snprintf(rec->consumeId, CONSUME_ID_MAX_LEN, "CNS%d", consumeCounter++);
    rec->modelId = modelId;
    strncpy(rec->modelName, modelName, NAME_MAX_LEN - 1); // 新增
    rec->modelName[NAME_MAX_LEN - 1] = '\0';
    rec->amount = amount;
    rec->next = acc->consumeList;
    acc->consumeList = rec;
}

/* ----------  run a consumption round  ---------- */
void runConsumptionRound(Account* accList[], int accCount,
                         Model* modelTable, int mCnt, int& roundCounter) {
    if (accCount == 0) {
        cout << "  No accounts available for consumption round!\n";
        return;
    }
    
    header("Consumption Round " + to_string(++roundCounter));

    /* ----------  select account from list  ---------- */
    int accIndex = selectAccount(accList, accCount);
    if (accIndex < 0) return;
    
    Account* selectedAcc = accList[accIndex];
    
    cout << "\n  Selected Account: " << selectedAcc->name 
         << " (ID: " << selectedAcc->id << ")\n";
    cout << "  Current balance: " << selectedAcc->balance << " tokens\n";
    
    if (selectedAcc->balance == 0) {
        cout << "  No tokens available. Please top-up first.\n";
        return;
    }

    /* ----------  show token balance by model  ---------- */
    cout << "\n  Token Balance by Model:\n";
    printBalanceByModel(selectedAcc, modelTable, mCnt);
    
    /* ----------  select model for consumption  ---------- */
    cout << "\n  Available models for consumption:\n";
    int modelId = pickModel(modelTable, mCnt);

    /* ----------  check model token balance  ---------- */
    int modelBalance = getTokenBalance(selectedAcc, modelId);
    if (modelBalance == 0) {
        cout << "  No tokens available for this model. Please top-up first.\n";
        return;
    }
    
    cout << "  Available tokens for this model: " << modelBalance << "\n";
    int request = readInt("  How many tokens to consume: ", 1, modelBalance);

    /* ----------  execute consumption  ---------- */



    int consumed = consumeTokens(selectedAcc, request, modelId);
    

    cout << "\n  =============  Consumption Result  =============\n";
    cout << "  Account: " << selectedAcc->name << "\n";
    cout << "  Model: ";
    for (int i = 0; i < mCnt; ++i) {
        if (modelTable[i].modelId == modelId) {
            cout << modelTable[i].name << "\n";
            break;
        }
    }
    cout << "  Requested: " << request << " tokens\n";
    cout << "  Actually consumed: " << consumed << " tokens\n";
    cout << "  Remaining balance: " << selectedAcc->balance << " tokens\n";

    /* Consumption Details*/
    /* Record consumption */
    if (consumed > 0) {
        const char* modelName = "Unknown";
        Model* modelTable = getModelTable();
        int modelCnt = getModelCount();
        
        for (int i = 0; i < modelCnt; ++i) {
            if (modelTable[i].modelId == modelId) {
                modelName = modelTable[i].name;
                break;
            }
        }
        
        addConsumptionRecord(selectedAcc, modelId, modelName, consumed);
    }

    cout << "\n  Consumption Details:\n";

    /* Print the current state of token packages for the current modelId */
    TopupTokenPkg* printCurr = selectedAcc->pkgList;
    cout << "  Remaining packages after consumption:" << endl;
    while (printCurr) {
        if (printCurr->modelId == modelId) {
            cout << "  Package ID: " << printCurr->orderId << ", Amount: " << printCurr->amount << endl;
        }
        printCurr = printCurr->next;
    }

    if (consumed < request) {
        cout << "  Note: Could not consume all requested tokens.\n";
    }
    
    cout << "  ==============================================\n";
}

/* ----------  helpers  ---------- */
/* ----------  pick model from list  ---------- */
int pickModel(Model* modelTable, int mCnt) {
    cout << "  Available models:\n";
    for (int i = 0; i < mCnt; ++i) {
        cout << "    " << modelTable[i].modelId << ") " << modelTable[i].name 
             << " (Price: " << modelTable[i].pricePerToken << " per token)\n";
    }
    return readInt("  Select model ID: ", 1, mCnt);
}

/* ----------  print token balance by model  ---------- */
void printBalanceByModel(Account* acc, Model* modelTable, int mCnt) {
    cout << "  ------------------------------------------------------------\n";
    cout << "  |                    Token Balance by Model                |\n";
    cout << "  ------------------------------------------------------------\n";
    
    int totalBalance = 0;
    for (int i = 0; i < mCnt; ++i) {
        int balance = getTokenBalance(acc, modelTable[i].modelId);
        totalBalance += balance;
        
        /* ----------  formatted output  ---------- */
        printf("  | %2d) %-20s | %6d tokens  |\n", 
               modelTable[i].modelId, 
               modelTable[i].name, 
               balance);
    }
    
    cout << "  ------------------------------------------------------------\n";
    printf("  |  Total Balance:                        | %5d tokens    |\n", totalBalance);
    cout << "  ------------------------------------------------------------\n";
}


void viewRechargeHistory(const Account* acc) {
    cout << "\n  =============  Recharge History  =============\n";
    if (!acc) {
        cout << "  No account selected.\n";
        return;
    }
    if (!acc->rechargeHistoryList) {
        cout << "  No recharge records.\n";
        return;
    }
    
    const TopupTokenPkg* p = acc->rechargeHistoryList;
    cout << "    Order ID         | Model ID | Model Name           | Amount\n";
    cout << "    ----------------+----------+----------------------+-------\n";
    while (p) {
        printf("    %-16s | %8d | %-20s | %6d\n", p->orderId, p->modelId, p->modelName, p->amount);
        p = p->next;
    }
}

void viewConsumptionHistory(const Account* acc) {
    cout << "\n  =============  Consumption History  =============\n";
    if (!acc) {
        cout << "  No account selected.\n";
        return;
    }
    if (!acc->consumeList) {
        cout << "  No consumption records.\n";
        return;
    }
    const ConsumptionRecord* p = acc->consumeList;
    cout << "    Consume ID       | Model ID | Model Name           | Amount\n";
    cout << "    -----------------+----------+----------------------+-------\n";
    while (p) {
        printf("    %-16s | %8d | %-20s | %6d\n", p->consumeId, p->modelId, p->modelName, p->amount);
        p = p->next;
    }
}