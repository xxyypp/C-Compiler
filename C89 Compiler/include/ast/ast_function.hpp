#ifndef ast_function_hpp
#define ast_fcuntion_hpp

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <string>

class Test
    : public Program
{
private:
    const std::string *id;
    const Program *scope;

public:
  Test(const std::string *_id , const Program *_scope)
      : id(_id),scope(_scope)
  {}

    virtual ~Test()
    {
    //  std::cout << "</FunctionNoParam>";
        delete id;
        delete scope;
    }

    virtual void print() const override
    {
      scope->print();
    }
};
class Function_Four_Comp
    : public Program
{
private:

    const std::string *str;//type
    const Program *pgm1;//T_ID
    const Program *pgm2;//Parameter
    const Program *pgm3;//COMP_STAT

public:
    Function_Four_Comp(const std::string *_str,const Program *_pgm1, const Program *_pgm2,const Program *_pgm3)
        : str(_str),pgm1(_pgm1),pgm2(_pgm2),pgm3(_pgm3)
    {}

    virtual void printcode(Top *pt) const override
    {
      pt->IncrementIndex();
      std::cout << ".globl ";
      pgm1->print();
      std::cout<<"\n";
      std::cout << ".ent ";
      pgm1->print();
      std::cout<<"\n";
      std::cout << ".type ";
      pgm1->print();
      std::cout<<", @function\n";
      pgm1->print();
      std::cout<<":"<<std::endl; //print function name
      std::cout << "addiu	$sp,$sp,-500"<<std::endl;
      //std::cout << "sw	$fp,4($sp)" << std::endl;
      //std::cout << "move	$fp,$sp" << std::endl;
      pgm2->printcode(pt);
      pgm3->printcode(pt);
      //std::cout << "</Function>" << '\n';

      std::cout << "ypypreturn:" << '\n';
      std::cout << "addiu	$sp,$sp,500" << std::endl;
      std::cout << "j $31" << std::endl;
      std::cout << "nop" << std::endl;
    }

    ~Function_Four_Comp(){
      delete pgm1;
      delete pgm2;
      delete pgm3;
    }
};

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

    virtual void printcode(Top *pt) const override
    {
      pt->IncrementIndex();
      std::cout << ".globl ";
      pgm1->print();
      std::cout<<"\n";
      std::cout << ".ent ";
      pgm1->print();
      std::cout<<"\n";
      std::cout << ".type ";
      pgm1->print();
      std::cout<<", @function\n";
      pgm1->print();
      std::cout<<":"<<std::endl;
      std::cout << "addiu	$sp,$sp,-500"<<std::endl;
      //std::cout << "sw	$fp,4($sp)" << std::endl;
      //std::cout << "move	$fp,$sp" << std::endl;
      // std::cout << "<Function id=\"";
      // pgm1->print();
      // std::cout<<"\">\n";
       pgm2->printcode(pt);
       pgm3->printcode(pt);
      // std::cout << "</Function>" << '\n';
      std::cout << "ypypreturn:" << '\n';
      std::cout << "addiu	$sp,$sp,500" << std::endl;
      std::cout << "j $31" << std::endl;
      std::cout << "nop" << std::endl;

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

    virtual void printcode(Top *pt) const override
    {
      pt->IncrementIndex();
      std::cout << ".globl ";
      pgm1->print();
      std::cout<<"\n";
      std::cout << ".ent ";
      pgm1->print();
      std::cout<<"\n";
      std::cout << ".type ";
      pgm1->print();
      std::cout<<", @function\n";
      pgm1->print();
      std::cout<<":"<<std::endl;
      std::cout << "addiu	$sp,$sp,-500"<<std::endl;
      //std::cout << "sw	$fp,4($sp)" << std::endl;
      //std::cout << "move	$fp,$sp" << std::endl;
      //std::cout << "#in func" << '\n';
      pgm2->printcode(pt);
      // std::cout << "</Function>" << '\n';

      std::cout << "ypypreturn:" << '\n';
      std::cout << "addiu	$sp,$sp,500" << std::endl;
      std::cout << "j $31" << std::endl;
      std::cout << "nop" << std::endl;

    }

    ~Function_Three_Comp(){
      delete pgm1;
      delete pgm2;
    }
};


