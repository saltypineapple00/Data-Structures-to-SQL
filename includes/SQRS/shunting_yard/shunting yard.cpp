#include "shunting_yard.h"

ShuntingYard ::ShuntingYard()
{
}

ShuntingYard ::ShuntingYard(const vector<string> &infix)
{
    for (int i = 0; i < infix.size(); i++)
    {
        string check = infix[i];
        if (check == "(")
        {
            inf.push(new LeftParen(check));
        }
        else if (check == ")")
        {
            inf.push(new RightParen(check));
        }
        else if (check == "and" || check == "or")
        {
            inf.push(new Logical(check));
        }
        else if (check == "<" || check == "<=" || check == "=" || check == ">=" || check == ">")
        {
            inf.push(new Relational(check));
        }
        else
        {
            inf.push(new TokenStr(check));
        }
    }
}

ShuntingYard ::ShuntingYard(const Queue<Token *> &q)
{
    inf = q;
    // cout << "the inf is " << inf << endl;
}

Queue<Token *> ShuntingYard::postfix()
{
    // cout << "in sy the queue is " << inf << endl;
    Token *save;
    Queue<Token *> outputq;
    Stack<Token *> opstack;
    while (!inf.empty())
    {
        save = inf.pop();
        // cout << "Just popped " << save << endl;
        switch (save->TypeOf())
        {
        case TK_STRING:
            outputq.push(save);
            break;

        case LOGICAL:
        {
            while (!opstack.empty() && opstack.top()->TypeOf() != L_PAREN && is_greater(save, opstack.top()))
            {
                outputq.push(opstack.pop());
            }
            opstack.push(save);
        }
        break;
        case RELATIONAL:
        {
            opstack.push(save);
            break;
            // cout << "In relational with token: " << save << endl;
            // if (opstack.empty())
            // {
            //     opstack.push(save);
            //     break;
            // }
            // else // if (opstack.top() != nullptr)
            // {
            //     int top_prec = static_cast<Logical *>(opstack.top())->get_prec();
            //     int save_prec = static_cast<Relational *>(save)->get_prec();
            //     if (opstack.top()->TypeOf() == LOGICAL)
            //     {
            //         if (top_prec >= save_prec)
            //         {
            //             while (top_prec >= save_prec)
            //             {
            //                 // cout << __LINE__ << endl;
            //                 if (!opstack.empty())
            //                 {
            //                     // cout << __LINE__ << endl;
            //                     outputq.push(opstack.pop());
            //                     cout << outputq << endl;
            //                 }
            //             }
            //             // cout << __LINE__ << endl;
            //             opstack.push(save);
            //             break;
            //         }
            //     }
            //     if (opstack.top()->TypeOf() == RELATIONAL)
            //     {
            //         int get_prec_rela = static_cast<Relational *>(opstack.top())->get_prec();
            //         if (get_prec_rela >= save_prec)
            //         {
            //             while (get_prec_rela >= save_prec)
            //             {
            //                 if (!opstack.empty())
            //                 {
            //                     outputq.push(opstack.pop());
            //                 }
            //             }
            //             opstack.push(save);
            //             break;
            //         }
            //     }
            // }
        }
        case L_PAREN:
        {
            opstack.push(save);
            break;
        }
        case R_PAREN:
        {
            // cout << "got into rparen" << endl;

            // cout << opstack << endl;
            while (!opstack.empty() && (opstack.top()->TypeOf() != L_PAREN))
            {
                outputq.push(opstack.pop());
                // cout << "popping and pushing " << endl;
            }
            // cout << "type:" << opstack.top()->TypeOf() << endl;
            // if (!opstack.empty() && opstack.top()->TypeOf() == L_PAREN)
            opstack.pop();

            break;
        }
        }
    }
    while (!opstack.empty())
    {
        // cout << "am i here ? " << endl;
        outputq.push(opstack.pop());
    }
    return outputq;
}

Queue<Token *> ShuntingYard::postfix(Queue<Token *> infix)
{
    infix = postfix();
}

void ShuntingYard::infix(const Queue<Token *> &q)
{
    inf = q;
}

void ShuntingYard::print(std::ostream &outs) const
{
    outs << inf << endl;
}

bool ShuntingYard::is_greater(Token *t1, Token *t2)
{
    if (t1->TypeOf() > t2->TypeOf())
    {
        return true;
    }
    else if (t1->TypeOf() == t2->TypeOf())
    {
        if (static_cast<Logical *>(t1)->get_prec() > static_cast<Logical *>(t2)->get_prec())
            return false;
    }
    return true;
}