#ifndef LABB1_PARSE_H
#define LABB1_PARSE_H

#include "nodes.h"
#include "lex.h"
//Dagen

template<typename IT>
Char* parse_char(IT &first, IT last){

    auto char_token = lex(first, last);

    if(char_token !=  CHAR && char_token != DOT)
    {
        return nullptr;
    }

    auto p_char = new Char;
    p_char->ch=*first;
    first++;
    return p_char;
}

template<typename IT>
String* parse_string(IT &first, IT last){

    //Parsa operand

    Char* p_lhs = nullptr;
    p_lhs = parse_char(first,last);


    String* p_string = new String;
    p_string->add(p_lhs);
    //Nästa tecken
    auto char_token = lex(first,last);
    String* p_rhs = nullptr;

    if(char_token != CHAR && char_token != DOT){
        p_string->add(p_rhs);
        return p_string;
    }
    p_rhs = parse_string(first,last);
    p_string->add(p_rhs);

    return p_string;
}

template<typename IT>
Group* parse_group(IT &first, IT last) {

    auto lparen_token = lex(first, last);
    first++;
    if(lparen_token!= L_PAREN)
    {
        return nullptr;
    }

    String* p_string = nullptr;
    p_string = parse_string(first, last);
    auto token_RPAREN = lex(first, last);
    first++;

    if(token_RPAREN != R_PAREN)
    {
        return nullptr;
    }

    auto p_group = new Group;
    p_group->children.push_back(p_string);
    return p_group;

}

template<typename IT>
Expr* parse_expression(IT &first, IT last){

    String* p_string = nullptr;

    auto token = lex(first,last);
    auto p_expr = new Expr;

    if(token == CHAR)
    {
        p_string = parse_string(first,last);
        p_expr->add(p_string);
        token = lex(first,last);

    }

    Group* p_group = nullptr;
    if(token == L_PAREN) {
        p_group = parse_group(first,last);
        p_expr->add(p_group);
    }

    token = lex(first,last);
    Expr * p_rhs = nullptr;
    if(token != END){
        p_rhs = parse_expression(first,last);
        p_expr->add(p_rhs);
    }

    return p_expr;
}

template<typename IT>
GroupOut* parse_groupOut(IT &first, IT last){

    Expr* p_expr = nullptr;
    p_expr = parse_expression(first,last);
    auto p_groupOut = new GroupOut;
    p_groupOut->add(p_expr);

    return p_groupOut;
};

template<typename IT>
Search *parse_search(IT &first, IT last){

    GroupOut* p_groupOut = nullptr;
    p_groupOut = parse_groupOut(first,last);
    auto p_search = new Search;
    p_search->add(p_groupOut);

    return p_search;
}










#endif //LABB1_PARSE_H
