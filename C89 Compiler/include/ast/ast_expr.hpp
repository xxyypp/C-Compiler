#ifndef ast_expr_hpp
#define ast_expr_hpp

#include <string>
#include <iostream>
#include <map>

class Expr
    : public Program
{
private:
    const Program *pgm1;
    const Program *pgm2;
public:
    Expr(const Program *_pgm1,const Program *_pgm2)
        : pgm1(_pgm1),pgm2(_pgm2)
    {}

    virtual void print() const override
    {
      std::cout << "i am in declear" << '\n';
      pgm1->print();
      pgm2->print();
    }

    virtual void printcode(Top *pt) const override{
      pgm1->printcode(pt);
      pgm2->printcode(pt);
    }

    ~Expr(){
      delete pgm1;
      delete pgm2;
    }
};

class Not_Array_Expr
    : public Program
{
private:
    const Program *left;
    const std::string *op;
    const Program *right;


public:
  Not_Array_Expr(const Program *_left, const std::string *_op , const Program *_right)
      : left(_left),op(_op),right(_right)
  {}

    virtual ~Not_Array_Expr()
    {
    //  std::cout << "</FunctionNoParam>";
        delete left;
        delete right;
    }

    virtual void print() const override
    {
      //right->printcode();

      // if(*op == "+"){
      //   //if
      //   std::cout << "addiu	$2,$2,10" << "\n";
      // }

      //std::cout << "addu	$2,$3,$2" << "\n";
    }
};

#endif
