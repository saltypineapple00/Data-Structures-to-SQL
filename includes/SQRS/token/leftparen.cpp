#include "leftparen.h"

using namespace std;

LeftParen::LeftParen() {
    left = "(";   
}

LeftParen::LeftParen(char left_paren){
    left = "(";
}
LeftParen::LeftParen(string left_paren){
    left = left_paren;
}

void LeftParen::Print(ostream &outs) const{
    // outs << "left_paren: " ;
    outs << left;
}



