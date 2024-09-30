#include "logical.h"

Logical::Logical()
{
    op = "";
    prec = -1;
}

Logical::Logical(string oper)
{
    op = oper;
    if (op.compare("and") == 0)
        prec = AND;
    if (op.compare("or") == 0)
        prec = OR;
}

void Logical::Print(ostream &outs) const
{
    outs << op;
}

int Logical::get_prec() //get precedence for RPN
{
    return prec;
}
    