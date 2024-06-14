/**
 *  Header file for hc.c 
 */

// Imports
#include "stdint.h"

// Datatypes
typedef uint16_t unib4_t; // unsigned 4-nibble (16-bit) number
typedef uint32_t unib8_t; // unsigned 8-nibble (32-bit) number 
typedef enum {            // operator type (value = ASCII)
  ADD = 43,  
  SUB = 45, 
  MUL = 42, 
  DIV = 47, 
  ERR = 0   // if invalid
} uhex_operator;

// char* -> unib4_t
// + Returns 0 on success, non-zero on failure
// |-> A return value of 1 indicates overflow (i.e. more than 4 nibbles)
// + Converted string is stored in *h on success
int parse_unib4(char* s, unib4_t* h);

// char* -> uhex_operator
// + Returns ADD/SUB/MUL/DIV on success, ERR on failure 
uhex_operator parse_operator(char* arg);

// Calculate 
// + Returns 0 on success, non-zero on failure
// + Calculated value is stored in *c on success
// |-> In case of success, actual value is stored 
// |-> In case of failure, 0 is stored
int calculate(unib4_t a, uhex_operator op, unib4_t b, unib8_t* c);

// unib8_t -> char*
// + Returns a string representation of a unib8
// + Beware that this allocates a new string!
// |->  The return value of this function needs to 
//      be freed!
char* unib8_str(unib8_t c);
