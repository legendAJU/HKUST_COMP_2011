#ifndef OCTOPUS_H
#define OCTOPUS_H

#include "helper.h"

/**
 * @brief The default iniital balance for a new Octopus card in cents.
 */
const int DEFAULT_INITIAL_BALANCE{5000};

/**
 * @brief The maximum number of transactions stored in an Octopus card.
 */
const int MAX_TRANSACTIONS{5};

/**
 * @brief The maxmimum length of C-strings supported by an Octopus card.
 */
const int MAX_DATA_LENGTH{64};

/**
 * @brief The maximum negative balance in cents an Octopus card is allowed to have.
 */
const int MAX_NEGATIVE_BALANCE{-5000};

/**
 * @brief The maximum top-up amount in cents a user is able to register AAVS for.
 */
const int MAX_AAVS_AMOUNT{100000};

/**
 * @brief The maximum balance in cents an Octopus card is able to store.
 */
const int MAX_STORED_BALANCE{300000};

enum TransactionType { EXPENSE, TOPUP };

/**
 * @brief An Octopus Transaction.
 */
struct OctopusTransaction {
  /**
   * @brief Whether this transaction is a valid transaction.
   */
  bool is_valid;

  /**
   * @brief The type of this transaction, i.e. whether this is an expense or a top-up.
   */
  TransactionType type;

  /**
   * @brief The value of this transaction.
   *
   * This value is an unsigned integer because it only stores the value of the transaction. For instance, if this
   * transaction is an expense of $10, this variable should be set to 1000.
   */
  unsigned int value;

  /**
   * @brief The description of this transaction.
   */
  char description[MAX_DATA_LENGTH];
};

/**
 * @brief Initializes a transaction to its default values.
 *
 * After initialization, the transaction should be invalid. The other variables can be set to any value.
 */
void transaction_init(OctopusTransaction& transaction);

/**
 * @brief Sets up a transaction using the provided values.
 *
 * The transaction's type, value, and description should be set according to the arguments provided to the
 * function.
 */
void transaction_setup(OctopusTransaction& transaction,
                       TransactionType type,
                       unsigned int value,
                       const char description[MAX_DATA_LENGTH]);

/**
 * @brief An Octopus card.
 */
struct Octopus {
  /**
   * @brief The Octopus number of this card, stored as an array of numbers.
   */
  short digits[NUM_DIGITS];

  /**
   * @brief The current balance of this Octopus card.
   */
  int current_balance;

  /**
   * @brief An array of the most recent transactions, stored as a circular buffer.
   */
  OctopusTransaction transactions[MAX_TRANSACTIONS];

  /**
   * @brief The index of the most recent transaction.
   */
  unsigned int most_recent_transaction_index;

  /**
   * @brief The top-up amount for this Octopus card if this card is registered with AAVS, or 0 if AAVS is not enabled.
   */
  unsigned int aavs_amount;
};

/**
 * @brief Initializes an Octopus card to its default values.
 *
 * After initialization, the card digits, and current balance should be set according to the arguments to this function.
 * All transactions should be initialized to invalid transactions, the most recent transaction index should be set to
 * `MAX_TRANSACTIONS - 1`, and the AAVS amount should be set to 0.
 */
bool octopus_init(Octopus& card, const short digits[NUM_DIGITS], int initial_balance = DEFAULT_INITIAL_BALANCE);

/**
 * @brief Tops-up value to this Octopus card by making a transaction with type `TOPUP`.
 *
 * @param card The Ocotpus card to top-up value to.
 * @param amount The top-up amount in cents.
 * @param description C-String containing the description of this transaction.
 */
bool octopus_topup(Octopus& card, unsigned int amount, const char description[MAX_DATA_LENGTH]);

/**
 * @brief Deducts value from this Octopus card by making a transaction with type `EXPENSE`.
 *
 * @param card The Ocotpus card to deduce value from.
 * @param amount The deduction amount in cents.
 * @param description C-String containing the description of this transaction.
 */
bool octopus_deduct(Octopus& card, unsigned int amount, const char description[MAX_DATA_LENGTH]);
/**
 * @brief Retrieves a recent transaction from the Octopus card.
 *
 * @param card The Octopus card to query.
 * @param recencyIndex The index of the transaction to retrieve (0 for most recent).
 * @return The requested OctopusTransaction. If the transaction is invalid, the returned struct will have isValid set to
 * false.
 */
OctopusTransaction octopus_get_recent_transaction(const Octopus& card, unsigned int recency_index);

/**
 * @brief Registers the Octopus card for Automatic Add Value Service (AAVS) with the specified amount.
 *
 * @param card The Octopus card to register.
 * @param aavsAmount The top-up amount in cents for AAVS.
 * @return true if registration is successful, false otherwise.
 */
bool octopus_register_aavs(Octopus& card, unsigned int aavs_amount);

/**
 * @brief Tries to top-up this Octopus using AAVS.
 *
 * @param card The Octopus card to top-up.
 * @param transaction_amount The value of the transaction that triggered AAVS.
 * @return true if AAVS top-up is successful, false if the top-up is unsuccessful or AAVS is not registered.
 */
bool octopus_try_aavs_topup(Octopus& card, unsigned int transaction_amount);

#endif  // OCTOPUS_H
