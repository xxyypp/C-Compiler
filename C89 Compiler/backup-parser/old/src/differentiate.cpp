#include "ast.hpp"
#include <iostream>

virtual const Expression *differentiate(
    const std::string &variable
) const
{
  if (getId == variable){
    //std::cout << "1";
    return (new Number(1));
  } else{
    //std::cout << "1";
    return (new Number(0));
  }
}
