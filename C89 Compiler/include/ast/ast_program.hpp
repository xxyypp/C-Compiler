#ifndef ast_program_hpp
#define ast_program_hpp

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <list>

class Top{
    using bindingMap = std::map<std::string, double >;
protected:
    mutable int index;
public:
    mutable bindingMap map;
    mutable bindingMap Opmap;
    mutable int makeNameNum = 0;
    mutable int paramIter = 4;

    std::string makeName(std::string in)const{
      return "_" + in + "_" + std::to_string(makeNameNum++);
    }

    Top(int _index = 0):index(_index){}

    virtual double GetIndex(){
      return index;
    }

    virtual void IncrementIndex(){
      index = index +4;
    }


};

class Program : public Top
{
public:

    Program(){}
    virtual void print() const {}
    virtual ~Program() {}
    virtual void printcode(Top *pt) const{
      //std::cout << "#Printcode Not implemented \n";
    }
    virtual void ReturnPrint(Top *pt) const{
      //std::cout << "#Returnprint Not implemented \n";
    }

    virtual void printdeclare(Top *pt) const{
      //std::cout << "#printdeclare Not implemented \n";
    }

    virtual void printnum(Top *pt) const{
      //std::cout << "#printNum Not implemented \n";
    }

    virtual const std::string getId() const {
      return 0;
    }

    virtual void printGlobal(Top *tp) const {
      //std::cout << "#printGlobal Not implemented " << '\n';
    }


};

class Program_Declear
    : public Program
{
private:
    const Program *pgm;
    const Program *other;
public:
    Program_Declear(const Program *_pgm, const Program *_other)
        : pgm(_pgm), other(_other)
    {}

    virtual void print() const override
    {
      std::cout << "im in progra declare \n";
      pgm->print();
      other->print();
    }

    virtual void printcode(Top *pt) const {
      pgm->printcode(pt);
      other->printcode(pt);


    }

    ~Program_Declear(){
      delete pgm;
      delete other;
    }
};

#endif
