#ifndef ast_variable_num_hpp
#define ast_variable_num_hpp
#include "ast.hpp"
#include <string>
#include <iostream>


class Variable
    : public Program
{
private:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    const std::string getId() const
    { return id; }

    virtual void print() const override
    {
        std::cout << id;
    }

    virtual void printcode(Top *pt) const override{
       //int index = pt->GetIndex();
       //std::cout << "sw $0 , " << index << "($sp)" << '\n';
       //std::cout << "#hello -------------------*************************" << '\n';
    }

    virtual void ReturnPrint(Top *pt) const override{
      //std::cout << "#pt map id is: " << id << '\n';
    //  std::cout << "#pt map[id] is: " << pt->map[id] << '\n';
      std::cout << "lw $2, " << pt->map[id] << "($sp)" << '\n';
    }

    virtual void printdeclare (Top *pt) const override{
      std::cout << "lw $t1, " << pt->map[id] << "($sp)" << '\n';
    }

    ~Variable(){
    }
};

class Dec_Spec_Two
    : public Program
{
private:
    std::string id1;
    std::string id2;
public:
    Dec_Spec_Two(const std::string &_id1,const std::string &_id2)
        : id1(_id1),id2(_id2)
    {}

    virtual void print() const override
    {
        std::cout << id1;
        std::cout << id2;
    }

    ~Dec_Spec_Two(){
    }
};

class Number
    : public Program
{
private:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    double getValue() const
      { return value; }

    virtual void print() const override
    {
      //double val = getValue();
      //std::cout << "addiu $2,$2," << val << "\n" ;
        std::cout<<value;
    }

    virtual void printcode(Top *pt) const override
    {
      double val = getValue();
      std::cout << "addiu $t1,$0," << val << "\n" ;
    }

    virtual void printnum(Top *pt) const override
    {
      double val = getValue();
      std::cout << "addiu $t1,$0," << val << "\n" ;
    }

    virtual void ReturnPrint(Top *pt) const override{
      double val = getValue();
      std::cout << "addi $t0, $0, " << val << '\n';
      std::cout << "move $2, $t0" << '\n';
    }


    virtual void printdeclare (Top *pt) const override{
      double val = getValue();
      std::cout << "addiu $t1,$0," << val << '\n';
    }

};
class INC_OP
    : public Program
{
private:
    const Program *pgm1;
    const std::string *opcode;
public:
    INC_OP(const Program *_pgm1, const std::string *_opcode)
        : pgm1(_pgm1), opcode(_opcode)
    {}

      virtual void printcode(Top *pt) const override{
        std::cout << "#_______________________________-" << '\n';
        pgm1->printcode(pt);
        std::cout << "#+++++++++++++++++++++++++++" << '\n';

      }

    ~INC_OP(){
      delete pgm1;
    }
};


#endif
