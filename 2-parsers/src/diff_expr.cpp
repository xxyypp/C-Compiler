#include "ast.hpp"

#include <iomanip>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {

	std::string variable; //input;
	const Expression *ast=parseAST();//parse the value
	for (unsigned int i = 1; i < argc; i++) {
		variable = argv[i];
		ast = ast->differentiate(variable);
	}
	ast->print();
	std::cout << std::endl;
	return 0;
}
