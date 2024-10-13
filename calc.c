#include "calc.h"
#include "input.h"

void calc_FSM(calc_t* calcPtr, char in){

  // Regardless of FSM state, Reset and BaseToggle are handled the same way
  if(in == INPUT_RESET){
    calcPtr->state     = State_InputOperand;
    calcPtr->stackPtr  = 0;
    calcPtr->accum     = 0;
    calcPtr->operand   = 0;
    calcPtr->operation = &calc_performAdd;
  }
  else if(in == INPUT_BASE_TOGGLE) {
    calcPtr->base = (calcPtr->base == base16) ? base10 : base16; // toggle base
  }

  else {
    switch(calcPtr->state) {
      case State_InputOperand:
        calc_handleInputOperand(calcPtr, in);
        break;
      case State_InputOperation:
        calc_handleInputOperation(calcPtr, in);
        break;
      case State_OpenFrame:
        calc_handleOpenFrame(calcPtr, in);
        break;
      case State_CloseFrame:
        calc_handleCloseFrame(calcPtr, in);
  
      default:
        // TODO: Dox user in case of invalid state
        break;
    }
  }
  
  return;
}

void calc_handleInputOperand(calc_t* calcPtr, char in) {
  // If input is a valid number in current base, add a new digit
  // to the end of the operand (multiply by 10 or 16 and add new digit)
  if(input_isNumeric(in) && (input_toNumber(in) < calcPtr->base)){
    calcPtr->operand *= calcPtr->base;
    calcPtr->operand += input_toNumber(in);
  }

  // Update accumulator with value of operation(accum, operand), then set new
  // operation and operand
  else if(input_isLogicOp(in)){
    calcPtr->state = State_InputOperation;
    calcPtr->accum = (*(calcPtr->operation))(calcPtr->accum, calcPtr->operand);
    calcPtr->operand = 0;
    calc_updateOperation(calcPtr, in); // Update function ptr
  }

  else {
    switch(in) {
      case INPUT_PLUS_MINUS:
        calcPtr->operand *= -1;
        break;
      case INPUT_EQUALS:
        // consider adding an additional state for repeated EQUALS inputs; for now, update accum and reset operand/operation
        calcPtr->accum = (*(calcPtr->operation))(calcPtr->accum, calcPtr->operand);
        calcPtr->operand = 0;
        calcPtr->operation = &calc_performAdd;
        break;
      case INPUT_CLOSE_P:
        if(calcPtr->stackPtr > 0) {
          calcPtr->state = State_CloseFrame;
          calcPtr->stackPtr--;
          calcPtr->operand = (*(calcPtr->operation))(calcPtr->accum, calcPtr->operand);
          calcPtr->accum = calcPtr->stack[calcPtr->stackPtr].accum;
          calcPtr->operation = calcPtr->stack[calcPtr->stackPtr].operation;
        }
        break;


      default:
        break;
    }
  }

  return;
}

void calc_handleInputOperation(calc_t* calcPtr, char in);
void calc_handleOpenFrame(calc_t* calcPtr, char in);
void calc_handleCloseFrame(calc_t* calcPtr, char in);

// Helper for updating operation function ptr
void calc_updateOperation(calc_t* calcPtr, char in){
  switch(in) {
    case INPUT_ADD:
      calcPtr->operation = &calc_performAdd;
      break;
      
    case INPUT_SUBTRACT:
      calcPtr->operation = &calc_performSubtract;
      break;
      
    case INPUT_MULTIPLY:
      calcPtr->operation = &calc_performMultiply;
      break;
      
    case INPUT_DIVIDE:
      calcPtr->operation = &calc_performDivide;
      break;
      
    case INPUT_SHIFT_L:
      calcPtr->operation = &calc_performShiftLeft;
      break;
      
    case INPUT_SHIFT_R:
      calcPtr->operation = &calc_performShiftRight;
      break;
      
    case INPUT_AND:
      calcPtr->operation = &calc_performAnd;
      break;
      
    case INPUT_OR:
      calcPtr->operation = &calc_performOr;
      break;
      
    case INPUT_NOT:
      calcPtr->operation = &calc_performNot;
      break;
      
    case INPUT_NAND:
      calcPtr->operation = &calc_performNand;
      break;
      
    case INPUT_NOR:
      calcPtr->operation = &calc_performNor;
      break;
      
    case INPUT_XOR:
      calcPtr->operation = &calc_performXor;
      break;
      
    case INPUT_MOD:
      calcPtr->operation = &calc_performMod;
      break;

    default:
      break;
  }

  return;
}
