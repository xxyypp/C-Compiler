#ifndef ast_program_hpp
#define ast_program_hpp

#include <string>
#include <iostream>
#include <map>

class Program
{
public:

    //virtual void print() const =0;
    virtual void print() const {
    }

    Program()
    {
      //std::cout << "<?xml version=\"1.0\"?>" << '\n';
      //std::cout << "<Program>\n";
    }
    virtual ~Program()
    {
      //std::cout << "</Program>";
    }

    //! Evaluate the tree using the given mapping of variables to numbers
};


#endif
