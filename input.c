#include "input.h"

// Right now both these functions depend on 0-9 inputs, A-F inputs being contiguous
// If not then we have to switch to switch-case statements (L)

int input_isNumeric(char in){
  return (  ((in >= INPUT_0) && (in <= INPUT_9))
         || ((in >= INPUT_A) && (in <= INPUT_F)) );
}

// Convert input character to actual number
// Again if char values are not contiguous we must rewrite to switch-case
int input_toNumber(char in){
  if((in >= INPUT_0) && (in <= INPUT_9))
    return (in - INPUT_0); // subtract numeric value of character '0'

  else if((in >= INPUT_A) && (in <= INPUT_F))
    return (in - INPUT_A + 10); // subtract numeric value of character '10' but add 10 back in

  else
    return -1; 
}

// Check if input character corresponds to logical op
int input_isLogic(char in){
  switch(in) {
    case INPUT_ADD:
    case INPUT_SUBTRACT:
    case INPUT_MULTIPLY:
    case INPUT_DIVIDE:
    case INPUT_SHIFT_L:
    case INPUT_SHIFT_R:
    case INPUT_AND:
    case INPUT_OR:
    case INPUT_NOT:
    case INPUT_NAND:
    case INPUT_NOR:
    case INPUT_XOR:
    case INPUT_MOD:
      return 1;
      
    default:
      break;
  }

  return 0;
}
