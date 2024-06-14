// Imports
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "hc.h"


// char* -> unib4_t
int parse_unib4(char* s, unib4_t* h) {
  int rv = 0;
  
  int i = 0;
  for (char* c = (s+i); (*c) != '\0'; c = (s+(++i))) {
    // + First, shift *h to the left by 4 
    // |-> on first iteration, this does nothing (0 << 4 = 0) 
    // |-> on subsequent iterations, this multiplies the running total by 16, 
    //     allowing us to have a running calculation
    // + However, this is also where overflow happens, so check i to inform the caller (via rv)
    *h = *h << 4;
    rv = (i <= 4) ? 0 : 1;

    // Then, convert char to decimal number, and add to *h
    switch (*c) {
      case '0':
        *h += 0;
        break;
      case '1':
        *h += 1;
        break;
      case '2':
        *h += 2;
        break;
      case '3':
        *h += 3;
        break;
      case '4':
        *h += 4;
        break;
      case '5':
        *h += 5;
        break;
      case '6':
        *h += 6;
        break;
      case '7':
        *h += 7;
        break;
      case '8':
        *h += 8;
        break;
      case '9':
        *h += 9;
        break;
      case 'A':
      case 'a':
        *h += 10;
        break;
      case 'B':
      case 'b':
        *h += 11;
        break;
      case 'C':
      case 'c':
        *h += 12;
        break;
      case 'D':
      case 'd':
        *h += 13;
        break;
      case 'E':
      case 'e':
        *h += 14;
        break;
      case 'F':
      case 'f':
        *h += 15;
        break;
      default:
        rv = 2;
        break;
    }
  }

  // return rv, to inform caller 
  return rv;
}

// char* -> uhex_operator
uhex_operator parse_operator(char* arg) {
  //  || *arg == '\0'
  if (arg == NULL) {
    return ERR;
  }

  switch (*arg) {
    case '+':
      return ADD;
    case '-':
      return SUB;
    case '*':
      return MUL;
    case '/':
      return DIV;
    default:
      return ERR;
  }
}

// Calculate 
int calculate(unib4_t a, uhex_operator op, unib4_t b, unib8_t* c) {
  int rv = 0;

  switch (op) {
    case ADD:
      *c = a + b;
      break;
    case SUB:
      *c = (a > b) ? a - b : 0;
      break;
    case MUL:
      *c = ((unib8_t) a) * ((unib8_t) b);
      break;
    case DIV:
      if (b == 0) {
        *c = 0;
        rv = 2;
      } else {
        *c = a / b;
      }
      break;
    default:
      *c = 0;
      rv = 1; 
      break;
  }

  return rv;
}

// unib8_t -> char*
// !! This function allocates a new string that must be freed !!
char* unib8_str(unib8_t c) {
  // Only need to allocate 8 chars, since only 8 nibs in datatype
  char* s = (char*) malloc(8);
  memset(s, '0', 8);
  
  // Calculate nibbles right-to-left
  for (int i = 7; i >= 0; --i) {
    uint8_t rem = c % 16;
    c = c >> 4;

    // 0-9 case, ASCII 0 = 48
    if (rem < 10) {
      *(s+i) = (48 + rem);
    }
    // A-F case, ASCII A = 65
    else if (rem < 16) {
      *(s+i) = (65 + rem);
    }
  }

  return s;
}
