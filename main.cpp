#include "lex.h"
#include "parse.h"
#include "nodes.h"
#include <iostream>

int main(){

    //search string iterators
    std::string search_string = "TEST";
    auto search_string_start = search_string.begin();
    auto search_string_end = search_string.end();

    //Input text iterators
    std::string input_text = "TEST THIS";
    auto input_text_start = input_text.begin();
    auto input_text_end = input_text.end();


    auto result = parse_search(search_string_start, search_string_end, input_text_start, input_text_end);

    auto test = lex(first);



    //Input test example "lo* could.{3}"

}