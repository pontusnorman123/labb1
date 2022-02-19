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

struct Char:ASTNode{

    char ch;

    bool evaluate(std::string::const_iterator first, std::string::const_iterator last) override{
        return ch == *first || ch == '.';

    }
};

struct String:ASTNode{


    bool evaluate(std::string::const_iterator first, std::string::const_iterator last) override{

        bool rhs = true;
        bool lhs = children[0]->evaluate(first,last);

        if(!lhs)
        {
            return false;
        }

        if(children.size() == 2)
        {
            rhs = children[1]->evaluate(first + 1, last);
        }


        return lhs && rhs;
    }
};


struct Group:ASTNode{

    bool evaluate(std::string::const_iterator first, std::string::const_iterator last) override{

        return children[0]->evaluate(first,last);
    }
};


struct Search:ASTNode{


    bool evaluate(std::string::const_iterator first, std::string::const_iterator last) override{

        for(; first != last; first++)
        {
            if(children[0]->evaluate(first,last))
            {
                return true;
            }
        }
        return false;
        /*
        for(auto child:children){

            bool match = children[0]->evaluate(first,last);
            if(!match) {
                return false;
            }
        }
        return true;
        */
    }

};







#endif //LABB1_NODES_H
