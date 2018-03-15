#ifndef ast_declear_hpp
#define ast_declear_hpp

#include <string>
#include <iostream>
#include <map>

class Declear
    : public Program
{
private:
    const Program *pgm;
public:
    Declear(const Program *_pgm)
        : pgm(_pgm)
    {}

    virtual void print() const override
    {
      std::cout << "<Variable id =\"";
      pgm->print();
      std::cout << "\" />" << '\n';
    }

    ~Declear(){
      delete pgm;
    }
};

class Declare_Declare
    : public Program
{
private:
    const Program *pgm1;
    const Program *pgm2;
public:
    Declare_Declare(const Program *_pgm1, const Program *_pgm2)
        : pgm1(_pgm1),pgm2(_pgm2)
    {}

    virtual void print() const override
    {
      pgm1->print();
      pgm2->print();
    }

    ~Declare_Declare(){
      delete pgm1;
      delete pgm2;
    }
};
#endif
