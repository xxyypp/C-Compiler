#include "ast.hpp"

#include <fstream>
#include <string>
#include <cstdlib>

int main(int argc, char *argv[])
{
    if(argc < 2){
        fprintf(stderr, "usage : compiler sourceCode\n");
        exit(1);
    }

    std::ifstream src(argv[1]);
    if(!src.is_open()){
        fprintf(stderr, "Couldn't open '%s'\n", argv[1]);
        exit(1);
    }

    TreePtr tree=Parse(src);

    Compile(tree);
    std::string str = "mips-linux-gnu-g++ -static output.cpp -o";
    str+=argv[2];
    system(str.c_str());
    return 0;
}
