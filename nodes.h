#ifndef LABB1_NODES_H
#define LABB1_NODES_H

#include <vector>
#include <string>

std::vector<std::string> search_result;

struct ASTNode{
    bool virtual evaluate() = 0;
    std::vector<ASTNode*> children;

};

struct Operand:ASTNode{
    char op;
    bool evaluate() override{

    }
};

struct GroupOut:ASTNode{

};

struct Search:ASTNode{
    bool evaluate() override{
        auto group_out_node = dynamic_cast<GroupOut*>(children[0]);
        return
    }

};


struct Expression:ASTNode{

};


struct String:ASTNode{

};




#endif //LABB1_NODES_H
