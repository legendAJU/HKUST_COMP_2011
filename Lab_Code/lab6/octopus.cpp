#include "octopus.h"

#include <cstring>

using namespace std;

void transaction_init(OctopusTransaction& transaction) {
  // TODO: Task 1.1
}

void transaction_setup(OctopusTransaction& transaction,
                       TransactionType type,
                       unsigned int value,
                       const char description[MAX_DATA_LENGTH]) {
  // TODO: Task 1.2
}

bool octopus_init(Octopus& card, const short digits[NUM_DIGITS], int initial_balance) {
  // TODO: Task 2.1
  return false;
}

bool octopus_topup(Octopus& card, unsigned int amount, const char description[MAX_DATA_LENGTH]) {
  // TODO: Task 2.2
  return false;
}

bool octopus_deduct(Octopus& card, unsigned int amount, const char description[MAX_DATA_LENGTH]) {
  // TODO: Task 2.3
  return false;
}

OctopusTransaction octopus_get_recent_transaction(const Octopus& card, unsigned int recency_index) {
  OctopusTransaction transaction;

  // TODO: Task 2.4

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
