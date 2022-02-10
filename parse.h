#ifndef LABB1_PARSE_H
#define LABB1_PARSE_H

<unknown> parse_group();

#include "nodes.h"

template<typename IT>
Search *parse_search(IT first, IT last){
        bool group = parse_group();
        auto p_search = new Search;
}

GroupOut* parse_group() {

    auto expression = parse_expression();
    return ;
}

#endif //LABB1_PARSE_H
