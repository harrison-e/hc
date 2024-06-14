/**
 *  + In short, this is a two-operand, infix-notation hexadecimal calculator.
 *  + This program takes in a hex number, an operator, and another hex number, and produces the result.
 *  |-> Hex numbers are formatted as a string, with max length of TODO
 *  |-> Operators are: +, -, *, / 
 *  
 *  + For now, this program is super simple. There's room to make it into a full-fledged calculator (fledgling compiler).
 */
const char* const USAGE = "Usage: ./hc <0x operand> <+|-|*|/> <0x operand>\n";

// Imports
#include "hc.h"
#include "stdio.h"
#include "stdlib.h"


// Main function
int main(int argc, char** argv) {
  // for now, only 4 arguments works (name, operand, operator, operand)
  if (argc != 4) {
    char* comparison = (argc < 4) ? "few" : "many";
    fprintf(stderr, "Too %s arguments!\n%s", comparison, USAGE);
    return -1;
  }
  
  int rv = 0;

  // Parse first operand
  unib4_t a = 0;
  rv = parse_unib4(argv[1], &a);
  if (rv != 0) {
    if (rv == 1) {
      fprintf(stdout, "WARNING: Overflow detected on first operand ( %s )!\n", argv[1]);
    } else {
      fprintf(stderr, "Could not parse first operand \"%s\"\n%s", argv[1], USAGE);
      return -1;
    }
  }

  // Parse operator 
  uhex_operator op = ERR;
  op = parse_operator(argv[2]);
  if (op == ERR) {
    fprintf(stderr, "Could not parse operator \"%s\"\n%s", argv[2], USAGE);
  }

  // Parse second operand
  unib4_t b = 0;
  rv = parse_unib4(argv[3], &b);
  if (rv != 0) {
    if (rv == 1) {
      fprintf(stdout, "WARNING: Overflow detected on second operand ( %s )!\n", argv[3]);
    } else {
      fprintf(stderr, "Could not parse second operand \"%s\"\n%s", argv[3], USAGE);
      return -1;
    }
  }

  // Calculate result
  unib8_t c = 0;
  rv = calculate(a, op, b, &c);
  if (rv != 0) {
    fprintf(stderr, "Could not calculate %s %s %s!\n%s", argv[1], argv[2], argv[3], USAGE);
    return -1;
  } else {
    char* ans = unib8_str(c);
    fprintf(stdout, "%s\n", ans);
    free(ans);
    return 0;
  }
}
