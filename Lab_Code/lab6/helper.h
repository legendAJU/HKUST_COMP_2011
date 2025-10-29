#ifndef HELPER_H
#define HELPER_H

/**
 * @brief Maximum input length of the balance string.
 *
 * The string consists of at most 4 integral digits, a decimal point, 2 decimal digits, and a `\0`
 * at the end of the string.
 */
const int AMOUNT_STR_MAX_LENGTH{10};

/**
 * @brief The ratio of dollar to cents.
 */
const int DOLLAR_CENT_RATIO{100};

/**
 * @brief The maximum length of a string representing an `unsigned int`.
 */
const int UINT_STR_MAX_LENGTH{11};

/**
 * @brief The number of digits of the Octopus card number.
 */
const int NUM_DIGITS{10};

/**
 * @brief Converts an amount in cents to dollars.
 *
 * @param cent_amt Amount in cents.
 * @return Equivalent amount in dollars.
 */
double cents_to_dollars(int cent_amt);

/**
 * @brief Converts an amount in dollars to cents.
 *
 * @param dollar_amt Amount in dollars.
 * @return Equivalent amount in cents.
 */
int dollars_to_cents(double dollar_amt);

/**
 * @brief Parses a dollar input string as cents and stores the result in an integer.
 *
 * @param str Input string representing a dollar amount.
 * @param amount Reference to integer where the parsed cent value will be stored.
 * @return True if parsing was successful, false otherwise.
 */
bool parse_dollar_input_as_cents(const char str[AMOUNT_STR_MAX_LENGTH], int& amount);

/**
 * @brief Parses a dollar input string as cents and stores the result in an unsigned integer.
 *
 * @param str Input string representing a dollar amount.
 * @param amount Reference to unsigned integer where the parsed cent value will be stored.
 * @return True if parsing was successful, false otherwise.
 */
bool parse_dollar_input_as_cents(const char str[AMOUNT_STR_MAX_LENGTH], unsigned int& amount);

/**
 * @brief Parses an unsigned integer from a string.
 *
 * @param str Input string representing an unsigned integer.
 * @param num Reference to unsigned integer where the parsed value will be stored.
 * @return True if parsing was successful, false otherwise.
 */
bool parse_uint(const char str[UINT_STR_MAX_LENGTH], unsigned int& num);

/**
 * @brief Reads `str` as a sequence of numbers, converting them into `short`s and writing them into the `digits` array,
 * and returning the number of digits read.
 *
 * Examples:
 *
 * ```
 * short digits[10] = {};
 * int digitsRead = str_to_short_array("1", digits, 10);
 * // digitsRead = 1
 * // digits = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
 *
 * digitsRead = str_to_short_array("123456789", digits, 10);
 * // digitsRead = 9
 * // digits = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
 *
 * digitsRead = str_to_short_array("abcdefghi", digits, 10);
 * // digitsRead = -1
 * // digits = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
 * ```
 */
int str_to_short_array(const char str[NUM_DIGITS + 1], short digits[NUM_DIGITS], int numDigits);

#endif  // HELPER_H
