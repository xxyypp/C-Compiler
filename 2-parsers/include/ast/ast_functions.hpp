#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expression.hpp"

#include <cmath>

class Function
    : public Expression
{
private:
    const Expression *arg;
protected:
    Function(const Expression *_arg)
        : arg(_arg)
    {}
public:

    virtual ~Function()
    {
        delete arg;
    }

    virtual const char * getFunction() const =0;

    const Expression *getArg() const
    { return arg; }

    virtual void print() const override
    {
        std::cout<<getFunction()<<"( ";
        arg->print();
        std::cout<<" )";
    }
    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const
    {
      if(getFunction() == "log"){
        return log(arg->evaluate(bindings));
      }else if(getFunction() == "exp"){
        return exp(arg->evaluate(bindings));
      }else if(getFunction() == "sqrt"){
        return sqrt(arg->evaluate(bindings));
      }
    }

  /*  virtual const Expression *differentiate(
        const std::string &variable
    ) const
    {
      if(getFunction() == "log"){
        // std::cout << " 1/( ";
        // getArg()->print();
        // std::cout << " ) ";
        // std::cout << " * ";
        return(new MulOperator(new DivOperator(new Number(1),getArg()),getArg()->differentiate(variable)));
      }else if(getFunction() == "exp"){
        // std::cout << getFunction() <<"(";
        // getArg()->print();
        // std::cout << ") ";
        // std::cout << "* ";
        return(new MulOperator(new ExpFunction(getArg()),getArg()->differentiate(variable)));
      }else if(getFunction() == "sqrt"){
        //std::cout << " 1/2 *  ";
        // std::cout << " 1/sqrt( ";
        // getArg()->print();
        // std::cout << " ) ";
        // std::cout << " * ";
        return(new DivOperator(getArg()->differentiate(variable),new MulOperator(new Number(2),new SqrtFunction(getArg()))));
      }
    }*/

};

class LogFunction
    : public Function
{
public:
    LogFunction(const Expression *_arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "log"; }

    virtual const Expression *differentiate(
        const std::string &variable
    ) const{
      return(new MulOperator(new DivOperator(new Number(1),getArg()),getArg()->differentiate(variable)));
    }

};

class ExpFunction
    : public Function
{
public:
    ExpFunction(const Expression *_arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "exp"; }

    virtual const Expression *differentiate(
        const std::string &variable
    ) const{
      return(new MulOperator(new ExpFunction(getArg()),getArg()->differentiate(variable)));
    }
};

class SqrtFunction
    : public Function
{
public:
    SqrtFunction(const Expression *_arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "sqrt"; }

    virtual const Expression *differentiate(
        const std::string &variable
    ) const{
      return(new DivOperator(getArg()->differentiate(variable),new MulOperator(new Number(2),new SqrtFunction(getArg()))));
    }
};


#endif
