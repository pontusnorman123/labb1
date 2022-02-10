#ifndef LABB1_PARSE_H
#define LABB1_PARSE_H

#include "nodes.h"

template<typename IT>
Search *parse_search(IT first1, IT last1, IT first2, IT last2){
        bool group = parse_group();
        auto p_search = new Search;
}

GroupOut* parse_group() {

    auto expression = parse_expression();
    return ;
}

Expression* parse_expression(){

}



#endif //LABB1_PARSE_H
