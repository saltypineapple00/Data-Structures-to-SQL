#include "parser.h"
Parser::Parser()
{
    flag = true; // fail == true
    build_keyword_list();
}
Parser::Parser(char *s)
{
    flag = true;
    build_keyword_list();
    set_string(s);
}
void Parser::set_string(char *s)
{
    STokenizer stk(s); // cout << "here is s in parser : " << s << endl;
    make_table();
    SToken t;
    int i = 0;
    stk >> t;
    inputq.clear();
    while (stk.more())
    {
        if (t.type_string() != "SPACE" && t.type_string() != "EMPTY" && t.type_string() != "UNKNOWN")
        {
            // cout << "token:" << t.token_str() << "\ttype:" << t.type_string() << endl;
            inputq.push_back(t.token_str());
        }
        t = SToken();
        stk >> t;
    }
    t = SToken();
    ptree.clear();
    // get_parse_tree(inputq);
}
int Parser::get_column(string token)
{
    if (keywords.contains(token))
    {
        if (keywords[token] == FIELDS || keywords[token] == VALUES) //
        {
            save_state = keywords[token];
        }
        // if (keywords[token] == FIELDS)
        // {
        //     save_state = COLS;
        // }
        else if (keywords[token] == WHERE)
        {
            save_state = SYM;
        }
        else if (keywords[token] == SELECT)
        {
            save_state = FIELDS;
        }
        // cout << "THE TOKEN IS " << token << "the col is " << keywords[token] << endl;
        return keywords[token];
    }
    return save_state;
}
bool Parser::get_parse_tree(vector<string> s)
{
    string token = "";
    int state = 0;
    int endstate = -1;
    int i = 0;
    for (; i < s.size(); i++)
    {
        // cout << "the i is " << i << endl;
        token = s[i];
        // cout << "the column is " << get_column(token) << endl;
        int cur_state = table[state][get_column(token)];
        // cout << "token:" << token;
        // cout << "   new state:" << state << "   the col : " << get_column(token) << endl;
        switch (cur_state)
        {
        case -1:
            cur_state = endstate;
            // cout << " the state: " << state << endl;

        case SYM:
            ptree["condition"] += token;
            endstate = SYM;

            break;

        case SELECT:
            ptree["command"] += token;
            endstate = FIELDS;
            break;

        case INSERT:
            ptree["command"] += token;
            break;

        case MAKE:
            ptree["command"] += token;
            break;

        case FIELDS:
            if (i < s.size() && token == "fields")
            {
                i++;
                token = s[i];
            }
            ptree["fields"] += token;
            endstate = FIELDS;
            break;

        case VALUES:
            if (i < s.size() && token == "values")
            {
                i++;
                token = s[i];
            }
            ptree["values"] += token;
            endstate = VALUES;
            break;

        case WHERE:
            ptree["where"] += string("yes");
            endstate = SYM;
            break;

        case INTO:
            ptree["command"] += token;
            if (i < s.size())
            {
                i++;
                token = s[i];
            }
            ptree["table_name"] += token;
            break;

        case FROM:
            if (i < s.size())
            {
                i++;
                token = s[i];
            }
            ptree["table_name"] += token;
            break;

        case STAR:
            ptree["fields"] += token;
            break;

        case TABLE:
            if (i < s.size())
            {
                i++;
                token = s[i];
            }
            ptree["table_name"] += token;
            break;

        default:
            break;
        }
    }
    if (endstate == TABLE || endstate == FIELDS || endstate == SYM || endstate == STAR || endstate == VALUES)
    {
        return false;
    }
    return true;
}

MMap<string, string> Parser::parse_tree()
{
    flag = get_parse_tree(inputq);
    return ptree;
}
void Parser::build_keyword_list()
{
    keywords["select"] = SELECT;
    keywords["*"] = STAR;
    keywords["from"] = FROM;
    keywords["make"] = MAKE;
    keywords["table"] = TABLE;
    keywords["fields"] = FIELDS;
    keywords["insert"] = INSERT;
    keywords["values"] = VALUES;
    keywords["where"] = WHERE;
    keywords["into"] = INTO;
    keywords["COLS"] = COLS;
    // anything thats not here goes to sym
}

void Parser::make_table()
{
    init_table();
}

// acessors and mutators
bool Parser::fail()
{
    return flag;
}

void Parser::init_table()
{
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            table[i][j] = -1;
        }
    }

    // marking for make table command
    mark_cell(0, table, MAKE, MAKE);
    mark_cell(0, table, SELECT, SELECT);
    mark_cell(0, table, STAR, STAR);
    mark_cell(0, table, FROM, FROM);
    mark_cell(0, table, TABLE, TABLE);
    mark_cell(0, table, FIELDS, FIELDS);
    mark_cell(0, table, INSERT, INSERT);
    mark_cell(0, table, INTO, INTO);
    mark_cell(0, table, VALUES, VALUES);
    mark_cell(0, table, WHERE, WHERE);
    mark_cell(0, table, SYM, SYM);
    // mark_cell(0, table, COLS, COLS);

    mark_cell(MAKE, table, MAKE, MAKE);
    mark_cell(SELECT, table, SELECT, SELECT);
    mark_cell(STAR, table, STAR, STAR);
    mark_cell(FROM, table, FROM, FROM);
    mark_cell(TABLE, table, TABLE, TABLE);
    mark_cell(FIELDS, table, FIELDS, FIELDS);
    mark_cell(INSERT, table, INSERT, INSERT);
    mark_cell(INTO, table, INTO, INTO);
    mark_cell(VALUES, table, VALUES, VALUES);
    mark_cell(WHERE, table, WHERE, WHERE);
    mark_cell(SYM, table, SYM, SYM);
    // mark_cell(COLS, table, COLS, COLS);
}