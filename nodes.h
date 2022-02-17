#ifndef LABB1_NODES_H
#define LABB1_NODES_H
//Dagen
#include <vector>
#include <string>

std::vector<std::string> search_result;

struct ASTNode{

    bool virtual evaluate(std::string::const_iterator first, std::string::const_iterator last) = 0;
    std::vector<ASTNode*> children;

    void add(ASTNode* child){
        children.push_back(child);
    }

};

struct Operand:ASTNode{

    char op;

    bool evaluate(std::string::const_iterator first, std::string::const_iterator last) override{
        return op == *first;

        for(auto it = first; it != last; it++)
        {
            if(*it== op) {
                return true;
            }
        }

        return false;
    }
};

struct String:ASTNode{


    bool evaluate(std::string::const_iterator first, std::string::const_iterator last) override{

        bool rhs = true;
        if(children.size() == 2)
        {
            children[1]->evaluate(first + 1, last);
        }
        else
            rhs = false;

        return rhs && children[0]->evaluate(first,last);
    }
};


struct Group:ASTNode{

    bool evaluate(std::string::const_iterator first, std::string::const_iterator last) override{


        return children[0]->evaluate(first,last);
    }
};


struct Search:ASTNode{

    bool evaluate(std::string::const_iterator first, std::string::const_iterator last) override{

        for(auto child:children){

            bool match = children[0]->evaluate(first,last);
            if(!match) {
                return false;
            }
        }
        return true;

    }

};







#endif //LABB1_NODES_H
