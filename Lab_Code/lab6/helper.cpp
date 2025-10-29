#include "helper.h"

#include <cerrno>
#include <cmath>
#include <cstring>

namespace {
const int BASE_10{10};

bool read_double_input(const char str[AMOUNT_STR_MAX_LENGTH], double& amount) {
  char* parsed{};
  amount = strtod(str, &parsed);
  return amount != HUGE_VAL && parsed != str;
}
}  // namespace

double cents_to_dollars(int cent_amt) {
  return static_cast<double>(cent_amt) / static_cast<double>(DOLLAR_CENT_RATIO);
}

int dollars_to_cents(double dollar_amt) {
  return static_cast<int>(dollar_amt * static_cast<double>(DOLLAR_CENT_RATIO));
}

bool parse_dollar_input_as_cents(const char str[AMOUNT_STR_MAX_LENGTH], int& amount) {
  if (strlen(str) == 0) {
    return true;
  }

  double amount_fp{};
  if (!read_double_input(str, amount_fp)) {
    return false;
  }
  amount = dollars_to_cents(amount_fp);

  return true;
}

bool parse_dollar_input_as_cents(const char str[AMOUNT_STR_MAX_LENGTH], unsigned int& amount) {
  if (strlen(str) == 0) {
    return true;
  }

  double amount_fp{};
  if (!read_double_input(str, amount_fp)) {
    return false;
  }
  amount = static_cast<unsigned int>(dollars_to_cents(amount_fp));

  return true;
}

bool parse_uint(const char str[UINT_STR_MAX_LENGTH], unsigned int& num) {
  char* parsed{};
  num = static_cast<unsigned int>(strtoul(str, &parsed, BASE_10));
  if (parsed == str || errno == ERANGE) {
    errno = 0;
    return false;
  }

  return true;
}

int str_to_short_array(const char str[NUM_DIGITS + 1], short digits[NUM_DIGITS], int numDigits) {
  int len{0};
  for (len = 0; len < numDigits; ++len) {
    if (str[len] == '\0') {
      break;
    }
    if (str[len] < '0' || str[len] > '9') {
      return -1;  // Invalid character
    }
    digits[len] = static_cast<short>(str[len] - '0');
  }

  if (str[len] != '\0') {
    return -1;  // Input string is longer than numDigits
  }

  return len;
}
