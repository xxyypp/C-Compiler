#ifndef ast_selection_hpp
#define ast_selection_hpp

#include <string>
#include <iostream>

class IF_Stat_Three_Comp
    : public Program
{
private:

    const Program *pgm1;
    const Program *pgm2;
    const Program *pgm3;

public:
    IF_Stat_Three_Comp(const Program *_pgm1, const Program *_pgm2,const Program *_pgm3)
        : pgm1(_pgm1),pgm2(_pgm2),pgm3(_pgm3)
    {}

    virtual void print() const override
    {
    //  std::cout << "<Function id=\"";
      pgm1->print();
      //std::cout<<"\">\n";
      pgm2->print();
      pgm3->print();
      //std::cout << "</Function>" << '\n';
    }

    ~IF_Stat_Three_Comp(){
      delete pgm1;
      delete pgm2;
      delete pgm3;
    }
};
/*
class Function_Three_Comp_Program
    : public Program
{
private:
    const Program *pgm1;
    const Program *pgm2;
    const Program *pgm3;
    const Program *pgm4;

public:
    Function_Three_Comp_Program(const Program *_pgm1, const Program *_pgm2,const Program *_pgm3)
        : pgm1(_pgm1),pgm2(_pgm2),pgm3(_pgm3)
    {}

    virtual void print() const override
    {
      std::cout << "<Function id=\"";
      pgm1->print();
      std::cout<<"\">\n";
      pgm2->print();
      pgm3->print();
      std::cout << "</Function>" << '\n';
    }

    ~Function_Three_Comp_Program(){
      delete pgm1;
      delete pgm2;
      delete pgm3;

    }
};

class Function_Three_Comp
    : public Program
{
private:

    const std::string str;
    const Program *pgm1;
    const Program *pgm2;

public:
    Function_Three_Comp(const std::string &_str,const Program *_pgm1, const Program *_pgm2)
        :str(_str), pgm1(_pgm1),pgm2(_pgm2)
    {}

    virtual void print() const override
    {
      std::cout << "<Function id=\"";
      pgm1->print();
      std::cout<<"\">\n";
      pgm2->print();
      std::cout << "</Function>" << '\n';
    }

    ~Function_Three_Comp(){
      delete pgm1;
      delete pgm2;
    }
};


class Func_List
    : public Program
{
private:
    const std::string str;
    const Program *pgm1;

public:
    Func_List( const std::string &_str,const Program *_pgm1)
        : str(_str),pgm1(_pgm1)
    {}

    virtual void print() const override
    {
      std::cout << "<Parameter id=\"";
      pgm1->print();
      std::cout << "/\">" << '\n';
    }

    ~Func_List(){
      delete pgm1;
    }
};

class Func_List_Rec
    : public Program
{
private:
    const std::string str;
    const Program *pgm1;
    const Program *pgm2;

public:
    Func_List_Rec(const std::string &_str, const Program *_pgm1, const Program *_pgm2)
        : str(_str),pgm1(_pgm1),pgm2(_pgm2)
    {}

    virtual void print() const override
    {
      std::cout << "<Parameter id=\"";
      pgm1->print();
      std::cout << "/\">" << "\n";
      pgm2->print();
    }

    ~Func_List_Rec(){
      delete pgm1;
      delete pgm2;
    }
};

class Comp_Stat
    : public Program
{
private:
    const Program *pgm1;
public:
    Comp_Stat(const Program *_pgm1)
        : pgm1(_pgm1)
    {}

    virtual void print() const override
    {
      std::cout << "<Scope>" << '\n';
      pgm1->print();
      std::cout << "</Scope>" << '\n';
    }

    ~Comp_Stat(){
      delete pgm1;
    }
};

class Block_Item_List
    : public Program
{
private:
    const Program *pgm1;
public:
    Block_Item_List(const Program *_pgm1)
        : pgm1(_pgm1)
    {}

    virtual void print() const override
    {
      pgm1->print();
    }

    ~Block_Item_List(){
      delete pgm1;
    }
};
class Block_Item_List_Rec
    : public Program
{
private:
    const Program *pgm1;
    const Program *pgm2;
public:
    Block_Item_List_Rec(const Program *_pgm1, const Program *_pgm2)
        : pgm1(_pgm1),pgm2(_pgm2)
    {}

    virtual void print() const override
    {
      pgm1->print();
      pgm2->print();
    }

    ~Block_Item_List_Rec(){
      delete pgm1;
      delete pgm2;
    }
};
*/



#endif
