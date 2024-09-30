#ifndef RELATIONAL_H
#define RELATIONAL_H

#include <iostream>
#include "token.h"

using namespace std;

class Relational: public Token
{
public:
    Relational();
    Relational(string oper);

    void Print(ostream &outs) const;
    virtual int get_prec(); //get precedence for RPN
    
    string get_oper() const {return op;}
    
    TOKEN_TYPES TypeOf(){
        return RELATIONAL;
    }

private:
    string op;
    int prec;  //precedence of operator
};


#endif