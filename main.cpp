#include "lex.h"
#include "parse.h"
#include "nodes.h"
#include <iostream>
//Dagen


void printTree(const std::string& prefix, ASTNode *node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "L__" );

        // print the value of the node
        std::cout << node->getNameFromNode() << std::endl;

        // enter the next tree level - left and right branch
        if(!node->children.empty()){

            printTree( prefix + (isLeft ? "|   " : "    "), node->children[0], true);

        }
        if(node->children.size() > 1){

            printTree( prefix + (isLeft ? "|   " : "    "), node->children[1], false);

        }
    }
}

void printTree(ASTNode* node)
{
    printTree("", node, false);
}



int main(){

    //search string iterators
    std::string search_string = "lO*\\I";
    auto search_string_start = search_string.begin();
    auto search_string_end = search_string.end();

    std::string input_text = "waterloo";
    std::string::iterator input_first = input_text.begin();
    std::string::iterator input_last = input_text.end();
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
    std::cout<<std::endl;

    printTree(result);


    //Input test example "lo* could.{3}"*/


}


