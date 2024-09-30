#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <iomanip>
#include "../../includes/bplustree/bplustree.h"
#include "../../includes/bplustree/multimap.h"
#include "../../includes/bplustree/map.h"
#include <string>
#include <cstring>
#include "../../includes/tokenizer/stokenize.h"
// #include "../../includes/tokenizer/state_machine_functions.h"
#include "../../includes/table/typedefs.h"

class Parser
{
public:
    Parser();
    Parser(char *s);
    void set_string(char *s);
    int get_column(string token);
    bool get_parse_tree(vector<string> s);
    void build_keyword_list();
    void init_table();
    void make_table();

    // acessors and mutators
    bool fail();
    MMap<string, string> parse_tree();

private:
    // STokenizer stk;

    int table[MAX_ROWS][MAX_COLUMNS];

    // string p_token;

    int save_state = -1;

    MMap<string, string> ptree; // output mmap

    Map<string, int> keywords; // maps keywords to col numbers
    bool flag;
    vector<string> inputq;
    // const int key_count = 14;
    enum keys
    {
        ZERO,
        SELECT,
        MAKE,
        INSERT,
        STAR,
        FROM,
        TABLE,
        FIELDS,
        VALUES,
        INTO,
        WHERE,
        COLS,
        // AND,
        // OR,
        SYM,

    };
};
#endif