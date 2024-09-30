#ifndef LEFTPAREN_H
#define LEFTPAREN_H
#include <iostream>
#include "token.h"

using namespace std;

class LeftParen: public Token
{
public:
    LeftParen();
    LeftParen(char left_paren);
    LeftParen(string left_paren);
        
    int get_prec() {return prec;} // get precedence
    
    void Print(ostream &outs=cout) const;

    TOKEN_TYPES TypeOf(){return L_PAREN;}

private:
    string left; 
    int prec = 0;

};


#endif 