/**
 *  Tests for hc.h/c 
 */
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"
#include "hc.h"


/**
 *  Parsing unib4_t tests 
 */
typedef struct parse_unib4_testcase {
  char* arg;
  unib4_t exp;
} parse_unib4_case_t;

#define NUM_PARSE_UNIB4_TESTCASES 10
parse_unib4_case_t parse_unib4_testcases[NUM_PARSE_UNIB4_TESTCASES] = {
  {"0123",  291},
  {"4567",  17767},
  {"89ab",  35243},
  {"cdef",  52719},
  {"0000",  0},
  {"FFFF",  65535},
  {"0FFFF", 65535},
  {"10000", 0},
  {"ABCD",  43981},
  {"E145",  57669} 
};

/**
 *  Parsing uhex_operator tests 
 */
typedef struct parse_op_testcase {
  char* arg;
  uhex_operator exp;
} parse_op_case_t;

#define NUM_PARSE_OPERATOR_TESTCASES 8
parse_op_case_t parse_op_testcases[NUM_PARSE_OPERATOR_TESTCASES] = {
  {"+",  ADD},
  {"-",  SUB},
  {"*",  MUL},
  {"/",  DIV},
  {"+-", ADD},
  {"",   ERR},
  {"_",  ERR},
  {" ",  ERR},
};

/**
 *  Calculator tests 
 */
typedef struct calc_testcase {
  uhex_operator op;
  unib4_t a;
  unib4_t b;
  unib8_t exp;
} calc_case_t;

#define NUM_CALCULATOR_TESTCASES 16 
calc_case_t calc_testcases[NUM_CALCULATOR_TESTCASES] = {
  {ADD, 1, 1, 2},
  {ADD, 0, 1, 1},
  {ADD, 1, 0, 1},
  {ADD, 65535, 65535, 131070},
  {SUB, 5, 2, 3},
  {SUB, 0, 1, 0},
  {MUL, 0, 1, 0},
  {MUL, 1, 1, 1},
  {MUL, 2, 2, 4},
  {MUL, 65535, 65535, 4294836225},
  {DIV, 2, 1, 2},
  {DIV, 12, 4, 3},
  {DIV, 1, 0, 0},
  {DIV, 23, 4, 5},
  {ERR, 0, 0, 0} 
};


/**
 *  Test suites
 */
int suite_parse_unib4() {
  int passed = 0;
  printf("Testing parse_unib4()...\n");

  for (int c = 0; c < NUM_PARSE_UNIB4_TESTCASES; ++c) {
    parse_unib4_case_t testcase = parse_unib4_testcases[c];
    unib4_t act = 0;
    parse_unib4(testcase.arg, &act);

    if (act == testcase.exp) {
      ++passed;
    } else {
      printf("Test case #%d failed\nExpected: %d, actual: %d\n", c+1, testcase.exp, act);
    }
  }

  printf("Passed %d/%d tests for parse_unib4()\n", passed, NUM_PARSE_UNIB4_TESTCASES);
  return passed;
}

int suite_parse_ops() {
  int passed = 0;
  printf("Testing parse_operator()...\n");

  for (int c = 0; c < NUM_PARSE_OPERATOR_TESTCASES; ++c) {
    parse_op_case_t testcase = parse_op_testcases[c];
    uhex_operator act = ERR;
    act = parse_operator(testcase.arg);

    if (act == testcase.exp) {
      ++passed;
    } else {
      printf("Test case #%d failed\nExpected: %c, actual: %c\n", c+1, testcase.exp, act);
    }
  }

  printf("Passed %d/%d tests for parse_operator()\n", passed, NUM_PARSE_OPERATOR_TESTCASES);
  return passed;
}

int suite_calc() {
  int passed = 0;
  printf("Testing calculate()...\n");

  for (int c = 0; c < NUM_CALCULATOR_TESTCASES; ++c) {
    calc_case_t testcase = calc_testcases[c];
    unib8_t act = 0;
    calculate(testcase.a, testcase.op, testcase.b, &act);

    if (act == testcase.exp) {
      ++passed;
    } else {
      char* s_exp = unib8_str(testcase.exp); 
      char* s_act = unib8_str(act); 
      printf("Test case #%d failed\nExpected: %s (%d), actual: %s (%d)\n", c+1, s_exp, testcase.exp, s_act, act);
      free(s_exp);
      free(s_act);
    }
  }

  printf("Passed %d/%d tests for calculate()\n", passed, NUM_CALCULATOR_TESTCASES);
  return passed;
}

int suite_all() {
  int passed = 0;
  int total  = 0;
  printf("Testing all...\n");
  
  passed += suite_parse_unib4();
  total  += NUM_PARSE_UNIB4_TESTCASES;
  passed += suite_parse_ops();
  total  += NUM_PARSE_OPERATOR_TESTCASES;
  passed += suite_calc();
  total  += NUM_CALCULATOR_TESTCASES;

  printf("Passed %d of %d tests overall\n", passed, total);
  return passed;
}


/** 
 *  Main function 
 */
int main(int argc, char** argv) {
  suite_all();
  return 0;
}
