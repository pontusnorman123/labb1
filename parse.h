#ifndef LABB1_PARSE_H
#define LABB1_PARSE_H

#include "nodes.h"
#include "lex.h"
//Dagen


template<typename IT>
Repeat* parse_repeat(IT &first, IT last);

template<typename IT>
String* parse_string(IT &first, IT last);

template<typename IT>
Expr* parse_expression(IT &first, IT last);

template<typename IT>
Expr* parse_expression(IT &first, IT last);

template<typename IT>
IgnoreCaseString* parse_ignore_case_string(IT &first,IT last);

template<typename IT>
Char* parse_char(IT &first, IT last){

    auto char_token = lex(first, last);

    if(char_token !=  CHAR && char_token != DOT && char_token != REPEAT)
    {
        return nullptr;
    }

    auto p_char = new Char;
    p_char->ch=*first;
    first++;
    return p_char;
}

template<typename IT>
Counter* parse_counter(IT &first, IT last){

    first++;
    auto token = lex(first, last);
    if(token!= L_COUNTER)
    {
        return nullptr;
    }

    first--;
    Char* p_char = parse_char(first,last);
    first++;
    auto p_counter = new Counter;
    p_counter->add(p_char);

    int tmp = std::stoi(&*first);
    p_counter->counter = tmp;

    first++;

    auto token_RPAREN = lex(first, last);
    first++;

    if(token_RPAREN != R_COUNTER)
    {
        return nullptr;
    }

    return p_counter;

}

template<typename IT>
Repeat* parse_repeat(IT &first, IT last){

    ASTNode* p_lhs = parse_char(first,last);

    Repeat* p_repeat = new Repeat;
    p_repeat->add(p_lhs);
    //Hoppa över stjärna
    first++;

    auto token = lex(first,last);
    String* p_rhs = nullptr;

    if(token != CHAR && token != DOT && token != REPEAT){
        p_repeat->add(p_rhs);
        return p_repeat;
    }
    p_rhs = parse_string(first,last);
    p_repeat->add(p_rhs);

    return p_repeat;
}

template<typename IT>
String* parse_string(IT &first, IT last){

    String* p_string = new String;
    ASTNode* p_lhs;

    auto tmp = first;
    auto next_token = lex(++tmp, last);
    if(next_token == REPEAT)
    {
        p_lhs = parse_repeat(first,last);
        p_string->add(p_lhs);
    }

    if(next_token == L_COUNTER)
    {
        p_lhs = parse_counter(first,last);
        p_string->add(p_lhs);
    }
    else
    {
        p_lhs = parse_char(first,last);
        p_string->add(p_lhs);
    }

    /*
    p_lhs = parse_char(first,last);
    p_string->add(p_lhs);
    */

    auto token = lex(first,last);
    ASTNode* p_rhs = nullptr;

    if(token != CHAR && token != DOT && token != REPEAT){
        p_string->add(p_rhs);
        return p_string;
    }

    tmp = first;
    next_token = lex(++tmp, last);
    if(next_token == REPEAT)
    {
        p_lhs = parse_repeat(first,last);
        p_string->add(p_lhs);
    }
    else
    {
        p_rhs = parse_string(first,last);
        p_string->add(p_rhs);
    }


    return p_string;
}

template<typename IT>
Group* parse_group(IT &first, IT last) {

    auto token = lex(first, last);
    first++;
    if(token!= L_PAREN)
    {
        return nullptr;
    }

    String* p_string = nullptr;
    p_string = parse_string(first, last);
    auto p_group = new Group;
    p_group->add(p_string);
    auto token_RPAREN = lex(first, last);
    first++;

    if(token_RPAREN != R_PAREN)
    {
        return nullptr;
    }

    return p_group;

}

template<typename IT>
IgnoreCaseChar* parse_ignore_case_char(IT &first,IT last){

    auto token = lex(first, last);

    if(token !=  CHAR && token != DOT && token != REPEAT)
    {
        return nullptr;
    }

    auto p_char = new IgnoreCaseChar;
    p_char->ch=tolower(*first);
    first++;
    if(*first == '\\')
    {
        first = first + 2;
    }

    return p_char;
}

template<typename IT>
IgnoreCaseRepeat* parse_ignore_repeat(IT &first, IT last){

    ASTNode* p_lhs = parse_ignore_case_char(first,last);

    IgnoreCaseRepeat* p_repeat = new IgnoreCaseRepeat;
    p_repeat->add(p_lhs);
    //Hoppa över stjärna
    first++;

    auto token = lex(first,last);
    IgnoreCaseString* p_rhs = nullptr;

    if(token != CHAR && token != DOT && token != REPEAT){
        p_repeat->add(p_rhs);
        return p_repeat;
    }
    p_rhs = parse_ignore_case_string(first,last);
    p_repeat->add(p_rhs);

    return p_repeat;

}

