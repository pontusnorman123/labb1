#ifndef LABB1_NODES_H
#define LABB1_NODES_H
//Dagen
#include <vector>
#include <string>

std::string search_result;

struct ASTNode{


    bool virtual evaluate(std::string::iterator &first, std::string::const_iterator last) = 0;
    std::vector<ASTNode*> children;

    void add(ASTNode* child){
        if(child != nullptr)
        {
            children.push_back(child);
        }
    }


    std::string virtual getNameFromNode() = 0;

};

struct Char:ASTNode{

    char ch;

    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override{


        if(ch == (*first) || ch == '.')
        {
            search_result.push_back(*first);
            return true;
        }
        search_result.clear();
        return false;


    }

    std::string getNameFromNode() override{
        return std::string(1,ch);
    }
};

struct IgnoreCaseChar:ASTNode{

    char ch;

    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override{

        char lower_ch = tolower(*first);
        if(ch == lower_ch || ch == '.')
        {
            search_result.push_back(lower_ch);
            return true;
        }
        search_result.clear();
        return false;

    }

    std::string getNameFromNode() override{
        return std::string(1,ch);
    }
};

struct IgnoreCaseGroup:ASTNode{
    std::string getNameFromNode() override{
        return "IGNORE_CASE_GROUP";
    }

    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override {

        return children[0]->evaluate(first, last);
    }
};

struct IgnoreCaseString:ASTNode{
    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override{

        bool rhs = true;
        bool lhs = children[0]->evaluate(first,last);

        if(!lhs)
        {
            return false;
        }

        if(children.size() == 2)
        {
            rhs = children[1]->evaluate(++first, last);
        }


        return lhs && rhs;
    }

    std::string getNameFromNode() override{
        return "IGNORE_CASE_STRING";
    }
};

struct IgnoreCaseCounter:ASTNode{

    int counter;

    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override{

        bool lhs = false;

        for(int i = 0; i < counter; i++)
        {
            lhs = children[0]->evaluate(first,last);
            first++;
        }
        //pekarn hoppar ett steg f??r mkt
        first--;

        return lhs;
    }

    std::string getNameFromNode() override{

        std::string return_counter = std::to_string(counter);
        return "COUNTER " + return_counter;
    }

};

struct IgnoreCaseOr:ASTNode{

    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override{

        auto tmp = search_result;

        bool lhs = children[0]->evaluate(first,last);

        if(lhs)
        {
            return true;
        }

        search_result = tmp;
        return children[1]->evaluate(first,last);

    }

    std::string getNameFromNode() override{
        return "IGNORE-CASE-OR";
    }
};

struct IgnoreCase:ASTNode{

    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override{
        return children[0]->evaluate(first,last);
    }

    std::string getNameFromNode() override{
        return "IGNORE_CASE";
    }
};

struct IgnoreCaseRepeat:ASTNode{

    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override{

        bool lhs = false;
        std::string tmp;


        while(children[0]->evaluate(first,last) && first != last)
        {
            tmp = search_result;
            first++;
            lhs = true;
        }

        search_result = tmp;

        //Pekarn hoppar ett steg f??r mkt
        first--;

        bool rhs = true;

        if(!lhs)
        {
            return false;
        }

        if(children.size() == 2)
        {
            rhs = children[1]->evaluate(++first, last);
        }

        return lhs && rhs;

    }

    std::string getNameFromNode() override{
        return "IGNORE-CASE-REPEAT";
    }

};

struct Repeat:ASTNode{

    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override {

        bool lhs = false;
        std::string tmp;

        while(children[0]->evaluate(first,last) && first != last)
        {
            //loopen orsakar alltid att search_result raderas s?? sparas tempor??rt
            tmp = search_result;
            first++;
            lhs = true;
        }

        search_result = tmp;

        //Pekarn hoppar ett steg f??r mkt
        first--;

        bool rhs = true;

        if(!lhs)
        {
            return false;
        }

        if(children.size() == 2)
        {
            rhs = children[1]->evaluate(++first, last);
        }

        return lhs && rhs;


    }

    std::string getNameFromNode() override{
        return "REPEAT";
    }
};

struct String:ASTNode{

    std::string getNameFromNode() override{
        return "STRING";
    }

    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override{

        bool rhs = true;
        bool lhs = children[0]->evaluate(first,last);

        if(!lhs)
        {
            return false;
        }

        if(children.size() == 2)
        {
            rhs = children[1]->evaluate(++first, last);
        }


        return lhs && rhs;
    }
};

struct Counter:ASTNode{

    int counter;

    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override{

        bool lhs = false;

        for(int i = 0; i < counter; i++)
        {
            lhs = children[0]->evaluate(first,last);
            first++;
        }
        //pekarn hoppar ett steg f??r mkt
        first--;

        return lhs;
    }

    std::string getNameFromNode() override{

        std::string return_counter = std::to_string(counter);
        return "COUNTER (" + return_counter + ")";
    }
};


struct Group:ASTNode{

    std::string getNameFromNode() override{
        return "GROUP";
    }

    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override {

         return children[0]->evaluate(first, last);
    }
};

struct IgnoreCaseExpr:ASTNode{

    std::string getNameFromNode() override{
        return "IGNORE_CASE_EXPR";
    }


    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override{
        bool rhs = true;
        bool lhs = children[0]->evaluate(first,last);

        if(!lhs)
        {
            return false;
        }

        if(children.size() == 2)
        {
            rhs = children[1]->evaluate(++first, last);
        }


        return lhs && rhs;
    }
};

struct Expr:ASTNode{

    std::string getNameFromNode() override{
        return "EXPR";
    }


    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override{
        bool rhs = true;
        bool lhs = children[0]->evaluate(first,last);

        if(!lhs)
        {
            return false;
        }

        if(children.size() == 2)
        {
            rhs = children[1]->evaluate(++first, last);
        }


        return lhs && rhs;
    }

};

struct Or:ASTNode{

    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override{

        auto tmp = search_result;

        bool lhs = children[0]->evaluate(first,last);

        if(lhs)
        {
            return true;
        }

        search_result = tmp;
        return children[1]->evaluate(first,last);

    }

    std::string getNameFromNode() override{
        return "OR";
    }
};

struct GroupOut:ASTNode{

    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override{

        return children[0]->evaluate(first,last);
    }

    std::string getNameFromNode() override{
        return "GROUP-OUT";
    }
};

struct AllOut:ASTNode{

    std::string getNameFromNode() override{
        return "All-OUT";
    }


    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override{
        return children[0]->evaluate(first,last);
    }
};


struct Search:ASTNode{

    std::string getNameFromNode() override{
        return "SEARCH";
    }

    bool evaluate(std::string::iterator &first, std::string::const_iterator last) override{

        for(auto it = first; it != last; it++)
        {
            first = it;
            if(children[0]->evaluate(first,last))
            {
                std::cout<<search_result;
                return true;
            }
        }
        return false;

    }

};







#endif //LABB1_NODES_H
