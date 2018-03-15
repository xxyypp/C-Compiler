#ifndef ast_notused_hpp
#define ast_notused_hpp
#include "ast.hpp"
#include <string>
#include <iostream>


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

#endif