template<typename IT>
IgnoreCaseGroup* parse_ignore_case_group(IT &first, IT last){

    auto token = lex(first, last);
    first++;
    if(token!= L_PAREN)
    {
        return nullptr;
    }

    IgnoreCaseString* p_string = nullptr;
    p_string = parse_ignore_case_string(first, last);
    auto p_group = new IgnoreCaseGroup;
    p_group->add(p_string);
    auto token_RPAREN = lex(first, last);
    first++;

    if(token_RPAREN != R_PAREN)
    {
        return nullptr;
    }

    return p_group;
}

template<typename IT>
IgnoreCaseCounter* parse_ignore_case_counter(IT &first, IT last){

    first++;
    auto token = lex(first, last);
    if(token!= L_COUNTER)
    {
        return nullptr;
    }

    first--;
    IgnoreCaseChar* p_char = parse_ignore_case_char(first,last);
    first++;
    auto p_counter = new IgnoreCaseCounter;
    p_counter->add(p_char);

    int tmp = std::stoi(&*first);
    p_counter->counter = tmp;

    first++;

    auto token_RPAREN = lex(first, last);
    first++;

    if(token_RPAREN != R_COUNTER)
    {
        return nullptr;
    }
    if(*first == '\\')
    {
        first = first + 2;
    }


    return p_counter;
}

template<typename IT>
IgnoreCaseString* parse_ignore_case_string(IT &first,IT last)
{
    IgnoreCaseString* p_string = new IgnoreCaseString;
    ASTNode* p_lhs;

    auto tmp = first;
    auto next_token = lex(++tmp, last);
    if(next_token == REPEAT)
    {
        p_lhs = parse_ignore_repeat(first,last);
        p_string->add(p_lhs);
    }

    if(next_token == L_COUNTER)
    {
        p_lhs = parse_ignore_case_counter(first,last);
        p_string->add(p_lhs);
    }
    else
    {
        p_lhs = parse_ignore_case_char(first,last);
        p_string->add(p_lhs);
    }




    auto token = lex(first,last);
    ASTNode* p_rhs = nullptr;

    if(token != CHAR && token != DOT && token != REPEAT){
        p_string->add(p_rhs);
        return p_string;
    }

    tmp = first;
    next_token = lex(++tmp, last);
    if(next_token == REPEAT)
    {
        p_lhs = parse_ignore_repeat(first,last);
        p_string->add(p_lhs);
    }
    else
    {
        p_rhs = parse_ignore_case_string(first,last);
        p_string->add(p_rhs);
    }


    return p_string;
}


template<typename IT>
IgnoreCaseExpr* parse_ignore_case_expr(IT &first, IT last){

    IgnoreCaseString* p_string = nullptr;

    auto token = lex(first,last);
    auto p_expr = new IgnoreCaseExpr;


    if(token == CHAR || token == DOT)
    {
        p_string = parse_ignore_case_string(first,last);
        p_expr->add(p_string);

        token = lex(first,last);
        if(token != END)
        {
            IgnoreCaseExpr* p_rhs = parse_ignore_case_expr(first,last);
            p_expr->add(p_rhs);
        }

    }

    token = lex(first,last);

    if(token == L_PAREN) {
        IgnoreCaseGroup* p_group = parse_ignore_case_group(first,last);
        p_expr->add(p_group);
    }

    token = lex(first,last);
    Expr * p_rhs = nullptr;

    if(*first == '\\')
    {
        first = first + 2;
    }

    if(token != END){
        p_rhs = parse_expression(first,last);
        p_expr->add(p_rhs);
    }


    return p_expr;

}

template<typename IT>
Expr* parse_expression(IT &first, IT last){

    String* p_string = nullptr;

    auto token = lex(first,last);
    auto p_expr = new Expr;
    bool ignore = false;

    for(auto i = first; i != last - 1; i++)
    {
        token = lex(i,last);
        if(token == IGNORE_CASE){
            ignore = true;
        }
    }

    token = lex(first,last);

    if(ignore)
    {
        IgnoreCaseExpr* p_ignore_case = parse_ignore_case_expr(first,last);
        p_expr->add(p_ignore_case);
    }
    else
    {
        if(token == CHAR || token == DOT)
        {
            p_string = parse_string(first,last);
            p_expr->add(p_string);

            token = lex(first,last);
            if(token != END)
            {
                Expr* p_rhs = parse_expression(first,last);
                p_expr->add(p_rhs);
            }

        }

        token = lex(first,last);

        if(token == L_PAREN) {
            Group* p_group = parse_group(first,last);
            p_expr->add(p_group);
        }

        token = lex(first,last);
        Expr * p_rhs = nullptr;
        if(token != END){
            p_rhs = parse_expression(first,last);
            p_expr->add(p_rhs);
        }
    }

    return p_expr;
}

template<typename IT>
AllOut* parse_AllOut(IT &first, IT last){

    Expr* p_expr = nullptr;
    p_expr = parse_expression(first,last);
    auto p_AllOut = new AllOut;
    p_AllOut->add(p_expr);

    return p_AllOut;
};

template<typename IT>
Search *parse_search(IT &first, IT last){

    AllOut* p_AllOut = parse_AllOut(first,last);
    auto p_search = new Search;
    p_search->add(p_AllOut);

    return p_search;
}










#endif //LABB1_PARSE_H
