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
    const Program *pgm1; //stat
    const Program *pgm2; //comp_stat
public:
    If_Stat(const Program *_pgm1, const Program *_pgm2)
        : pgm1(_pgm1), pgm2(_pgm2)
    {}

    virtual void print() const override
    {
      std::cout << "<Scope> \n";
      pgm1->print();
      std::cout << "</Scope> \n";
    }

    virtual void printcode(Top *pt) const override{
      std::string lbl = "lbl";
      std::cout  << '\n';
      std::string lbl0 = pt->makeName(lbl);
      std::string lbl1 = pt->makeName(lbl);
      pgm1->printdeclare(pt);
      std::cout << "addiu $t2, $0, 1" << '\n'; //$t2 = $t1
      std::cout << "bne $t1, $t2, " << lbl1 << '\n';
      std::cout << "nop" << '\n';

      std::cout << "b " << lbl0 << '\n';
      std::cout << "nop" << '\n';
      std::cout << lbl0 <<  ":" << '\n';

      pgm2->printcode(pt);//return second
      std::cout << "b " << "ypypreturn" << '\n';
      std::cout << "#--------------------------" << '\n';
      std::cout << lbl1 <<  ":" << '\n';



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
    const Program *pgm3;
public:
    Else_Stat(const Program *_pgm1, const Program *_pgm2, const Program *_pgm3)
        : pgm1(_pgm1),pgm2(_pgm2), pgm3(_pgm3)
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

    virtual void printcode(Top *pt) const override{
      std::string lbl = "lbl";
      std::cout  << '\n';
      std::string lbl0 = pt->makeName(lbl);
      std::string lbl1 = pt->makeName(lbl);
      pgm1->printdeclare(pt);
      std::cout << "addiu $t2, $0, 1" << '\n'; //$t2 = $t1
      std::cout << "bne $t1, $t2, " << lbl1 << '\n';
      std::cout << "nop" << '\n';

      pgm2->printcode(pt);
      std::cout << "b " << lbl0 << '\n';
      std::cout << "nop" << '\n';
      std::cout << lbl1 <<  ":" << '\n';
      pgm3->printcode(pt);//return second
      std::cout << "b " << "ypypreturn" << '\n';
      std::cout << lbl0 <<  ":" << '\n';

    }


    ~Else_Stat(){
      delete pgm1;
      delete pgm2;
      delete pgm3;
    }
};

class While_Stat
    : public Program
{
private:
    const Program *pgm1;
    const Program *pgm2;
public:
    While_Stat(const Program *_pgm1,const Program *_pgm2)
        : pgm1(_pgm1),pgm2(_pgm2)
    {}

    virtual void print() const override
    {
      std::cout<< "<Scope> \n";
      pgm1->print();
      std::cout << "</Scope> \n";
    }

    virtual void printcode(Top *pt) const override{
      std::string lbl = "lbl";
      std::cout  << '\n';
      std::string lbl1 = pt->makeName(lbl);
      std::string lbl2 = pt->makeName(lbl);
      std::string lbl3 = pt->makeName(lbl);

      std::cout << lbl1 << ":" << '\n';
      pgm1->printdeclare(pt);
      std::cout << "addiu $t2, $0, 1" << '\n'; //$t2 = $t1
      std::cout << "bne $t1, $t2, " << lbl3 << '\n';
      std::cout << "nop" << '\n';

      std::cout << lbl2 <<  ":" << '\n';
      pgm2->printcode(pt);
      std::cout << "b " << lbl1 << '\n';

      std::cout << lbl3 << ":" << '\n';
    }

    ~While_Stat(){
      delete pgm1;
      delete pgm2;
    }
};

class DoWhile_Stat
    : public Program
{
private:
    const Program *pgm1;
    const Program *pgm2;
public:
    DoWhile_Stat(const Program *_pgm1,const Program *_pgm2)
        : pgm1(_pgm1),pgm2(_pgm2)
    {}

    virtual void print() const override
    {
      std::cout<< "<Scope> \n";
      pgm1->print();
      std::cout << "</Scope> \n";
    }

    virtual void printcode(Top *pt) const override{
      std::string lbl = "lbl" ;
      std::string str = pt->makeName(lbl);

      std::cout << str << ":" << '\n';
      pgm1 -> printcode(pt);
      pgm2 -> printdeclare(pt);
      std::cout << "addiu $t2,$zero,1" << '\n';
      std::cout << "beq $t1,$t2, " << str << '\n';
      std::cout << "nop" << '\n';
    }

    ~DoWhile_Stat(){
      delete pgm1;
      delete pgm2;
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
      // std::cout<< "<Parameter id = \"";
      // pgm1->print();
      // pgm2->print();
      // pgm3->print();
      // std::cout << "\"/>" << "\n";
      // std::cout<< "<Scope> \n";
      // pgm4->print();
      // std::cout << "</Scope> \n";
    }
    virtual void printcode(Top *pt) const override{
      std::string lbl = "lbl";
      std::cout  << '\n';
      std::string lbl1 = pt->makeName(lbl);
      std::string lbl2 = pt->makeName(lbl);
      std::string lbl3 = pt->makeName(lbl);

      std::cout << lbl1 << ":" << '\n';
      pgm1->printdeclare(pt);//print condition
      pgm2->printdeclare(pt);//print condition
      pgm3->printdeclare(pt);//print condition
      std::cout << "addiu $t2, $0, 1" << '\n'; //$t2 = $t1
      std::cout << "bne $t1, $t2, " << lbl3 << '\n';
      std::cout << "nop" << '\n';

      std::cout << lbl2 <<  ":" << '\n';
      pgm2->printcode(pt);//printcode
      std::cout << "b " << lbl1 << '\n';

      std::cout << lbl3 << ":" << '\n';
    }

    ~For_Stat_Four(){
      delete pgm1;
      delete pgm2;
      delete pgm3;
      delete pgm4;
    }
};


#endif
