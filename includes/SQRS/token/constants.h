#ifndef CONSTANTS_TABLE_H
#define CONSTANTS_TABLE_H
#include <iostream>
#include <iomanip>

using namespace std;

enum TOKEN_TYPES {
                  TK_STRING,
                  RELATIONAL,
                  LOGICAL,
                  L_PAREN,
                  R_PAREN,
                  RESULT_SET,
                  TOKEN,
};

enum operators {LEFT,OR, AND, LESS, LESSEQ, EQUAL, GREATEQ, GREAT};


#endif // CONSTANTS_H