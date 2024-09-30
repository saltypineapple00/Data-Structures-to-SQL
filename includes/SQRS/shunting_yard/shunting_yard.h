#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H
#include <iostream>
#include <iomanip>
#include <vector>

#include "../node/node.h"
#include "../stack/MyStack.h"
#include "../queue/MyQueue.h"
#include "../token/token.h"
#include "../token/logical.h"
#include "../token/relational.h"
#include "../token/constants.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"
#include "../token/tk_string.h"

class ShuntingYard
{
public:
    ShuntingYard();                            // Default CTOR
    ShuntingYard(const vector<string> &infix); // CTOR
    ShuntingYard(const Queue<Token *> &q);     // CTOR

    Queue<Token *> postfix();
    Queue<Token *> postfix(Queue<Token *> infix);

    void infix(const Queue<Token *> &q); // set_input version
    void print(ostream &outs) const;

    bool is_greater(Token *t1, Token *t2);

private:
    Queue<Token *> inf;
};

#endif