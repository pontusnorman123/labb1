#ifndef LABB1_LEX_H
#define LABB1_LEX_H

enum tokens{OPERAND, L_PAREN, R_PAREN};


template<typename FwdIt>
tokens lex(FwdIt first){
    switch(*first) {
        case '(':
            first++;
            return L_PAREN;
        case ')':
            first++;
            return R_PAREN;
    }
}

#endif //LABB1_LEX_H
