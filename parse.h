#ifndef LABB1_PARSE_H
#define LABB1_PARSE_H

#include "nodes.h"

template<typename IT>
Search *parse_search(IT first, IT last){

    parse_group_out(first,last);
}

template<typename IT>
Operand* parse_operand(IT first){
    auto op_token = lex(first);
    if(op_token != OPERAND)
    {
        return nullptr;
    }
    auto p_op = new Operand;
    p_op->op=*first;
    return p_op;
}

template<typename IT>
GroupOut* parse_group(IT first, IT last) {

    auto token_LPAREN = lex(first);
    if(token_LPAREN != L_PAREN)
    {
        return nullptr;
    }
    parse_operand(first);

}



Expression* parse_expression(){

}





#endif //LABB1_PARSE_H
