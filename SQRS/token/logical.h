#ifndef LOGICAL_H
#define LOGICAL_H

#include <iostream>
#include "token.h"

using namespace std;

class Logical: public Token
{
public:
    Logical();
    Logical(string oper);

    void Print(ostream &outs) const;
    int get_prec(); //get precedence for RPN

    string get_oper()const {return op;} 

    TOKEN_TYPES TypeOf(){
        return LOGICAL;
    }
private:
    string op;
    int prec ;  //precedence of operator
    // enum op {AND, OR, EQUAL, GREAT, LESS, BIGEQ, LESSEQ};
};


#endif