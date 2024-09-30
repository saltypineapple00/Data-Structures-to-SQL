#include "sql.h"
int SQL ::query;
SQL ::SQL()
{
}
SQL ::SQL(string filename)
{
    SQL localobj;
    string line;
    ifstream f;
    f.open(filename);
    if (f.fail())
    {
        cout << "cannot open file " << endl;
    }
    while (getline(f, line))
    {
        if (line.find("make") == 0 || line.find("insert") == 0 || line.find("select") == 0)
        {
            cout << "[" << query << "]  " << line << endl;
            localobj.command(line);
            cout << "SQL: DONE." << endl;
            query++;
        }
        else if (f.eof())
        {
            cout << "BATCH FILE DONE!" << endl;
        }
        else // if (line.find("//"))
        {
            cout << line << endl;
        }
        // else if (line.find(...) == 0)
        // {
        //     cout << line << endl;
        // }
    }
    f.close();
}

// void SQL ::runFile(string filename)
// {
//     ifstream f;
//     string line;
//     f.open(filename + ".txt");
//     if (f.fail())
//     {
//         cout << "cannot open file " << endl;
//     }
//     while (getline(f, line))
//     {
//         cout << "am i here? " << endl;

//         if (line.find("//"))
//         {
//             cout << line << endl;
//         }
//         if (line.find("make") || line.find("insert") || line.find("select"))
//         {
//             cout << "[" << query << "]  " << line << endl;
//             command(line);
//             query++;
//         }
//     }
//     f.close();
// }

Table SQL::command(string list)
{
    MMap<string, string> ptree;
    bool valid = getSQL(list, ptree);
    if (ptree["command"][0] == "insert")
    {
        tbl = Table(ptree["table_name"][0]);
        tbl.insert_into(ptree["values"]);
        // return tbl;
    }
    else if (ptree["command"][0] == "make")
    {
        tbl = Table(ptree["table_name"][0], ptree["fields"]);
        // return tbl;
    }
    else if (ptree["command"][0] == "select")
    {
        tbl = Table(ptree["table_name"][0]);
        if (ptree.contains("condition"))
        {
            // cout << "here" << endl;
            return tbl.select(ptree["fields"], ptree["condition"]);
        }
        // if (!ptree.contains("condition") && ptree["fields"][0] != "*")
        // {
        //     return tbl.select(ptree["fields"]);
        // }
        else
        {
            tbl.select_all(); //(ptree["fields"], ptree["condition"]);
        }
    }
    return tbl;
}

bool SQL::getSQL(string str, MMap<string, string> &ptree)
{
    char s[500];
    strcpy(s, str.c_str());
    Parser p(s);
    ptree = p.parse_tree();
    return p.fail();
}
vector<long> SQL::select_recnos()
{
    return tbl.select_recnos();
}
