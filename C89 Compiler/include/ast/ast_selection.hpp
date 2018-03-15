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



#endif
