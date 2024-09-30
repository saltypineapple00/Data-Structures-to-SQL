#include "rpn.h"
RPN ::RPN()
{
}

RPN ::RPN(const Queue<Token *> &q) // CTOR
{
    post = q;
    // cout << "the post(fix) is " << post << endl;
}

vector<long> RPN ::eval()
{
    Token *save;
    Queue<string> outputq;
    Stack<vector<long>> opstack;
    vector<long> recordlist;
    while (!post.empty())
    {
        save = post.pop();
        switch (save->TypeOf())
        {
        case TK_STRING:
        {
            string temp = static_cast<TokenStr *>(save)->get_tkstr();
            outputq.push(temp);
            // cout << "Just pushed [" << temp << "] into outputq" << endl;
            break;
        }

        case LOGICAL:
        {
            if (static_cast<Logical *>(save)->get_oper() == "and")
            {
                // if AND call intersection
                vector<long> r1 = opstack.pop();
                vector<long> r2 = opstack.pop();
                recordlist = _intersection(r1, r2);
                opstack.push(recordlist);
            }
            if (static_cast<Logical *>(save)->get_oper() == "or")
            {
                // OR so call union
                vector<long> r1 = opstack.pop();
                vector<long> r2 = opstack.pop();
                recordlist = _union(r1, r2);
                opstack.push(recordlist);
            }
            break;
        }
        case RELATIONAL:
        {
            // cout << endl
            //      << "In realtional with " << save << endl
            //      << endl;
            string fieldnameis = outputq.pop();
            get_index(fieldnameis); // saved the index in field_ind

            // cout << "To get the index(field) is " << fieldnameis << endl;

            string value = outputq.pop();
            // cout << "value to look is " << value << endl
            //      << endl;

            int prec = static_cast<Relational *>(save)->get_prec();

            switch (prec)
            {

            case EQUAL:
            {
                MMap<string, long>::Iterator it;
                vector<long> records;
                records += ind.indices[field_ind][value];
                opstack.push(records);
                break;
            }

            case LESS:
            {
                // cout << "in less than " << endl;
                MMap<string, long>::Iterator it;
                vector<long> records;
                // cout << "tHe field index is " << field_ind << endl;
                // it = ind.indices[field_ind].lower_bound(value);
                // cout << *it << endl;
                // cout << ind.indices[field_ind] << endl;
                for (it = ind.indices[field_ind].begin(); it != ind.indices[field_ind].lower_bound(value); it++)
                {
                    // cout << "here? " << endl;
                    // cout << *it << endl;
                    // records += ind.indices[field_ind].at((*it).key);
                    records += (*it).value_list;
                }
                // cout << "the records are " << records << endl;
                opstack.push(records);
                break;
            }

            case LESSEQ:
            {
                MMap<string, long>::Iterator it;
                vector<long> records;
                for (it = ind.indices[field_ind].begin(); it != ind.indices[field_ind].upper_bound(value); it++)
                {
                    // records += ind.indices[field_ind].at((*it).key);
                    records += (*it).value_list;
                }
                opstack.push(records);
                break;
            }

            case GREAT:
            {
                // cout << "am i in greater than? " << endl;
                MMap<string, long>::Iterator it;
                vector<long> records;
                it = ind.indices[field_ind].upper_bound(value);
                for (; it != ind.indices[field_ind].end(); it++)
                {
                    records += (*it).value_list;
                }
                opstack.push(records);
                break;
            }
            case GREATEQ:
            {
                MMap<string, long>::Iterator it;
                vector<long> records;
                for (it = ind.indices[field_ind].lower_bound(value); it != ind.indices[field_ind].end(); it++)
                {
                    records += (*it).value_list;
                }
                opstack.push(records);
                break;
            }
            }
        }
        }
    }
    return opstack.pop();
}
vector<long> RPN ::operator()(const Index &indices, Map<string, int> fields)
{
    ind = indices;
    fieldmap = fields;
    MMap<string, long>::Iterator it;
    // for (int i = 0; i < fields.size(); i++)
    // {
    //     // for (it = ind.indices[field_ind].begin(); it != ind.indices[field_ind].end(); it++)
    //     {
    //         // cout << "did i get in " << endl;
    //         cout << ind.indices[i]; // << ":" << ind.indices[i][(*it).key] << endl;
    //     }
    // }
    // for (it = ind.indices[field_ind].begin(); it != ind.indices[field_ind].end(); it++)
    // {
    //     cout << *it << " | ";
    // }
    return eval();
}

void RPN ::get_index(const string field)
{
    // Table tbl;
    // field_ind = tbl.get_field_index(field);
    // cout << "The field is " << field << endl;
    // cout << "The field map is " << fieldmap << endl;
    field_ind = fieldmap[field];

    // cout << "field_ind is " << field_ind << endl;
}

void RPN ::set_input(Queue<Token *> &token)
{
    post = token;
}

void RPN ::print(std ::ostream &outs) const
{
    outs << post << endl;
}