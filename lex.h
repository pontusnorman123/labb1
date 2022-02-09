#ifndef LABB1_LEX_H
#define LABB1_LEX_H

enum tokens{ID, OR, REPEAT, CATCH, DOT, COUNTER, IGNORE, CATCH_OUT };

tokens lex(char c){
    switch(c) {
        case '+':
            return OR;
        case '*':
            return REPEAT;
        case '()':
            return CATCH;
        case '.':
            return DOT;
        case '{}':
            return COUNTER;
        case '/I':
            return IGNORE;
        case '/O{}':
            return CATCH_OUT;
    }
}

#endif //LABB1_LEX_H
