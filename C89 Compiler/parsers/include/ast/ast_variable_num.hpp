#ifndef ast_variable_num_hpp
#define ast_variable_num_hpp
#include "ast.hpp"
#include <string>
#include <iostream>


class Variable
    : public Program
{
private:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    const std::string getId() const
    { return id; }

    virtual void print() const override
    {
        std::cout << id;
    }

    ~Variable(){
    }
};

class Dec_Spec_Two
    : public Program
{
private:
    std::string id1;
    std::string id2;
public:
    Dec_Spec_Two(const std::string &_id1,const std::string &_id2)
        : id1(_id1),id2(_id2)
    {}

    virtual void print() const override
    {
        std::cout << id1;
        std::cout << id2;
    }

    ~Dec_Spec_Two(){
    }
};

class Number
    : public Program
{
private:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    virtual void print() const override
    {
      //  std::cout<<value;
    }
};

#endif
