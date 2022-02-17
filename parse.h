#ifndef LABB1_PARSE_H
#define LABB1_PARSE_H

#include "nodes.h"
#include "lex.h"
//Dagen

template<typename IT>
Operand* parse_operand(IT &first, IT last){

    auto op_token = lex(first, last);

    if(op_token != OPERAND)
    {
        return nullptr;
    }

    auto p_op = new Operand;
    p_op->op=*first;
    first++;
    return p_op;
}

template<typename IT>
String* parse_string(IT &first, IT last){

    //Parsa operand
    Operand* p_lhs = nullptr;
    p_lhs = parse_operand(first,last);


    String* p_string = new String;
    p_string->add(p_lhs);
    //Nästa tecken
    auto op_token = lex(first,last);
    String* p_rhs = nullptr;

    if(op_token != OPERAND){
        return p_string;
    }
    p_rhs = parse_string(first,last);

    p_string->add(p_rhs);

    return p_string;
}

template<typename IT>
Group* parse_group(IT &first, IT last) {

    auto lparen_token = lex(first, last);

    if(lparen_token!= L_PAREN)
    {
        return nullptr;
    }

    String* p_string = nullptr;
    p_string = parse_string(first, last);
    auto token_RPAREN = lex(first, last);

    if(token_RPAREN != R_PAREN)
    {
        return nullptr;
    }

    auto p_group = new Group;
    p_group->children.push_back(p_string);
    return p_group;

}

template<typename IT>
Search *parse_search(IT &first, IT last){

    Group* p_group = nullptr;



    p_group = parse_group(first,last);

    auto p_search = new Search;

    p_search->children.push_back(p_group);

    return p_search;
}










#endif //LABB1_PARSE_H
