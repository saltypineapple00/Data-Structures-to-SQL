#include "relational.h"

Relational::Relational()
{
    op = "";
    prec = -1;
}

Relational::Relational(string oper)
{
    op = oper;
    if (op.compare("=")== 0)
        prec = EQUAL;
    if (op.compare(">")== 0)
        prec = GREAT;
    if (op.compare("<")== 0)
        prec = LESS;
    if (op.compare(">=")== 0)
        prec = GREATEQ; 
    if (op.compare("<=")== 0)
        prec = LESSEQ;

}

void Relational::Print(ostream &outs) const
{
    outs << op;
}

int Relational::get_prec() //get precedence for RPN
{
    return prec;
}
