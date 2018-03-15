#include "ast.hpp"
int main()
{
    Top *pt = new Top();
    const Program *ast=parseAST();

    std::cout << "#start" << '\n';

    ast->printcode(pt);
    std::cout<<std::endl;

    std::cout << "#end" << '\n';

    return 0;
}
