#ifndef LABB1_NODES_H
#define LABB1_NODES_H

#include <vector>

struct ASTNode{
    bool virtual evaluate() = 0;
    std::vector<ASTNode*> operands;

};

struct or_op:ASTNode{

};




#endif //LABB1_NODES_H
