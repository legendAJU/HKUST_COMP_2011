#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

#include "helper.h"
#include "octopus.h"
#include "test.h"

namespace {
/**
 * @brief Input character that is always recognized as an exit command.
 */
const char MAGIC_ESCAPE_CHAR{'x'};

/**
 * @brief Terminates the current program if an 'x' character is received from input.
 *
 * If the first character of input is 'x', prints a message and exits the program.
 *
 * @param input The input string to check for the escape character.
 */
void check_escape_input(const char* input) {
  if (input[0] == 'x') {
    std::cout << MAGIC_ESCAPE_CHAR << " received - Terminating program!" << std::endl;
    std::exit(EXIT_SUCCESS);
  }
}

/**
 * @brief Resets std::cin by clearing all failure state flags and consuming the remainder of the buffer.
 *
 * If std::cin is in a failed state, this function clears the state and ignores the rest of the input line.
 */
void reset_cin() {
  if (!std::cin) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

/**
 * @brief Interactive prompt for making a transaction on the given Octopus card.
 *
 * Prompts the user for transaction amount and description, then performs the transaction.
 *
 * @param card Reference to the Octopus card to perform the transaction on.
 */
void make_transaction(Octopus& card) {
  // Read the amount string from `std::cin`
  char amt_str[AMOUNT_STR_MAX_LENGTH]{};
  while (!std::cin || std::strlen(amt_str) == 0) {
    reset_cin();
    std::cout << "Enter the transaction amount (positive for top-up, negative for expense): ";
    if (!std::cin.getline(amt_str, AMOUNT_STR_MAX_LENGTH)) {
      std::cout << "Error: Input exceeded buffer size " << AMOUNT_STR_MAX_LENGTH << '.' << std::endl;
      continue;
    }
  }

  // Read the description string from `std::cin`
  char description[MAX_DATA_LENGTH]{};
  while (!std::cin || std::strlen(description) == 0) {
    reset_cin();
    std::cout << "Enter the transaction description: ";
    if (!std::cin.getline(description, MAX_DATA_LENGTH)) {
      std::cout << "Error: Input exceeded buffer size " << MAX_DATA_LENGTH << '.' << std::endl;
      continue;
    }
  }

  // Check whether the amount string implies an exit command
  // We don't check if description == "x", because a transaction description may be "x"
  check_escape_input(amt_str);

  // Parse the amount string as the transaction value in cents
  int amount{};
  if (!parse_dollar_input_as_cents(amt_str, amount)) {
    std::cout << "Error: Unable to read transaction amount " << amt_str << " as an integer." << std::endl;
    return;
  }

  // Perform the transaction
  bool success{};
  if (amount > 0) {
    success = octopus_topup(card, static_cast<unsigned int>(amount), description);
  } else {
    success = octopus_deduct(card, static_cast<unsigned int>(-amount), description);
  }

  if (success) {
    std::cout << "Successfully performed transaction of value " << (amount < 0 ? "-" : "") << '$'
              << cents_to_dollars(std::abs(amount)) << '.' << std::endl;
  } else {
    std::cout << "Failed to perform transaction." << std::endl;
  }
}

/**
 * @brief Interactive prompt for retrieving and displaying a transaction from the Octopus card.
 *
 * Prompts the user for the transaction index and displays the transaction details.
 *
 * @param card Reference to the Octopus card to retrieve the transaction from.
 */
void get_transaction(const Octopus& card) {
  // Read the index string from `std::cin`
  char index_str[UINT_STR_MAX_LENGTH]{};
  while (!std::cin || std::strlen(index_str) == 0) {
    reset_cin();
    std::cout << "Enter the index of the transaction to output (0 for most recent): ";
    if (!std::cin.getline(index_str, UINT_STR_MAX_LENGTH)) {
      std::cout << "Error: Input exceeded buffer size " << UINT_STR_MAX_LENGTH << '.' << std::endl;
      continue;
    }
  }

  // Check whether the index string implies an exit command
  check_escape_input(index_str);

  // Parse the index string as the transaction index to retrieve
  unsigned int index{};
  if (!parse_uint(index_str, index)) {
    std::cout << "Error: Unable to read transaction index " << index_str << " as an unsigned integer." << std::endl;
    return;
  }

  // Retrieve the transaction
  const OctopusTransaction transaction{octopus_get_recent_transaction(card, index)};
  if (!transaction.is_valid) {
    std::cout << "Error: Transaction at index " << index << " is invalid." << std::endl;
    return;
  }

  std::cout << "Transaction Details:" << std::endl;
  std::cout << "  Amount: " << (transaction.type == EXPENSE ? "-" : "") << '$'
            << cents_to_dollars(static_cast<int>(transaction.value)) << std::endl;
  std::cout << "  Description: " << transaction.description << std::endl;
}

/**
 * @brief Interactive prompt for registering AAVS (Automatic Add Value Service) for the Octopus card.
 *
 * Prompts the user for the initial AAVS amount and registers it to the card.
 *
 * @param card Reference to the Octopus card to register AAVS for.
 */
void register_aavs(Octopus& card) {
  // Read the amount string from `std::cin`
  char amt_str[AMOUNT_STR_MAX_LENGTH]{};
  while (!std::cin || std::strlen(amt_str) == 0) {
    reset_cin();
    std::cout << "Enter initial amount for AAVS: ";
    if (!std::cin.getline(amt_str, AMOUNT_STR_MAX_LENGTH)) {
      std::cout << "Error: Input exceeded buffer size " << AMOUNT_STR_MAX_LENGTH << '.' << std::endl;
      continue;
    }
  }

  // Check whether the amount string implies an exit command
  check_escape_input(amt_str);

  // Parse the amount string as the AAVS amount
  unsigned int aavs_amount{};
  if (!parse_dollar_input_as_cents(amt_str, aavs_amount)) {
    std::cout << "Error: Unable to read AAVS amount " << amt_str << " as a floating-point number." << std::endl;
    return;
  }

  if (octopus_register_aavs(card, aavs_amount)) {
    std::cout << "Successfully registered AAVS with amount $" << cents_to_dollars(static_cast<int>(aavs_amount)) << '.'
              << std::endl;
  } else {
    std::cout << "Failed to register for AAVS." << std::endl;
  }
}
}  // namespace

int main(int argc, const char* argv[]) {
  if (argc == 2) {
    unsigned int test_case_index{};
    if (!parse_uint(argv[1], test_case_index)) {
      std::cout << "Error: Invalid test case " << argv[1] << std::endl;
      return EXIT_FAILURE;
    }

    if (!run_test(test_case_index)) {
      std::cout << "Error: Invalid test case " << argv[1] << std::endl;
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }

  std::cout << std::fixed << std::setprecision(2);

  std::cout << "Welcome to the Octopus Card Simulator!" << std::endl;

  char digit_str[NUM_DIGITS + 1]{};
  while (true) {
    reset_cin();
    std::cout << "Enter the number of your Octopus Card: ";
    if (std::cin.getline(digit_str, NUM_DIGITS + 1) && std::strlen(digit_str) == NUM_DIGITS) {
      break;
    }
    std::cout << "Error: Card number does not contain " << NUM_DIGITS << " digits!" << std::endl;
  }

  char balance_str[AMOUNT_STR_MAX_LENGTH];
  while (true) {
    reset_cin();
    std::cout << "Enter the initial balance of your Octopus Card (default=$50): ";
    if (std::cin.getline(balance_str, AMOUNT_STR_MAX_LENGTH)) {
      break;
    }

    std::cout << "Error: Input exceeded buffer size " << AMOUNT_STR_MAX_LENGTH << '.' << std::endl;
  }

  check_escape_input(digit_str);
  check_escape_input(digit_str);

  short digits[NUM_DIGITS];
  const int numDigits{str_to_short_array(digit_str, digits, NUM_DIGITS)};
  if (numDigits != NUM_DIGITS) {
    std::cout << "Error: Card number does not contain " << NUM_DIGITS << " digits!" << std::endl;
    return EXIT_FAILURE;
  }

  int balance{DEFAULT_INITIAL_BALANCE};
  if (!parse_dollar_input_as_cents(balance_str, balance)) {
    std::cout << "Error: Unable to read initial balance " << balance_str << " as a floating-point number." << std::endl;
    return EXIT_FAILURE;
  }

  Octopus octopus{};
  if (!octopus_init(octopus, digits, balance)) {
    std::cout << "Failed to initialize Octopus card!" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Initialized Octopus Card with the following attributes:" << std::endl;
  std::cout << "  Card Number: ";
  for (int i{0}; i < NUM_DIGITS; ++i) {
    std::cout << octopus.digits[i];
  }
  std::cout << std::endl;
  std::cout << "  Balance: " << (octopus.current_balance < 0 ? "-" : "") << '$'
            << cents_to_dollars(std::abs(octopus.current_balance)) << std::endl;
  std::cout << "  AAVS Amount: $" << octopus.aavs_amount << std::endl;

  char option_str[]{'0', '\0'};
  const char& option{option_str[0]};
  while (option != 'x') {
    std::cout << "Please select an option:" << std::endl;
    std::cout << "  1. Make a Transaction" << std::endl;
    std::cout << "  2. Print a Recent Transaction" << std::endl;
    std::cout << "  3. Register for AAVS" << std::endl;
    std::cout << "  p. Print Card Information" << std::endl;
    std::cout << "  x. Exit the Program" << std::endl;
    std::cout << "Selection: ";
    if (!std::cin.getline(option_str, 2)) {
      std::cout << "Unknown option - Please try again." << std::endl;
      reset_cin();
      continue;
    }

    switch (option) {
      case '1':
        make_transaction(octopus);
        break;
      case '2':
        get_transaction(octopus);
        break;
      case '3':
        register_aavs(octopus);
        break;
      case 'p':
        std::cout << "Octopus Card Information:" << std::endl;
        std::cout << "  Balance: " << (octopus.current_balance < 0 ? "-" : "") << '$'
                  << cents_to_dollars(std::abs(octopus.current_balance)) << std::endl;
        std::cout << "  AAVS Amount: $" << cents_to_dollars(static_cast<int>(octopus.aavs_amount)) << std::endl;
        break;
      case 'x':
        std::cout << "Exiting program..." << std::endl;
        break;
      default:
        std::cout << "Unknown option " << option << " - Please try again" << std::endl;
    }
  }
}
