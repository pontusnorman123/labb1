#ifndef LABB1_LEX_H
#define LABB1_LEX_H
//Dagen
#include <iostream>
#include <stdio.h>
#include <ctype.h>


enum tokens{CHAR, L_PAREN, R_PAREN, END, DOT, REPEAT, IGNORE_CASE, CATCH_GROUP, L_COUNTER, R_COUNTER};


template<typename IT>
tokens lex(IT &first, IT last){
    switch(*first) {

        case '(':
            return L_PAREN;
        case ')':
            return R_PAREN;
        case '\0':
          return END;
        case '.':
            return DOT;
        case '*':
            return REPEAT;
        case '{':
            return L_COUNTER;
        case '}':
            return R_COUNTER;
        case '\\': {

            if (*(first + 1) == 'I') {
                return IGNORE_CASE;
            }
            return CATCH_GROUP;
        }

        default:
            return CHAR;

    }
}

#endif //LABB1_LEX_H