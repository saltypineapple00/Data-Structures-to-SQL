#include "rightparen.h"

RightParen::RightParen() {
    right = ")";
}

RightParen::RightParen(char right_paren){
    right = ")";
}
RightParen::RightParen(string right_paren){
    right = right_paren;
}
void RightParen::Print(ostream &outs) const{
    // outs << "right_paren: " ;
    outs <<  right;
}


