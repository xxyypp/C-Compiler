#include "ast.hpp"

#include <iomanip>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
    std::map<std::string,double> bindings;

    // TODO : for each pair of arguments:
    //  - read the variable name
    for(unsigned int i = 1; i < argc; i=i+2){
      std::string str(argv[i]);
      double num(atof(argv[i+1]));
      bindings.insert(std::pair<std::string,double>(str,num));
    }
    //  - parse the value
    const Expression *ast=parseAST();
    //  - insert into the bindings map
    double res=ast->evaluate(bindings);

    // TODO : print out with 6 decimal digits of precision

    std::cout << std::fixed << std::setprecision(6)<< res << std::endl;
    return 0;
}
