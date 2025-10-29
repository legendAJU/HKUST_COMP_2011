#include "octopus.h"

#include <cstring>

using namespace std;

void transaction_init(OctopusTransaction& transaction) {
  // TODO: Task 1.1
  transaction.is_valid = false;
}

void transaction_setup(OctopusTransaction& transaction,
                       TransactionType type,
                       unsigned int value,
                       const char description[MAX_DATA_LENGTH]) {
  // TODO: Task 1.2
  transaction.is_valid = true;
  transaction.type = type;
  transaction.value = value;
  strcpy(transaction.description,description);
}

bool octopus_init(Octopus& card, const short digits[NUM_DIGITS], int initial_balance) {
  // TODO: Task 2.1
  if(initial_balance < 0 || initial_balance > MAX_STORED_BALANCE)
    return false;
  else
  {
    for (int i = 0; i < NUM_DIGITS; i++) // init digit
    {
      card.digits[i] = digits[i];
    }
    card.current_balance = initial_balance; // init current balance
    for (int i = 0; i < MAX_TRANSACTIONS; i++) // init transactions
    {
      transaction_init(card.transactions[i]);
    }
    card.most_recent_transaction_index = MAX_TRANSACTIONS - 1; // init most_recent_transaction_index
    card.aavs_amount = 0; // init aavs amount
    return true;
  }
}

bool octopus_topup(Octopus& card, unsigned int amount, const char description[MAX_DATA_LENGTH]) {
  // TODO: Task 2.2
  if(card.current_balance + amount > MAX_STORED_BALANCE)
    return false;
  else
  {
    card.most_recent_transaction_index = (card.most_recent_transaction_index + 1 == MAX_TRANSACTIONS) ? 0 : card.most_recent_transaction_index + 1;
    transaction_setup(card.transactions[card.most_recent_transaction_index],TOPUP,amount,description);
    card.current_balance += amount;
    return true; 
  }
}

bool octopus_deduct(Octopus& card, unsigned int amount, const char description[MAX_DATA_LENGTH]) {
  // TODO: Task 2.3
  if(card.current_balance < 0 || (int)(card.current_balance - amount) < MAX_NEGATIVE_BALANCE)
  {
    if(octopus_try_aavs_topup(card,amount) == false)
    {
      return false;
    }
    else
    {
      card.most_recent_transaction_index = (card.most_recent_transaction_index + 1 == MAX_TRANSACTIONS) ? 0 : card.most_recent_transaction_index + 1;
      transaction_setup(card.transactions[card.most_recent_transaction_index],EXPENSE,amount,description);
      card.current_balance -= amount;
      return true; 
    }
  }
  else
  {
    card.most_recent_transaction_index = (card.most_recent_transaction_index + 1 == MAX_TRANSACTIONS) ? 0 : card.most_recent_transaction_index + 1;
    transaction_setup(card.transactions[card.most_recent_transaction_index],EXPENSE,amount,description);
    card.current_balance -= amount;
    return true; 
  }
}

OctopusTransaction octopus_get_recent_transaction(const Octopus& card, unsigned int recency_index) {
  OctopusTransaction transaction;

  // TODO: Task 2.4
  if(recency_index >= MAX_TRANSACTIONS)
  {
     transaction_init(transaction);
  }
  else
  {
    //cout << "Current most index = "<< card.most_recent_transaction_index;
    //cout << "Recency index = "<<recency_index;
    if((int)(card.most_recent_transaction_index - recency_index) >= 0)
    {
      transaction = card.transactions[card.most_recent_transaction_index - recency_index];
    }
    else
    {
      transaction = card.transactions[MAX_TRANSACTIONS + (int)(card.most_recent_transaction_index - recency_index)];
    }
  }
  return transaction;
}

bool octopus_register_aavs(Octopus& card, unsigned int aavs_amount) {
  // Note: The implementation of this function is provided for you.

  if (card.aavs_amount != 0) {
    // AAVS already registered
    return false;
  }
  if (aavs_amount == 0 || aavs_amount > MAX_AAVS_AMOUNT) {
    return false;
  }

  card.aavs_amount = aavs_amount;
  return true;
}

bool octopus_try_aavs_topup(Octopus& card, unsigned int transaction_amount) {
  // Note: The implementation of this function is provided for you.

  if (card.aavs_amount == 0) {
    // No AAVS setup for this Octopus Card
    return false;
  }

  const int new_balance =
      card.current_balance + static_cast<int>(card.aavs_amount) - static_cast<int>(transaction_amount);
  if (new_balance < MAX_NEGATIVE_BALANCE) {
    // AAVS limit exceeded
    return false;
  }

  return octopus_topup(card, card.aavs_amount, "AAVS");
}
