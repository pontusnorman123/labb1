#ifndef LABB1_LEX_H
#define LABB1_LEX_H
//Dagen
#include <iostream>
#include <stdio.h>
#include <ctype.h>


enum tokens{OPERAND, L_PAREN, R_PAREN, END};


template<typename IT>
tokens lex(IT &first, IT last){
    switch(*first) {

        case '(':
            return L_PAREN;
        case ')':
            return R_PAREN;

        case '\0':
          return END;
        default:
            return OPERAND;

    }
}

#endif //LABB1_LEX_H