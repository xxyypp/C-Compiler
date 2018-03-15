#include "ast.hpp"

static std::vector<std::string> Tokenise(std::istream &src)
//Turns an input caracter stream into a s equence of tokens, simply by splitting on whitespace
{
    std::vector<std::string> res;
    std::string tmp;
    while(src >> tmp){
        res.push_back(tmp);
    }
    return res;
}

static std::pair<TreePtr,int> ParseImpl(const std::vector<std::string> &tokens, int pos)
{
    std::string type;//what type of node it is, or the name/value
    std::string value; //an optional string representing a value at this node
    std::vector<TreePtr> branches; // a vector of zero or more sub-trees

    type=tokens.at(pos++);

    if(pos < tokens.size()){
        if(tokens.at(pos)==":"){
            pos++;

            value=tokens.at(pos++);
        }
    }

    if(pos < tokens.size()){
        if(tokens.at(pos)=="["){
            pos++;

            while(tokens.at(pos)!="]"){
                auto sub=ParseImpl(tokens, pos);
                branches.push_back( sub.first );
                pos=sub.second;
            }

            pos++; // skip ']'
        }
    }

    return std::make_pair(std::make_shared<Tree>(type, value, branches),pos);
}

TreePtr Parse(std::istream &src)
//recursive-decent parser which implements a complete parser in ~40 lines of code
{
    auto tokens=Tokenise(src);
    return ParseImpl(tokens, 0).first;
}
