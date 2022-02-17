#ifndef LABB1_NODES_H
#define LABB1_NODES_H
//Dagen
#include <vector>
#include <string>

extern std::string::const_iterator input_first;
extern std::string::const_iterator input_last;

std::vector<std::string> search_result;

struct ASTNode{

    bool virtual evaluate() = 0;
    std::vector<ASTNode*> children;

};

struct Operand:ASTNode{

    char op;

    bool evaluate() override{
        for(auto it = input_first; it != input_last; it++)
        {
            if(*it== op) {
                return true;
            }
        }

        return false;
    }
};

struct String:ASTNode{

    bool evaluate() override{
        return children[0]->evaluate();
    }
};


struct Group:ASTNode{

    bool evaluate() override{

        return children[0]->evaluate();
    }
};


struct Search:ASTNode{

    bool evaluate() override{

        return children[0]->evaluate();

    }

};







#endif //LABB1_NODES_H
