#ifndef RPN_H
#define RPN_H
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
#include "../../../includes/table/table.h"
#include "../../../includes/binary_files/file_record.h"
#include "../../../includes/table/index.h"

class RPN
{
public:
    RPN();
    RPN(const Queue<Token *> &q); // CTOR

    vector<long> eval();
    vector<long> operator()(const Index &indices, Map<string, int> fields);

    void get_index(const string field);

    void set_input(Queue<Token *> &token);
    void print(ostream &outs) const;

private:
    Index ind;
    Queue<Token *> post; // Postfix
    Map<string, int> fieldmap;
    int field_ind;
};

#endif