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



    //String* p_string = nullptr;
    //p_string = parse_string(first, last);

    Expr* p_expr = parse_expression(first,last);
    auto p_group = new Group;

    //p_group->add(p_string);
    p_group->add(p_expr);
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

    /*
    if(*first == '\\')
    {
        first = first + 2;
    }
    */

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

    if(*first == '\\')
    {
        first = first + 2;
    }

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
    auto token = lex(++tmp, last);

    if(token == REPEAT)
    {
        p_lhs = parse_ignore_repeat(first,last);
        p_string->add(p_lhs);
    }

    if(token == L_COUNTER)
    {
        p_lhs = parse_ignore_case_counter(first,last);
        p_string->add(p_lhs);
    }
    else
    {
        p_lhs = parse_ignore_case_char(first,last);
        p_string->add(p_lhs);
    }

    if(*first == '\\')
    {
        first = first + 2;
        return p_string;
    }

    token = lex(first,last);
    ASTNode* p_rhs = nullptr;

    if(token != CHAR && token != DOT && token != REPEAT){
        p_string->add(p_rhs);
        return p_string;
    }

    tmp = first;
    auto next_token = lex(++tmp, last);
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
Or* parse_or(IT &first, IT last){

    String* p_lhs = parse_string(first,last);
    first++;
    String* p_rhs = parse_string(first,last);
    first++;

    Or* p_or = new Or;
    p_or->add(p_lhs);
    p_or->add(p_rhs);

    return p_or;



}

template<typename IT>
IgnoreCaseOr* parse_ignore_case_or(IT &first, IT last)
{
    IgnoreCaseString* p_lhs = parse_ignore_case_string(first,last);
    first++;
    IgnoreCaseString* p_rhs = parse_ignore_case_string(first,last);
    first = first + 4;

    IgnoreCaseOr* p_or = new IgnoreCaseOr;
    p_or->add(p_lhs);
    p_or->add(p_rhs);

    return p_or;
}

template<typename IT>
Expr* parse_expression(IT &first, IT last){

    ASTNode* p_string;
    ASTNode* p_lhs;
    auto p_expr = new Expr;

    auto token = lex(first,last);

    if(token == CHAR || token == DOT)
    {


        bool or_case = false;
        bool or_ignore_case = false;

        auto i = first;
        while (token == CHAR)
        {
            token = lex(i,last);
            i++;
        }
        if(token == OR)
        {
            i++;
            token = lex(i,last);
            while(token == CHAR)
            {
                token = lex(i,last);
                i++;
            }
            if(token == IGNORE_CASE)
            {
                p_lhs = parse_ignore_case_or(first,last);
                p_expr->add(p_lhs);
                token = lex(first,last);
                if(token != END)
                {
                    Expr* p_rhs = parse_expression(first,last);
                    p_expr->add(p_rhs);
                }
                return p_expr;
            }
            else
            {
                p_lhs = parse_or(first,last);
                p_expr->add(p_lhs);
                token = lex(first,last);
                if(token != END)
                {
                    Expr* p_rhs = parse_expression(first,last);
                    p_expr->add(p_rhs);
                }
                return p_expr;
            }

        }


        bool ignore_case_string = false;
        token = lex(first,last);
        for(auto i = first; token == CHAR ; i++)
        {
            token = lex(i,last);
            if(token == IGNORE_CASE)
            {
                ignore_case_string = true;
            }
        }

        if(ignore_case_string)
        {
            p_string = parse_ignore_case_string(first,last);
            p_expr->add(p_string);
        }
        else
        {
            p_string = parse_string(first,last);
            p_expr->add(p_string);
        }

        token = lex(first,last);

        if(token == CATCH_GROUP || token == R_PAREN)
        {
            return p_expr;
        }

        if(token != END)
        {
            Expr* p_rhs = parse_expression(first,last);
            p_expr->add(p_rhs);
        }

    }

    token = lex(first,last);

    if(token == L_PAREN) {

        bool or_case = false;
        bool or_ignore_case = false;
        auto i = first;


        while(token != R_PAREN) {
            token = lex(i, last);
            i++;
            if (token == OR) {
                or_case = true;
            }
        }
        token = lex(i,last);
        if(token == IGNORE_CASE)
        {
            or_ignore_case = true;
        }

        if(or_ignore_case)
        {
            first++;
            p_lhs = parse_ignore_case_or(first,last);
            p_expr->add(p_lhs);
            token = lex(first,last);
            if(token != END){
                Expr *p_rhs = parse_expression(first,last);
                p_expr->add(p_rhs);
            }
            return p_expr;
        }
        else if(or_case)
        {
            first++;
            p_lhs = parse_or(first,last);
            p_expr->add(p_lhs);
            token = lex(first,last);
            if(token != END){
                Expr *p_rhs = parse_expression(first,last);
                p_expr->add(p_rhs);
            }
            return p_expr;
        }

        bool ignore_case_group = false;

        i = first;
        while(lex(i,last) != R_PAREN)
        {
            i++;
        }
        if(lex(++i,last) == IGNORE_CASE)
        {
            ignore_case_group = true;
        }

        if(ignore_case_group)
        {
            p_lhs = parse_ignore_case_group(first,last);
            p_expr->add(p_lhs);
        }
        else
        {
            p_lhs = parse_group(first,last);
            p_expr->add(p_lhs);
        }

    }

    token = lex(first,last);

    if(token == CATCH_GROUP || token == R_PAREN)
    {
        return p_expr;
    }

    if(token != END){
        Expr *p_rhs = parse_expression(first,last);
        p_expr->add(p_rhs);
    }


    return p_expr;
}


template<typename IT>
GroupOut* parse_group_out(IT &first, IT last, int pos){

    ASTNode* p_child = nullptr;
    auto p_group_out = new GroupOut;
    if(pos == 0)
    {
        p_child = parse_expression(first,last);
        p_group_out->add(p_child);

    }
    else
    {
        for(int i = 0; i < pos; i++, first++)
        {
            while(*first != '(')
            {
                first++;
            }
        }
        //Hoppar ett för mkt
        first--;

        bool ignore_case_group = false;

        auto i = first;
        while(lex(i,last) != R_PAREN)
        {
            i++;
        }
        if(lex(++i,last) == IGNORE_CASE)
        {
            ignore_case_group = true;
        }

        if(ignore_case_group)
        {
            p_child = parse_ignore_case_group(first,last);
            p_group_out->add(p_child);
        }
        else
        {
            p_child = parse_group(first,last);
            p_group_out->add(p_child);
        }
    }


    return p_group_out;

}

template<typename IT>
AllOut* parse_all_out(IT &first, IT last){

    auto token = lex(first,last);
    bool ignore_case = false;
    auto p_all_out = new AllOut;

    Expr* p_expr = nullptr;
    p_expr = parse_expression(first,last);
    p_all_out->add(p_expr);



    return p_all_out;
};

template<typename IT>
Search *parse_search(IT &first, IT last){

    auto token = lex(first,last);
    bool catch_case = false;
    int group_pos;

    for(auto i = first; i != last - 1; i++)
    {
        token = lex(i,last);
        if(token == CATCH_GROUP){
            catch_case = true;
            i = i + 3;
            group_pos = std::stoi(&*i);
        }
    }

    ASTNode* p_child = nullptr;
    auto p_search = new Search;

    if(catch_case)
    {
        p_child = parse_group_out(first,last, group_pos);
        p_search->add(p_child);
    }
    else
    {
        p_child = parse_all_out(first,last);
        p_search->add(p_child);
    }

    return p_search;
}










#endif //LABB1_PARSE_H
