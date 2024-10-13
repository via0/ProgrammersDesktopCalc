// Short for calculator - just slang - no need to worry

#ifndef CALC_H_
#define CALC_H_

#define CALC_STACK_SIZE 10 // I should be based and use the entire hardware stack space

typedef enum {
  State_InputOperand,
  State_InputOperation,
  State_OpenFrame,
  State_CloseFrame
} calcState_t;

// Replacing this enum with function pointers
typedef enum {
  Op_Add,
  Op_Subtract,
  Op_Multiply,
  Op_Divide,
  Op_ShiftLeft,
  Op_ShiftRight,
  Op_And,
  Op_Or,
  Op_Not,
  Op_Nand,
  Op_Nor,
  Op_Xor,
  Op_Mod
} operation_t;

int calc_performAdd(int a, int b);
int calc_performSubtract(int a, int b);
int calc_performMultiply(int a, int b);
int calc_performDivide(int a, int b);
int calc_performShiftLeft(int a, int b);
int calc_performShiftRight(int a, int b);
int calc_performAnd(int a, int b);
int calc_performOr(int a, int b);
int calc_performNot(int a, int b); // b operand is ignored, we'll have to figure out if this makes operation silly
int calc_performNand(int a, int b);
int calc_performNor(int a, int b);
int calc_performXor(int a, int b);
int calc_performMod(int a, int b);

typedef struct {
  int accum;
  int (*operation)(int, int);
} calcFrame_t;

typedef enum {base16 = 16, base10 = 10} base_t;

typedef struct {
  calcState_t state;
  base_t base;
  
  calcFrame_t stack[CALC_STACK_SIZE];
  char stackPtr; // only need an 8 bit integer... for now...
  int accum;
  int operand;
  int (*operation)(int, int);
} calc_t;


// State transition handler
void calc_FSM(calc_t* calcPtr, char in);
void calc_handleInputOperand(calc_t* calcPtr, char in);
void calc_handleInputOperation(calc_t* calcPtr, char in);
void calc_handleOpenFrame(calc_t* calcPtr, char in);
void calc_handleCloseFrame(calc_t* calcPtr, char in);

// Helper for updating operation function ptr
void calc_updateOperation(calc_t* calcPtr, char in);

#endif // CALC_H_
