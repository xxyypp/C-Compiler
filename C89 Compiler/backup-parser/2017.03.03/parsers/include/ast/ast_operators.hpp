#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>
/*
class Operator
    : public Program
{
private:
    const Expression *left;
protected:
    Operator(const Expression *_left)
        : left(_left)
    {
      std::cout << "constructor in operator(function)"
    }
public:

    virtual ~Operator()
    {
      std::cout << "destructor in operator(function)"
        delete left;
    }

    virtual const char *getOpcode() const =0;

    const Expression *getLeft() const
    { return left; }

    const Expression *getRight() const
    { return right; }

    virtual void print() const override
    {
        std::cout<<"( ";
        left->print();
        std::cout<<" ";
        std::cout<<getOpcode();
        std::cout<<" ";
        right->print();
        std::cout<<" )";
    }
};

class AddOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    AddOperator(const Expression *_left)
        : Operator(_left)
    {std::cout << "constructor in AddOperator(Parameter)"}
};

class SubOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "-"; }
public:
    SubOperator(const Expression *_left, const Expression *_right)
        : Operator(_left, _right)
    {}
};

class MulOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "*"; }
public:
    MulOperator(const Expression *_left, const Expression *_right)
        : Operator(_left, _right)
    {}
    virtual double evaluate(
          const std::map<std::string,double> &bindings
    ) const{
        return (getLeft()->evaluate(bindings) * getRight()->evaluate(bindings));
    }

    virtual const Expression *differentiate(
        const std::string &variable
    ) const
    {
      return (new AddOperator(new MulOperator(getLeft()->differentiate(variable),getRight()),new MulOperator(getLeft(),getRight()->differentiate(variable))));
    }
};

class DivOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "/"; }
public:
    DivOperator(const Expression *_left, const Expression *_right)
        : Operator(_left, _right)
    {}
      virtual double evaluate(
            const std::map<std::string,double> &bindings
      ) const{
          return (getLeft()->evaluate(bindings) / getRight()->evaluate(bindings));
      }

      virtual const Expression *differentiate(
          const std::string &variable
      ) const
      {
        return (new DivOperator(new SubOperator(new MulOperator(getLeft()->differentiate(variable),getRight()),new MulOperator(getLeft(),getRight()->differentiate(variable))),new MulOperator(getRight(),getRight())));

      }

    };

#endif
