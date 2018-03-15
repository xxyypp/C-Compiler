#ifndef ast_declear_hpp
#define ast_declear_hpp

#include <string>
#include <iostream>
#include <map>

class Global_Declear
    : public Program
{
private:
    const Program *pgm;
public:
    Global_Declear(const Program *_pgm)
        : pgm(_pgm)
    {}

    virtual void print() const override
    {
      pgm->print();
      std::cout << '\n';
    }

    virtual void printcode(Top *pt) const override{
      pgm->printGlobal(pt);
    }


    ~Global_Declear(){
      delete pgm;
    }
};

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
      pgm->print();
      std::cout << '\n';
    }

    virtual void printcode(Top *pt) const override{
      pgm->printcode(pt);
    }

    virtual void printGlobal(Top *pt) const override{
      pgm->printGlobal(pt);
    }

    ~Declear(){
      delete pgm;
    }
};



class InitDeclar_1
    : public Program
{
private:
    const Program *pgm1;
public:
    InitDeclar_1(const Program *_pgm1)
        : pgm1(_pgm1)
    {}

    virtual void print() const override
    {
      //pgm1->print();
      pgm1->print();
    }

    virtual void printcode(Top *pt) const override{
      int index = pt->GetIndex();
      std::cout << "sw $0 , " << index << "($sp)" << '\n';

      std::string str = pgm1->getId();
      pt->map.insert(std::pair<std::string,int>(str,index));
      pt->IncrementIndex();
    }

    virtual void printGlobal(Top *pt) const override{
      std::cout << ".globl ";
      pgm1->print();
      std::cout << '\n';

      std::cout << ".type ";
      pgm1->print();
      std::cout << ", @object" << '\n';

      std::cout << ".size ";
      pgm1->print();
      std::cout << ", 4 \n";

      pgm1->print();
      std::cout << ":" << '\n';

      std::cout << ".space 4" << '\n';

      int index = pt->GetIndex();
      //std::cout << "sw $0 , " << index << "($sp)" << '\n';

      std::string str = pgm1->getId();
      std::cout << "#str is: " << str << '\n';
      pt->map.insert(std::pair<std::string,int>(str,index));
      pt->IncrementIndex();


    }

    ~InitDeclar_1(){
      delete pgm1;

    }
};

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
      pgm1->print();
    }

    virtual void printcode(Top *pt) const override
    {
      int index = pt->GetIndex();
      //std::cout << "sw $0 , " << index << "($sp)" << '\n';

      std::string str = pgm1->getId();
      pt->map.insert(std::pair<std::string,int>(str,index));
      pgm2->printdeclare(pt);
      std::cout << "sw $t1, " << pt->map[str] << "($sp)" << '\n';
      pt->IncrementIndex();
    }


    virtual void printGlobal(Top *pt) const override{
      std::cout << ".globl ";
      pgm1->printcode(pt);
      std::cout << '\n';

      std::cout << ".type ";
      pgm1->printcode(pt);
      std::cout << ", @object" << '\n';

      std::cout << ".size ";
      pgm1->printcode(pt);
      std::cout << ", 4";

      pgm1->printcode(pt);
      std::cout << ":" << '\n';

      std::cout << ".space 4" << '\n';
      int index = pt->GetIndex();
      //std::cout << "sw $0 , " << index << "($sp)" << '\n';

      std::string str = pgm1->getId();
      pt->map.insert(std::pair<std::string,int>(str,index));
      pgm2->printdeclare(pt);
      //std::cout << "sw $t1, " << pt->map[str] << "($sp)" << '\n';
      pt->IncrementIndex();

      pgm2->printGlobal(pt);
      }

    virtual void printdeclare(Top *pt) const override{
      pgm2->printdeclare(pt);
    }
    ~InitDeclar(){
      delete pgm1;
      delete pgm2;

    }
};

class Init_Dec_List
    : public Program
{
private:
    const Program *pgm1;
    const Program *pgm2;
public:
    Init_Dec_List(const Program *_pgm1, const Program *_pgm2)
        : pgm1(_pgm1),pgm2(_pgm2)
    {}

    virtual void print() const override
    {
      pgm1->print();
      pgm2->print();
    }

    ~Init_Dec_List(){
      delete pgm1;
      delete pgm2;

    }
};



class Declar_array
    : public Program
{
private:
    const Program *pgm;
public:
    Declar_array(const Program *_pgm)
        : pgm(_pgm)
    {}

    virtual void print() const override
    {
    //  std::cout << "<Variable id =\"";
      pgm->print();
      //std::cout << "\" />" << '\n';
    }

    ~Declar_array(){
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
