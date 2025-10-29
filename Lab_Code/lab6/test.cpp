#include "test.h"

#include "helper.h"
#include "octopus.h"

#include <cassert>
#include <cstring>
#include <iostream>

namespace {
void test1() {
  Octopus card{};
  const short digits[NUM_DIGITS]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  assert(octopus_init(card, digits) && "Octopus initialization failed but expected to succeed");

  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == digits[i] && "Card number digit mismatch");
  }

  assert(card.current_balance == DEFAULT_INITIAL_BALANCE && "Card balance mismatch");

  for (std::size_t i{0}; i < MAX_TRANSACTIONS; ++i) {
    assert(!card.transactions[i].is_valid && "Card transaction validity mismatch");
  }

  assert(card.aavs_amount == 0 && "Card AAVS amount mismatch");
}

void test2() {
  Octopus card{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, DEFAULT_INITIAL_BALANCE, {}, MAX_TRANSACTIONS - 1, 0};
  for (int i{0}; i < MAX_TRANSACTIONS; ++i) {
    card.transactions[i].is_valid = false;
  }

  assert(octopus_topup(card, 10000, "MTR") && "Top-up failed but expected to succeed");
  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == 0 && "Card number digit mismatch");
  }
  assert(card.current_balance == 15000 && "Card balance mismatch");
  assert(card.most_recent_transaction_index == 0 && "Card transaction index mismatch");
  assert(card.transactions[card.most_recent_transaction_index].is_valid && "Card transaction[0] validity mismatch");
  assert(card.transactions[card.most_recent_transaction_index].type == TOPUP && "Card transaction[0] type mismatch");
  assert(card.transactions[card.most_recent_transaction_index].value == 10000 && "Card transaction[0] amount mismatch");
  assert(std::strcmp(card.transactions[card.most_recent_transaction_index].description, "MTR") == 0
         && "Card transaction[0] description mismatch");
  assert(card.aavs_amount == 0 && "Card AAVS amount mismatch");

  assert(octopus_deduct(card, 710, "KMB") && "Deduct failed but expected to succeed");
  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == 0 && "Card number digit mismatch");
  }
  assert(card.current_balance == 14290 && "Card balance mismatch");
  assert(card.most_recent_transaction_index == 1 && "Card transaction index mismatch");
  assert(card.transactions[card.most_recent_transaction_index].is_valid && "Card transaction[1] validity mismatch");
  assert(card.transactions[card.most_recent_transaction_index].type == EXPENSE && "Card transaction[1] type mismatch");
  assert(card.transactions[card.most_recent_transaction_index].value == 710 && "Card transaction[1] amount mismatch");
  assert(std::strcmp(card.transactions[card.most_recent_transaction_index].description, "KMB") == 0
         && "Card transaction[1] description mismatch");
  assert(card.aavs_amount == 0 && "Card AAVS amount mismatch");

  assert(octopus_deduct(card, 2900, "American Diner") && "Deduct failed but expected to succeed");
  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == 0 && "Card number digit mismatch");
  }
  assert(card.current_balance == 11390 && "Card balance mismatch");
  assert(card.most_recent_transaction_index == 2 && "Card transaction index mismatch");
  assert(card.transactions[card.most_recent_transaction_index].is_valid && "Card transaction[2] validity mismatch");
  assert(card.transactions[card.most_recent_transaction_index].type == EXPENSE && "Card transaction[2] type mismatch");
  assert(card.transactions[card.most_recent_transaction_index].value == 2900 && "Card transaction[2] amount mismatch");
  assert(std::strcmp(card.transactions[card.most_recent_transaction_index].description, "American Diner") == 0
         && "Card transaction[2] description mismatch");
  assert(card.aavs_amount == 0 && "Card AAVS amount mismatch");

  assert(octopus_deduct(card, 3570, "Starbucks") && "Deduct failed but expected to succeed");
  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == 0 && "Card number digit mismatch");
  }
  assert(card.current_balance == 7820 && "Card balance mismatch");
  assert(card.most_recent_transaction_index == 3 && "Card transaction index mismatch");
  assert(card.transactions[card.most_recent_transaction_index].is_valid && "Card transaction[3] validity mismatch");
  assert(card.transactions[card.most_recent_transaction_index].type == EXPENSE && "Card transaction[3] type mismatch");
  assert(card.transactions[card.most_recent_transaction_index].value == 3570 && "Card transaction[3] amount mismatch");
  assert(std::strcmp(card.transactions[card.most_recent_transaction_index].description, "Starbucks") == 0
         && "Card transaction[3] description mismatch");
  assert(card.aavs_amount == 0 && "Card AAVS amount mismatch");

  assert(octopus_deduct(card, 310, "KMB") && "Deduct failed but expected to succeed");
  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == 0 && "Card number digit mismatch");
  }
  assert(card.current_balance == 7510 && "Card balance mismatch");
  assert(card.most_recent_transaction_index == 4 && "Card transaction index mismatch");
  assert(card.transactions[card.most_recent_transaction_index].is_valid && "Card transaction[4] validity mismatch");
  assert(card.transactions[card.most_recent_transaction_index].type == EXPENSE && "Card transaction[4] type mismatch");
  assert(card.transactions[card.most_recent_transaction_index].value == 310 && "Card transaction[4] amount mismatch");
  assert(std::strcmp(card.transactions[card.most_recent_transaction_index].description, "KMB") == 0
         && "Card transaction[4] description mismatch");
  assert(card.aavs_amount == 0 && "Card AAVS amount mismatch");

  assert(octopus_deduct(card, 2230, "MTR") && "Deduct failed but expected to succeed");
  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == 0 && "Card number digit mismatch");
  }
  assert(card.current_balance == 5280 && "Card balance mismatch");
  assert(card.most_recent_transaction_index == 0 && "Card transaction index mismatch");
  assert(card.transactions[card.most_recent_transaction_index].is_valid && "Card transaction[0] validity mismatch");
  assert(card.transactions[card.most_recent_transaction_index].type == EXPENSE && "Card transaction[0] type mismatch");
  assert(card.transactions[card.most_recent_transaction_index].value == 2230 && "Card transaction[0] amount mismatch");
  assert(std::strcmp(card.transactions[card.most_recent_transaction_index].description, "MTR") == 0
         && "Card transaction[0] description mismatch");
  assert(card.aavs_amount == 0 && "Card AAVS amount mismatch");

  assert(!octopus_deduct(card, 15000, "PARKnShop") && "Deduct succeeded but expected to fail");
  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == 0 && "Card number digit mismatch");
  }
  assert(card.current_balance == 5280 && "Card balance mismatch");
  assert(card.most_recent_transaction_index == 0 && "Card transaction index mismatch");
  assert(card.aavs_amount == 0 && "Card AAVS amount mismatch");

  assert(octopus_topup(card, 50000, "PARKnShop") && "Top-up failed but expected to succeed");
  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == 0 && "Card number digit mismatch");
  }
  assert(card.current_balance == 55280 && "Card balance mismatch");
  assert(card.most_recent_transaction_index == 1 && "Card transaction index mismatch");
  assert(card.transactions[card.most_recent_transaction_index].is_valid && "Card transaction[1] validity mismatch");
  assert(card.transactions[card.most_recent_transaction_index].type == TOPUP && "Card transaction[1] type mismatch");
  assert(card.transactions[card.most_recent_transaction_index].value == 50000 && "Card transaction[1] amount mismatch");
  assert(std::strcmp(card.transactions[card.most_recent_transaction_index].description, "PARKnShop") == 0
         && "Card transaction[1] description mismatch");
  assert(card.aavs_amount == 0 && "Card AAVS amount mismatch");

  assert(octopus_deduct(card, 15000, "PARKnShop") && "Deduct failed but expected to succeed");
  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == 0 && "Card number digit mismatch");
  }
  assert(card.current_balance == 40280 && "Card balance mismatch");
  assert(card.most_recent_transaction_index == 2 && "Card transaction index mismatch");
  assert(card.transactions[card.most_recent_transaction_index].is_valid && "Card transaction[2] validity mismatch");
  assert(card.transactions[card.most_recent_transaction_index].type == EXPENSE && "Card transaction[2] type mismatch");
  assert(card.transactions[card.most_recent_transaction_index].value == 15000 && "Card transaction[2] amount mismatch");
  assert(std::strcmp(card.transactions[card.most_recent_transaction_index].description, "PARKnShop") == 0
         && "Card transaction[2] description mismatch");
  assert(card.aavs_amount == 0 && "Card AAVS amount mismatch");

  OctopusTransaction transaction{false, {}, {}, {}};
  transaction = octopus_get_recent_transaction(card, 0);
  assert(transaction.is_valid && "recent_transaction[0] validity mismatch");
  assert(transaction.type == EXPENSE && "recent_transaction[0] type mismatch");
  assert(transaction.value == 15000 && "recent_transaction[0] amount mismatch");
  assert(std::strcmp(transaction.description, "PARKnShop") == 0 && "recent_transaction[0] description mismatch");

  transaction = {false, {}, {}, {}};
  transaction = octopus_get_recent_transaction(card, 2);
  assert(transaction.is_valid && "recent_transaction[2] validity mismatch");
  assert(transaction.type == EXPENSE && "recent_transaction[2] type mismatch");
  assert(transaction.value == 2230 && "recent_transaction[2] amount mismatch");
  assert(std::strcmp(transaction.description, "MTR") == 0 && "recent_transaction[2] description mismatch");

  transaction = {false, {}, {}, {}};
  transaction = octopus_get_recent_transaction(card, 3);
  assert(transaction.is_valid && "recent_transaction[3] validity mismatch");
  assert(transaction.type == EXPENSE && "recent_transaction[3] type mismatch");
  assert(transaction.value == 310 && "recent_transaction[3] amount mismatch");
  assert(std::strcmp(transaction.description, "KMB") == 0 && "recent_transaction[2] description mismatch");

  transaction = {false, {}, {}, {}};
  transaction = octopus_get_recent_transaction(card, MAX_TRANSACTIONS - 1);
  assert(transaction.is_valid && "recent_transaction[4] validity mismatch");
  assert(transaction.type == EXPENSE && "recent_transaction[4] type mismatch");
  assert(transaction.value == 3570 && "recent_transaction[4] amount mismatch");
  assert(std::strcmp(transaction.description, "Starbucks") == 0 && "recent_transaction[4] description mismatch");
}

