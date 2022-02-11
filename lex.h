#ifndef LABB1_LEX_H
#define LABB1_LEX_H

#include <iostream>
#include <stdio.h>
#include <ctype.h>


enum tokens{OPERAND, L_PAREN, R_PAREN, END};


template<typename IT>
tokens lex(IT &first, IT last){
    switch(*first) {

        case '(':
            first++;
            std::cout<<"test4" <<std::endl;

            return L_PAREN;
        case ')':
            first++;
            std::cout<<"test5" <<std::endl;

            return R_PAREN;

        case '\0':
          return END;

        default:
            // first++;
            return OPERAND;

    }
}

#endif //LABB1_LEX_H