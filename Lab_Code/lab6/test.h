#ifndef TEST_H
#define TEST_H

using TestCaseFnT = void (*)();

const unsigned int ALL_TESTS{0};

bool run_test(unsigned int test_case_index = ALL_TESTS);

#endif  // TEST_H
