#ifndef LABB1_LEX_H
#define LABB1_LEX_H

#include <iostream>
#include <stdio.h>
#include <ctype.h>


enum tokens{OPERAND, L_PAREN, R_PAREN};


template<typename IT>
tokens lex(IT first){
    switch(*first) {
        case 'T':
            first++;
            std::cout<<"test" <<std::endl;
            return OPERAND;
        case 'E':
            first++;
            std::cout<<"test2" <<std::endl;

            return OPERAND;
        case 'S':
            first++;
            std::cout<<"test3" <<std::endl;

            return OPERAND;
        case '(':
            first++;
            std::cout<<"test4" <<std::endl;

            return L_PAREN;
        case ')':
            first++;
            std::cout<<"test5" <<std::endl;

            return R_PAREN;
    }
}

#endif //LABB1_LEX_H