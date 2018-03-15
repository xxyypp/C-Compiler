#ifndef ast_operator_hpp
#define ast_operator_hpp

#include <string>
#include <iostream>

class OperatorProgram
    : public Program
{
private:
    const Program *pgm1;
    const std::string *str;
    const Program *pgm2;
public:
    OperatorProgram(const Program *_pgm1,const std::string *_str, const Program *_pgm2)
        : pgm1(_pgm1),str(_str),pgm2(_pgm2)
    {}

    virtual void print() const override
    {
      pgm1->print();
      pgm2->print();
    }

    ~OperatorProgram(){
      delete pgm1;
      delete pgm2;
    }
};

// class Operator
//     : public Program
// {
// private:
//     const Program *left;
//     const Program *right;
// protected:
//     Operator(const Program *_left, const Program *_right)
//         : left(_left)
//         , right(_right)
//     {}
// public:
//
//     virtual ~Operator()
//     {
//         delete left;
//         delete right;
//     }
//
//     virtual const char *getOpcode() const =0;
//
//     const Program *getLeft() const
//     { return left; }
//
//     const Program *getRight() const
//     { return right; }
//
//     virtual void print() const override
//     {
//     }
// };
//
// class AddOperator
//     : public Operator
// {
// protected:
//     virtual const char *getOpcode() const override
//     { return "+"; }
// public:
//     AddOperator(const Program *_left, const Program *_right)
//         : Operator(_left, _right)
//     {}
//
//
// };
//
// class SubOperator
//     : public Operator
// {
// protected:
//     virtual const char *getOpcode() const override
//     { return "-"; }
// public:
//     SubOperator(const Program *_left, const Program *_right)
//         : Operator(_left, _right)
//     {}
//
// };
//
// class MulOperator
//     : public Operator
// {
// protected:
//     virtual const char *getOpcode() const override
//     { return "*"; }
// public:
//     MulOperator(const Program *_left, const Program *_right)
//         : Operator(_left, _right)
//     {}
//
// };
//
// class DivOperator
//     : public Operator
// {
// protected:
//     virtual const char *getOpcode() const override
//     { return "/"; }
// public:
//     DivOperator(const Program *_left, const Program *_right)
//         : Operator(_left, _right)
//     {}
//
//
//     };

#endif
