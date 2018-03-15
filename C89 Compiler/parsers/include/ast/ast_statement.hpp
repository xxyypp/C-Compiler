#ifndef ast_statement_hpp
#define ast_statement_hpp

#include <string>
#include <iostream>

class Two_Program_Expr
    : public Program
{
private:
    const Program *pgm1;
    const Program *pgm2;
public:
    Two_Program_Expr(const Program *_pgm1, const Program *_pgm2)
        : pgm1(_pgm1),pgm2(_pgm2)
    {}

    virtual void print() const override
    {
      pgm1->print();
      pgm2->print();
    }

    ~Two_Program_Expr(){
      delete pgm1;
      delete pgm2;
    }
};

class If_Stat
    : public Program
{
private:
    const Program *pgm1;
    //const Program *pgm2;
public:
    If_Stat(const Program *_pgm1)
        : pgm1(_pgm1)
    {}

    virtual void print() const override
    {
      std::cout << "<Scope> \n";
      pgm1->print();
      std::cout << "</Scope> \n";
    }

    ~If_Stat(){
      delete pgm1;
    }
};

class Else_Stat
    : public Program
{
private:
    const Program *pgm1;
    const Program *pgm2;
public:
    Else_Stat(const Program *_pgm1, const Program *_pgm2)
        : pgm1(_pgm1),pgm2(_pgm2)
    {}

    virtual void print() const override
    {
      std::cout<< "<Scope> \n";
      pgm1->print();
      std::cout << "</Scope> \n";
      std::cout<< "<Scope> \n";
      pgm2->print();
      std::cout << "</Scope> \n";
    }

    ~Else_Stat(){
      delete pgm1;
      delete pgm2;
    }
};

class While_Stat
    : public Program
{
private:
    const Program *pgm1;
    //const Program *pgm2;
public:
    While_Stat(const Program *_pgm1)
        : pgm1(_pgm1)
    {}

    virtual void print() const override
    {
      std::cout<< "<Scope> \n";
      pgm1->print();
      std::cout << "</Scope> \n";
    }

    ~While_Stat(){
      delete pgm1;
    }
};

class For_Stat
    : public Program
{
private:
    const Program *pgm1;
    const Program *pgm2;
    const Program *pgm3;

public:
    For_Stat(const Program *_pgm1, const Program *_pgm2,const Program *_pgm3)
        : pgm1(_pgm1),pgm2(_pgm2),pgm3(_pgm3)
    {}

    virtual void print() const override
    {
      pgm1->print();
      pgm2->print();
      std::cout<< "<Scope> \n";
      pgm3->print();
      std::cout << "</Scope> \n";
    }

    ~For_Stat(){
      delete pgm1;
      delete pgm2;
      delete pgm3;
    }
};

class For_Stat_Four
    : public Program
{
private:
    const Program *pgm1;
    const Program *pgm2;
    const Program *pgm3;
    const Program *pgm4;

public:
    For_Stat_Four(const Program *_pgm1, const Program *_pgm2,const Program *_pgm3,const Program *_pgm4)
        : pgm1(_pgm1),pgm2(_pgm2),pgm3(_pgm3),pgm4(_pgm4)
    {}

    virtual void print() const override
    {
      std::cout<< "<Parameter> \n";
      pgm1->print();
      pgm2->print();
      pgm3->print();
      std::cout << "</Parameter> \n";
      std::cout<< "<Scope> \n";
      pgm4->print();
      std::cout << "</Scope> \n";
    }

    ~For_Stat_Four(){
      delete pgm1;
      delete pgm2;
      delete pgm3;
      delete pgm4;
    }
};

#endif
