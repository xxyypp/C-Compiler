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

    virtual void printcode(Top *pt) const override
    {
        pgm1->printcode(pt);
        pgm2->printcode(pt);
    }

    ~Assign(){
      delete pgm1;
      delete pgm2;
    }
};

class Assign_Expr
    : public Program
{
private:
    const Program *pgm1;
    const std::string *str;
    const Program *pgm2;
public:
    Assign_Expr(const Program *_pgm1,const std::string *_str, const Program *_pgm2)
        : pgm1(_pgm1),str(_str),pgm2(_pgm2)
    {}

    virtual void print() const override
    {
      //std::cout << "#in Assign_Expr" << '\n';
      pgm1->print();
      pgm2->print();
    }

    virtual void printcode(Top *pt) const override
    {
      //std::cout << "#in Assign_Expr 1" << '\n';
      if(*str == "="){
        pgm1->printcode(pt);

        int tmp = pt->GetIndex();
        std::string str = pgm1->getId();
        pt->map.insert(std::pair<std::string, int>(str,tmp));
        pt->IncrementIndex();

        pgm2->printdeclare(pt);
        std::cout << "sw $t1, " << pt->map[str] << "($sp)" << '\n';
      }else if(*str == "+="){
        pgm1->printcode(pt);

        int tmp = pt->GetIndex();
        std::string str = pgm1->getId();
        pt->map.insert(std::pair<std::string, int>(str,tmp));
        pt->IncrementIndex();

        pgm2->printdeclare(pt);
        std::cout << "lw $t2, " << pt->map[str] << "($sp)" << '\n';
        std::cout << "add $t1, $t1, $t2" << '\n';
        std::cout << "sw $t1, " << pt->map[str] << "($sp)" << '\n';
      }else if(*str == "-="){
        pgm1->printcode(pt);

        int tmp = pt->GetIndex();
        std::string str = pgm1->getId();
        pt->map.insert(std::pair<std::string, int>(str,tmp));
        pt->IncrementIndex();

        pgm2->printdeclare(pt);
        std::cout << "lw $t2, " << pt->map[str] << "($sp)" << '\n';
        std::cout << "sub $t1, $t2, $t1" << '\n';
        std::cout << "/* message */" << '\n';
        std::cout << "sw $t1, " << pt->map[str] << "($sp)" << '\n';
      }else if(*str == "*="){
        pgm1->printcode(pt);

        int tmp = pt->GetIndex();
        std::string str = pgm1->getId();
        pt->map.insert(std::pair<std::string, int>(str,tmp));
        pt->IncrementIndex();

        pgm2->printdeclare(pt);
        std::cout << "lw $t2, " << pt->map[str] << "($sp)" << '\n';
        std::cout << "mult $t2, $t1" << '\n';
        std::cout << "mflo $t1" << '\n';
        std::cout << "sw $t1, " << pt->map[str] << "($sp)" << '\n';
      }else if(*str == "/="){
        pgm1->printcode(pt);

        int tmp = pt->GetIndex();
        std::string str = pgm1->getId();
        pt->map.insert(std::pair<std::string, int>(str,tmp));
        pt->IncrementIndex();

        pgm2->printdeclare(pt);
        std::cout << "lw $t2, " << pt->map[str] << "($sp)" << '\n';
        std::cout << "div $0, $t2, $t1" << '\n';
        std::cout << "mflo $t1" << '\n';
        std::cout << "sw $t1, " << pt->map[str] << "($sp)" << '\n';
      }else if(*str == "%="){
        pgm1->printcode(pt);

        int tmp = pt->GetIndex();
        std::string str = pgm1->getId();
        pt->map.insert(std::pair<std::string, int>(str,tmp));
        pt->IncrementIndex();

        pgm2->printdeclare(pt);
        std::cout << "lw $t2, " << pt->map[str] << "($sp)" << '\n';
        std::cout << "div $0, $t2, $t1" << '\n';
        std::cout << "mfhi $t1" << '\n';
        std::cout << "sw $t1, " << pt->map[str] << "($sp)" << '\n';
      }else if(*str == "<<="){
        pgm1->printcode(pt);

        int tmp = pt->GetIndex();
        std::string str = pgm1->getId();
        pt->map.insert(std::pair<std::string, int>(str,tmp));
        pt->IncrementIndex();

        pgm2->printdeclare(pt);
        std::cout << "lw $t2, " << pt->map[str] << "($sp)" << '\n';
        std::cout << "sll $t1, $t2, $t1" << '\n';
        std::cout << "sw $t1, " << pt->map[str] << "($sp)" << '\n';
      }else if(*str == ">>="){
        pgm1->printcode(pt);

        int tmp = pt->GetIndex();
        std::string str = pgm1->getId();
        pt->map.insert(std::pair<std::string, int>(str,tmp));
        pt->IncrementIndex();

        pgm2->printdeclare(pt);
        std::cout << "lw $t2, " << pt->map[str] << "($sp)" << '\n';
        std::cout << "sra $t1, $t2, $t1" << '\n';
        std::cout << "sw $t1, " << pt->map[str] << "($sp)" << '\n';
      }else if(*str == "|="){
        pgm1->printcode(pt);

        int tmp = pt->GetIndex();
        std::string str = pgm1->getId();
        pt->map.insert(std::pair<std::string, int>(str,tmp));
        pt->IncrementIndex();

        pgm2->printdeclare(pt);
        std::cout << "lw $t2, " << pt->map[str] << "($sp)" << '\n';
        std::cout << "or $t1, $t2, $t1" << '\n';
        std::cout << "sw $t1, " << pt->map[str] << "($sp)" << '\n';
      }else if(*str == "&="){
        pgm1->printcode(pt);

        int tmp = pt->GetIndex();
        std::string str = pgm1->getId();
        pt->map.insert(std::pair<std::string, int>(str,tmp));
        pt->IncrementIndex();

        pgm2->printdeclare(pt);
        std::cout << "lw $t2, " << pt->map[str] << "($sp)" << '\n';
        std::cout << "and $t1, $t2, $t1" << '\n';
        std::cout << "sw $t1, " << pt->map[str] << "($sp)" << '\n';
      }else if(*str == "^="){
        pgm1->printcode(pt);

        int tmp = pt->GetIndex();
        std::string str = pgm1->getId();
        pt->map.insert(std::pair<std::string, int>(str,tmp));
        pt->IncrementIndex();

        pgm2->printdeclare(pt);
        std::cout << "lw $t2, " << pt->map[str] << "($sp)" << '\n';
        std::cout << "xor $t1, $t2, $t1" << '\n';
        std::cout << "sw $t1, " << pt->map[str] << "($sp)" << '\n';
      }



      /*pgm1->printcode(pt);

      int tmp = pt->GetIndex();
      std::string str = pgm1->getId();
      pt->map.insert(std::pair<std::string, int>(str,tmp));
      pt->IncrementIndex();

      pgm2->printdeclare(pt);
      std::cout << "sw $t1, " << pt->map[str] << "($sp)" << '\n';*/
    }

    virtual void ReturnPrint(Top *pt) const override{
      std::cout << "#in Assign_Expr" << '\n';
      pgm1->ReturnPrint(pt);
      pgm2->ReturnPrint(pt);
    }

    ~Assign_Expr(){
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
