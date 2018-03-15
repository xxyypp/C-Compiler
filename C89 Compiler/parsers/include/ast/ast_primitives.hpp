#ifndef ast_primitives_hpp
#define ast_primitives_hpp
#include "ast.hpp"
#include <string>
#include <iostream>

class Function
    : public Program
{
private:
    const std::string *type;
    const std::string *id;
    const Program *parameter;
    const Program *scope;

public:
  Function(const std::string *_type, const std::string *_id ,const Program *_parameter, const Program *_scope)
      : type(_type), id(_id), parameter(_parameter),scope(_scope)
  {}

  const std::string getId() const
  { return *id; }

    virtual ~Function()
    {
    //  std::cout << "</Function>";
        delete type;
        delete id;
        delete parameter;
        delete scope;
    }

    virtual void print() const override
    {
      std::cout << "<Function id = \"" << *id <<"\" > \n";
      parameter->print();
      scope->print();
      std::cout << "</Function>" << '\n';
    }
};

class FunctionNoParam
    : public Program
{
private:
    const std::string *type;
    const std::string *id;
    const Program *scope;

public:
  FunctionNoParam(const std::string *_type, const std::string *_id , const Program *_scope)
      : type(_type), id(_id),scope(_scope)
  {}

    virtual ~FunctionNoParam()
    {
    //  std::cout << "</FunctionNoParam>";
        delete type;
        delete id;
        delete scope;
    }

    virtual void print() const override
    {
      std::cout << "<Function id = \"" << *id <<"\" > \n";
      scope->print();
      std::cout << "</Function>" << '\n';
    }
};

class FunctionNoParamNoScope
    : public Program
{
private:
    const std::string *type;
    const std::string *id;

public:
  FunctionNoParamNoScope(const std::string *_type, const std::string *_id)
      : type(_type), id(_id)
  {}

    virtual ~FunctionNoParamNoScope()
    {
    //  std::cout << "</FunctionNoParamNoScope>";
        delete type;
        delete id;
    }

    virtual void print() const override
    {
      std::cout << "<Function id = \"" << *id <<"\" > \n";
      std::cout << "</Function>" << '\n';
    }
};


class NotUsed
    : public Program
{
private:
    //const std::string *id;

public:
  NotUsed( /*const std::string *_id*/)
      //:  id(_id)
  {}

    virtual ~NotUsed()
    {
        //delete id;
    }

    virtual void print() const override
    {
    }
};

class Parameter
    : public Program
{
private:
    std::string id;
public:
    Parameter(const std::string &_id)
        : id(_id)
    {}

    const std::string getId() const
    { return id; }

    virtual void print() const override
    {
        std::cout << "<Parameter id = \""<< id << "/>\n";
    }

    ~Parameter(){
    }
};

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

/*
class Scope
    : public Program
{
private:
    const Program *variable;

public:
  Scope(const Program *_variable)
      : variable(_variable)
  {}

    virtual ~Scope()
    {
        delete variable;
    }

    virtual void print() const override
    {
      std::cout << "<Scope>\n";
      variable->print();
      std::cout << "</Scope>" << '\n';
    }


};*/

class ProgramOther
    : public Program
{
private:
    const Program *pgm;
    const Program *other;
public:
    ProgramOther(const Program *_pgm, const Program *_other)
        : pgm(_pgm), other(_other)
    {}

    virtual void print() const override
    {
      pgm->print();
      other->print();
    }

    ~ProgramOther(){
      delete pgm;
      delete other;
    }
};


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
        std::cout << "<Variable id = \""<< id << "/>\n";
    }

    ~Variable(){
    }
};




#endif
