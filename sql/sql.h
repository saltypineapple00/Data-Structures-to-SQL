#ifndef SQL_H
#define SQL_H

#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>

#include "../../includes/table/table.h"
#include "../../includes/parser/parser.h"

class SQL
{
public:
    SQL();
    SQL(string filename);
    Table command(string list);
    vector<long> select_recnos();
    // void runFile(string filename);
    static int query;

private:
    bool getSQL(string str, MMap<string, string> &ptree);
    Table tbl;
};
#endif