class Function
    : public Program
{
private:
    const Program *pgm1;
    const Program *pgm2;

public:
    Function(const Program *_pgm1, const Program *_pgm2)
        : pgm1(_pgm1),pgm2(_pgm2)
    {}

    virtual void printcode(Top *pt) const override
    {
      pt->IncrementIndex();
      std::cout << "#Start Function" << '\n';
      std::cout << "\n";
      std::cout << ".globl ";
      pgm1->print();
      std::cout<<"\n";
      std::cout << ".ent ";
      pgm1->print();
      std::cout<<"\n";
      std::cout << ".type ";
      pgm1->print();
      std::cout<<", @function\n";
      pgm1->print();
      std::cout<<":"<<std::endl;
      std::cout << "#End function" << '\n';

      std::cout << "ypypreturn:" << '\n';
      std::cout << "addiu	$sp,$sp,-500"<<std::endl;
      //std::cout << "sw	$fp,4($sp)" << std::endl;
      //std::cout << "move	$fp,$sp" << std::endl;
      // std::cout << "<Function id=\"";
      // pgm1->print();
      pgm2->printcode(pt);

    }

    ~Function(){
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
    Func_List(const std::string _str,const Program *_pgm1)
        :str(_str),pgm1(_pgm1)
    {}

    virtual void print() const override
    {
       std::cout << "<Parameter id=\"";
       pgm1->print();
       std::cout << "\" />" << '\n';
      //std::cout << "sw	$4,8($fp)" << std::endl;
      //std::cout << "lw	$2,8($fp)" << std::endl;
    }

    virtual void printcode(Top *pt) const override{

        //for(std::map<std::string, int >::iterator it = map.begin();it!=map.end();++it){
          if (pt->paramIter < 8){
            //std::cout << "#in fun_list paramIter is: " << pt->paramIter << '\n';
            int tmp = pt->GetIndex();
            std::string str = pgm1->getId();
            pt->map.insert(std::pair<std::string, int>(str,tmp));
            std::cout << "sw $" << pt->paramIter << ", " << pt->GetIndex() << "($sp)" << '\n';
            pt->IncrementIndex();
            pt->paramIter++;
            //std::cout << "#in fun_list paramIter after ++ is: " << pt->paramIter << '\n';

          }

        //}
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
       std::cout << "\" />" << "\n";
       pgm2->print();
    }

    virtual void printcode(Top *pt) const override{
      if (pt->paramIter < 8){
        //std::cout << "#in fun_list paramIter is: " << pt->paramIter << '\n';
        int tmp = pt->GetIndex();
        std::string str = pgm1->getId();
        pt->map.insert(std::pair<std::string, int>(str,tmp));
        std::cout << "sw $" << pt->paramIter << ", " << pt->GetIndex() << "($sp)" << '\n';
        pt->IncrementIndex();
        pt->paramIter++;
        //std::cout << "#in fun_list paramIter after ++ is: " << pt->paramIter << '\n';

      }
          pgm2->printcode(pt);

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
       //std::cout << "I am in scope" << '\n';
       pgm1->print();
      // std::cout << "</Scope>" << '\n';
    }

    virtual void printcode(Top *pt) const override
    {
    //  std::cout << "comp stat" << '\n';
      pgm1->printcode(pt);
    }

    ~Comp_Stat(){
      delete pgm1;
    }
};


class Block_Item
    : public Program
{
private:
    const Program *pgm1;
public:
    Block_Item(const Program *_pgm1)
        : pgm1(_pgm1)
    {}

    virtual void print() const override
    {
      //std::cout << "# in Block_Item_List" << '\n';
      pgm1->print();
      //std::cout << "/ end" << '\n';
    }

    virtual void printcode(Top *pt) const override
    {
      //std::cout << "#in block item" << '\n';

       pgm1->printcode(pt);
    }

    ~Block_Item(){
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
      //std::cout << "# in Block_Item_List" << '\n';
      pgm1->print();
      //std::cout << "/ end" << '\n';
    }

    virtual void printcode(Top *pt) const override
    {
      //
      //std::cout << "lw $2, %got(" << pt->map[] << ")($28)" << '\n';
       pgm1->printcode(pt);
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
    virtual void printcode(Top *pt) const override
    {
      //std::cout << "lw $2, %got(" << pt-> getId() << ")($28)" << '\n';

       pgm1->printcode(pt);
       pgm2->printcode(pt);
    }


    ~Block_Item_List_Rec(){
      delete pgm1;
      delete pgm2;
    }
};


class Block_Item_Stat
    : public Program
{
private:
    const Program *pgm1;
public:
    Block_Item_Stat(const Program *_pgm1)
        : pgm1(_pgm1)
    {}

    virtual void print() const override
    {
      //std::cout << "# in Block_Item_List" << '\n';
      pgm1->print();
      //std::cout << "/ end" << '\n';
    }

    virtual void printcode(Top *pt) const override
    {
      //std::cout << "#*-*-*-*-" << '\n';
       pgm1->printcode(pt);
       //std::cout << "#*-*-*-*-" << '\n';
    }

    ~Block_Item_Stat(){
      delete pgm1;
    }
};

class Return
    : public Program
{
private:
    const Program *pgm1;
public:
    Return(const Program *_pgm1)
        : pgm1(_pgm1)
    {}

    virtual void print() const override
    {
      std::cout << "in return" << '\n';
      //pgm1->print();
    }

    virtual void printcode(Top *pt) const override{
      pgm1->ReturnPrint(pt);
      //std::cout << "move $2, $t0" << '\n';
      // std::cout << "addiu	$sp,$sp,500" << std::endl;
      // std::cout << "j $31" << std::endl;
      // std::cout << "nop" << std::endl;
    }
    ~Return(){
      delete pgm1;
    }
};

class Return_Null
    : public Program
{
private:

public:
    Return_Null(){}

    virtual void print() const override
    {
      std::cout << "in return" << '\n';
      //pgm1->print();
    }

    virtual void printcode(Top *pt) const override{
       std::cout << "move $2, $0" << '\n';
      // std::cout << "addiu	$sp,$sp,500" << std::endl;
      // std::cout << "j $31" << std::endl;
      // std::cout << "nop" << std::endl;
    }
    ~Return_Null(){
    }
};


#endif
