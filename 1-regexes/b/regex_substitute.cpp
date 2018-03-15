#include <iostream>
#include <string>
#include <regex>

int main(int argc, char *argv[])
{
	std::string r(argv[1]);
	std::regex reg(r);
    	std::string sub(argv[2]);
	std::string tmp;
	while(std::getline(std::cin, tmp) ){
	 std::cout<<std::regex_replace (tmp,reg,sub, std::regex_constants::format_sed)<<std::endl;
	}
    	return 0;
}
