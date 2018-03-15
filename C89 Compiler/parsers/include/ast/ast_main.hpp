#ifndef ast_main_hpp
#define ast_main_hpp

#include <string>
#include <iostream>
#include <map>
#include <vector>

class Program
{
public:

    //virtual void print() const =0;
    virtual void print() const {
    }

    Program()
    {  }
    virtual ~Program()
    { }


};

class ProgramOther
    : public Program
{
private:
    const Program *pgm;
    const Program *other;
public:
    ProgramOther(const Program *_pgm, const Program *_other)
        : pgm(_pgm), other(_other)
    {}

    virtual void print() const override
    {
      pgm->print();
      other->print();
    }

    ~ProgramOther(){
      delete pgm;
      delete other;
    }
};

#endif