void test3() {
  Octopus card{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, DEFAULT_INITIAL_BALANCE, {}, MAX_TRANSACTIONS - 1, 0};
  for (int i{0}; i < MAX_TRANSACTIONS; ++i) {
    card.transactions[i].is_valid = false;
  }

  assert(octopus_register_aavs(card, 50000) && "AAVS registration failed but expected to succeed");

  assert(octopus_topup(card, 10000, "MTR") && "Top-up failed but expected to succeed");
  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == 0 && "Card number digit mismatch");
  }
  assert(card.current_balance == 15000 && "Card balance mismatch");
  assert(card.most_recent_transaction_index == 0 && "Card transaction index mismatch");
  assert(card.transactions[card.most_recent_transaction_index].is_valid && "Card transaction[0] validity mismatch");
  assert(card.transactions[card.most_recent_transaction_index].type == TOPUP && "Card transaction[0] type mismatch");
  assert(card.transactions[card.most_recent_transaction_index].value == 10000 && "Card transaction[0] amount mismatch");
  assert(std::strcmp(card.transactions[card.most_recent_transaction_index].description, "MTR") == 0
         && "Card transaction[0] description mismatch");
  assert(card.aavs_amount == 50000 && "Card AAVS amount mismatch");

  assert(octopus_deduct(card, 710, "KMB") && "Deduct failed but expected to succeed");
  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == 0 && "Card number digit mismatch");
  }
  assert(card.current_balance == 14290 && "Card balance mismatch");
  assert(card.most_recent_transaction_index == 1 && "Card transaction index mismatch");
  assert(card.transactions[card.most_recent_transaction_index].is_valid && "Card transaction[1] validity mismatch");
  assert(card.transactions[card.most_recent_transaction_index].type == EXPENSE && "Card transaction[1] type mismatch");
  assert(card.transactions[card.most_recent_transaction_index].value == 710 && "Card transaction[1] amount mismatch");
  assert(std::strcmp(card.transactions[card.most_recent_transaction_index].description, "KMB") == 0
         && "Card transaction[1] description mismatch");
  assert(card.aavs_amount == 50000 && "Card AAVS amount mismatch");

  assert(octopus_deduct(card, 2900, "American Diner") && "Deduct failed but expected to succeed");
  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == 0 && "Card number digit mismatch");
  }
  assert(card.current_balance == 11390 && "Card balance mismatch");
  assert(card.most_recent_transaction_index == 2 && "Card transaction index mismatch");
  assert(card.transactions[card.most_recent_transaction_index].is_valid && "Card transaction[2] validity mismatch");
  assert(card.transactions[card.most_recent_transaction_index].type == EXPENSE && "Card transaction[2] type mismatch");
  assert(card.transactions[card.most_recent_transaction_index].value == 2900 && "Card transaction[2] amount mismatch");
  assert(std::strcmp(card.transactions[card.most_recent_transaction_index].description, "American Diner") == 0
         && "Card transaction[2] description mismatch");
  assert(card.aavs_amount == 50000 && "Card AAVS amount mismatch");

  assert(octopus_deduct(card, 3570, "Starbucks") && "Deduct failed but expected to succeed");
  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == 0 && "Card number digit mismatch");
  }
  assert(card.current_balance == 7820 && "Card balance mismatch");
  assert(card.most_recent_transaction_index == 3 && "Card transaction index mismatch");
  assert(card.transactions[card.most_recent_transaction_index].is_valid && "Card transaction[3] validity mismatch");
  assert(card.transactions[card.most_recent_transaction_index].type == EXPENSE && "Card transaction[3] type mismatch");
  assert(card.transactions[card.most_recent_transaction_index].value == 3570 && "Card transaction[3] amount mismatch");
  assert(std::strcmp(card.transactions[card.most_recent_transaction_index].description, "Starbucks") == 0
         && "Card transaction[3] description mismatch");
  assert(card.aavs_amount == 50000 && "Card AAVS amount mismatch");

  assert(octopus_deduct(card, 310, "KMB") && "Deduct failed but expected to succeed");
  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == 0 && "Card number digit mismatch");
  }
  assert(card.current_balance == 7510 && "Card balance mismatch");
  assert(card.most_recent_transaction_index == 4 && "Card transaction index mismatch");
  assert(card.transactions[card.most_recent_transaction_index].is_valid && "Card transaction[4] validity mismatch");
  assert(card.transactions[card.most_recent_transaction_index].type == EXPENSE && "Card transaction[4] type mismatch");
  assert(card.transactions[card.most_recent_transaction_index].value == 310 && "Card transaction[4] amount mismatch");
  assert(std::strcmp(card.transactions[card.most_recent_transaction_index].description, "KMB") == 0
         && "Card transaction[4] description mismatch");
  assert(card.aavs_amount == 50000 && "Card AAVS amount mismatch");

  assert(octopus_deduct(card, 2230, "MTR") && "Deduct failed but expected to succeed");
  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == 0 && "Card number digit mismatch");
  }
  assert(card.current_balance == 5280 && "Card balance mismatch");
  assert(card.most_recent_transaction_index == 0 && "Card transaction index mismatch");
  assert(card.transactions[card.most_recent_transaction_index].is_valid && "Card transaction[0] validity mismatch");
  assert(card.transactions[card.most_recent_transaction_index].type == EXPENSE && "Card transaction[0] type mismatch");
  assert(card.transactions[card.most_recent_transaction_index].value == 2230 && "Card transaction[0] amount mismatch");
  assert(std::strcmp(card.transactions[card.most_recent_transaction_index].description, "MTR") == 0
         && "Card transaction[0] description mismatch");
  assert(card.aavs_amount == 50000 && "Card AAVS amount mismatch");

  assert(octopus_deduct(card, 15000, "PARKnShop") && "Deduct failed but expected to succeed");
  for (std::size_t i{0}; i < NUM_DIGITS; ++i) {
    assert(card.digits[i] == 0 && "Card number digit mismatch");
  }
  assert(card.current_balance == 40280 && "Card balance mismatch");
  assert(card.most_recent_transaction_index == 2 && "Card transaction index mismatch");
  assert(card.transactions[card.most_recent_transaction_index - 1].is_valid && "Card transaction[1] validity mismatch");
  assert(card.transactions[card.most_recent_transaction_index - 1].type == TOPUP
         && "Card transaction[1] type mismatch");
  assert(card.transactions[card.most_recent_transaction_index - 1].value == 50000
         && "Card transaction[1] amount mismatch");
  assert(std::strcmp(card.transactions[card.most_recent_transaction_index - 1].description, "AAVS") == 0
         && "Card transaction[1] description mismatch");
  assert(card.transactions[card.most_recent_transaction_index].is_valid && "Card transaction[2] validity mismatch");
  assert(card.transactions[card.most_recent_transaction_index].type == EXPENSE && "Card transaction[2] type mismatch");
  assert(card.transactions[card.most_recent_transaction_index].value == 15000 && "Card transaction[2] amount mismatch");
  assert(std::strcmp(card.transactions[card.most_recent_transaction_index].description, "PARKnShop") == 0
         && "Card transaction[2] description mismatch");
  assert(card.aavs_amount == 50000 && "Card AAVS amount mismatch");

  OctopusTransaction transaction{false, {}, {}, {}};
  transaction = octopus_get_recent_transaction(card, 0);
  assert(transaction.is_valid && "recent_transaction[0] validity mismatch");
  assert(transaction.type == EXPENSE && "recent_transaction[0] type mismatch");
  assert(transaction.value == 15000 && "recent_transaction[0] amount mismatch");
  assert(std::strcmp(transaction.description, "PARKnShop") == 0 && "recent_transaction[0] description mismatch");

  transaction = {false, {}, {}, {}};
  transaction = octopus_get_recent_transaction(card, 2);
  assert(transaction.is_valid && "recent_transaction[2] validity mismatch");
  assert(transaction.type == EXPENSE && "recent_transaction[2] type mismatch");
  assert(transaction.value == 2230 && "recent_transaction[2] amount mismatch");
  assert(std::strcmp(transaction.description, "MTR") == 0 && "recent_transaction[2] description mismatch");

  transaction = {false, {}, {}, {}};
  transaction = octopus_get_recent_transaction(card, 3);
  assert(transaction.is_valid && "recent_transaction[3] validity mismatch");
  assert(transaction.type == EXPENSE && "recent_transaction[3] type mismatch");
  assert(transaction.value == 310 && "recent_transaction[3] amount mismatch");
  assert(std::strcmp(transaction.description, "KMB") == 0 && "recent_transaction[2] description mismatch");

  transaction = {false, {}, {}, {}};
  transaction = octopus_get_recent_transaction(card, MAX_TRANSACTIONS - 1);
  assert(transaction.is_valid && "recent_transaction[4] validity mismatch");
  assert(transaction.type == EXPENSE && "recent_transaction[4] type mismatch");
  assert(transaction.value == 3570 && "recent_transaction[4] amount mismatch");
  assert(std::strcmp(transaction.description, "Starbucks") == 0 && "recent_transaction[4] description mismatch");
}

const TestCaseFnT test_suite[]{test1, test2, test3};
}  // namespace

bool run_test(unsigned int test_case_index) {
  const std::size_t test_suite_size{sizeof(test_suite) / sizeof(test_suite[0])};

  if (test_case_index > test_suite_size) {
    return false;
  }

  if (test_case_index == ALL_TESTS) {
    for (unsigned int i{1}; i <= test_suite_size; ++i) {
      run_test(i);
    }
    return true;
  }

  std::cout << ">>> Running Test Case " << test_case_index << std::endl;
  test_suite[test_case_index - 1]();
  std::cout << ">>> Completed Test Case " << test_case_index << std::endl;
  return true;
}
