#ifndef LABB1_LEX_H
#define LABB1_LEX_H
//Dagen
#include <iostream>
#include <stdio.h>
#include <ctype.h>


enum tokens{CHAR, L_PAREN, R_PAREN, END, DOT, REPEAT};


template<typename IT>
tokens lex(IT &first, IT last){
    switch(*first) {

        case '(':
            first++;
            return L_PAREN;
        case ')':
            return R_PAREN;
        case '\0':
          return END;
        case '.':
            return DOT;
        case '*':
            return REPEAT;
        default:
            return CHAR;

    }
}

#endif //LABB1_LEX_H