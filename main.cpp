#include "lex.h"
#include "parse.h"
#include "nodes.h"
#include <iostream>
//Dagens
std::string input_text = "ES HTIS";
std::string::const_iterator input_first;
std::string::const_iterator input_last;

int main(){

    //search string iterators
    std::string search_string = "(T)";
    auto search_string_start = search_string.begin();
    auto search_string_end = search_string.end();

    input_first = input_text.begin();
    input_last = input_text.end();
    //Input text iterators
    //std::string input_text = "TEST THIS";
    //auto input_text_start = input_text.begin();
    //auto input_text_end = input_text.end();


    auto result = parse_search(search_string_start, search_string_end);

    if(result->evaluate())
    {
        std::cout << "FINNS!";
    }
    else{
        std::cout<< "INTE FINNS!";
    }


    //Input test example "lo* could.{3}"

}