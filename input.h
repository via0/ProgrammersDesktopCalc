#ifndef INPUT_H_
#define INPUT_H_

#define INPUT_RESET       '\e'
#define INPUT_PLUS_MINUS  'p' // temporary
#define INPUT_EQUALS      '='
#define INPUT_OPEN_P      '('
#define INPUT_CLOSE_P     ')'
#define INPUT_ADD         '+'
#define INPUT_SUBTRACT    '-'
#define INPUT_MULTIPLY    '*'
#define INPUT_DIVIDE      '/'
#define INPUT_SHIFT_L     '<'
#define INPUT_SHIFT_R     '>'
#define INPUT_AND         '&'
#define INPUT_OR          '|'
#define INPUT_NOT         '~'
#define INPUT_NAND        'q' // arbitrary, temporary
#define INPUT_NOR         'w' // arbitrary, temporary
#define INPUT_XOR         '^'
#define INPUT_MOD         '%'
#define INPUT_0           '0'
#define INPUT_1           '1'
#define INPUT_2           '2'
#define INPUT_3           '3'
#define INPUT_4           '4'
#define INPUT_5           '5'
#define INPUT_6           '6'
#define INPUT_7           '7'
#define INPUT_8           '8'
#define INPUT_9           '9'
#define INPUT_A           'a'
#define INPUT_B           'b'
#define INPUT_C           'c'
#define INPUT_D           'd'
#define INPUT_E           'e'
#define INPUT_F           'f'
#define INPUT_BASE_TOGGLE '\t' // toggle base between 16 and 10

// Helper function for determining if input char is between 0-F
int input_isNumeric(char in);

// Helper function for converting input char to an actual integer between 0-F
int input_toNumber(char in);

// Helper function for determing if input char is one of our logic operations
int input_isLogicOp(char in);

#endif // INPUT_H_
