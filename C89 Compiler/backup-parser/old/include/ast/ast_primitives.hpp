#ifndef ast_primitives_hpp
#define ast_primitives_hpp
#include "ast.hpp"
#include <string>
#include <iostream>

class Number
    : public Expression
{
private:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    double getValue() const
    { return value; }

    virtual void print() const override
    {
        std::cout<<value;
    }
    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const
    {
      return value;
    }
    virtual const Expression *differentiate(
        const std::string &variable
    ) const
    {
      return (new Number(0));
    }

};

class Variable
    : public Expression
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
        std::cout<<id;
    }
    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const
    {
      for(auto it = bindings.cbegin(); it != bindings.cend(); ++it){
       auto fd = bindings.find(id);
       if (fd != bindings.end()){
         return fd->second;
       }
      }
    }

    virtual const Expression *differentiate(
        const std::string &variable
    ) const
    {
      if (id == variable){
          //std::cout << "1";
          return (new Number(1));
      } else{
          //std::cout << "0";
          return (new Number(0));
      }
    }

};
#endif
