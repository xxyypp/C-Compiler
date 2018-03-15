#include "ast.hpp"

int main()
{
    const Program *ast=parseAST();
    std::cout << "<?xml version=\"1.0\"?>" << '\n';
    std::cout << "<Program>" << '\n';
    ast->print();
    std::cout << "</Program>" << '\n';
    std::cout<<std::endl;

    return 0;
}
