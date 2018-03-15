#ifndef ast_init_declar_hpp
#define ast_init_declar_hpp

#include <string>
#include <iostream>

class InitDeclar
    : public Program
{
private:
    const Program *pgm1;
    const Program *pgm2;
public:
    InitDeclar(const Program *_pgm1, const Program *_pgm2)
        : pgm1(_pgm1),pgm2(_pgm2)
    {}

    virtual void print() const override
    {
      //pgm1->print();
      pgm1->print();
    }

    ~InitDeclar(){
      delete pgm1;
      delete pgm2;

    }
};


#endif
