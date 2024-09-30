#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H
#include <iostream>
#include "token.h"
#include "constants.h"


using namespace std;

class RightParen: public Token
{
public:
    RightParen();
    RightParen(char right_paren);
    RightParen(string right_paren);

    int get_prec() {return prec;} // get precedence

    void Print(ostream &outs=cout) const ;

    TOKEN_TYPES TypeOf(){return R_PAREN;}

private:
    string right;
    int prec = 6;
};

#endif 