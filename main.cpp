#include "lex.h"
#include "parse.h"
#include "nodes.h"
#include <iostream>
//Dagen


int main(){

    //search string iterators
    std::string search_string = "(Wat)";
    auto search_string_start = search_string.begin();
    auto search_string_end = search_string.end();

    std::string input_text = "Waterloo";
    std::string::const_iterator input_first = input_text.begin();
    std::string::const_iterator input_last = input_text.end();
    //Input text iterators
    //std::string input_text = "TEST THIS";
    //auto input_text_start = input_text.begin();
    //auto input_text_end = input_text.end();


    auto result = parse_search(search_string_start, search_string_end);

    if(result->evaluate(input_first,input_last))
    {
        std::cout<<"MATCH";
    }
    else
    {
        std::cout<<"EJ MATCH";
    }

    //Input test example "lo* could.{3}"

}