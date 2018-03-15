#ifndef ast_assign_hpp
#define ast_assign_hpp
#include "ast.hpp"
#include <string>
#include <iostream>


class Assign
    : public Program
{
private:
    const Program *pgm1;
    const std::string *id;
    const Program *pgm2;
public:
    Assign(const Program *_pgm1,const std::string *_id,const Program *_pgm2)
        : pgm1(_pgm1),id(_id),pgm2(_pgm2)
    {}

    virtual void print() const override
    {
        pgm1->print();
        pgm2->print();
    }

    ~Assign(){
      delete pgm1;
      delete pgm2;
    }
};

class Postfix
    : public Program
{
private:
    const Program *pgm1;
public:
    Postfix(const Program *_pgm1)
        : pgm1(_pgm1)
    {}

    virtual void print() const override
    {
      pgm1->print();
    }

    ~Postfix(){
      delete pgm1;
    }
};


#endif
