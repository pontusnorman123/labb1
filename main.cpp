#include "lex.h"
#include "parse.h"
#include "nodes.h"
#include <iostream>
#include <string>
#include<stdio.h>
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

    /*
    // För att ange i terminalen vad man söker.
    // Observera att det räcker med ett st "\" inte två som cpp kräver.
    std::string name;
    char nm[20];
    gets(nm);
    std::cout<<nm<<std::endl;
    std::string search_string = nm;
    */

    // Kommentera bort för att ovanstående ska fungera.
    std::string search_string = "(Wat)(er)\\O{1}";
    auto search_string_start = search_string.begin();
    auto search_string_end = search_string.end();

    std::string input_text = "Waterloo I was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";

    std::string::iterator input_first = input_text.begin();
    std::string::iterator input_last = input_text.end();


    auto result = parse_search(search_string_start, search_string_end);


    if(result->evaluate(input_first,input_last))
    {
        std::cout<<" MATCH";
    }
    else
    {
        std::cout<<"EJ MATCH";
    }

    std::cout<<std::endl;

    printTree(result);


    //Waterloo I was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't esc"
    //                             "ape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo"


}


