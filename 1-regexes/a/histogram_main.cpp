#include "histogram.hpp"

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <regex>
#include <string>

typedef std::unordered_map<std::string,unsigned> histogram_type;

// Define the instance of the variable that is declared in the header
TokenValue yylval;

int main()
{
    histogram_type histogram;
    double sum=0;
    std::string tmp;
    while(1){
        TokenType type=(TokenType)yylex();

        if(type==None){
            break; // No more tokens

        }else if(type==Number){
            // We have a number. The value will be
            // in yylval.numberValue

            // TODO: add to sum
            sum+=yylval.numberValue;

        }else if(type==Word){
            // We have a string. The value is in a string
            // _pointed to_ by yylval.wordValue. Note that
            // the string is allocated by the lexer, but
            // deallocated by us.
	    std::string str = *yylval.wordValue;
   	    str.erase(std::remove(str.begin(),str.end(),'\"'),str.end());
	    //*yylval.wordValue = str;
 	  

	   
	    
		

            // TODO: add yylval.wordValue to histogram
	    histogram[str]+=1;

            // TODO: Free the pointer yylval.wordValue to stop leaks
	    delete yylval.wordValue;
        }else{
            assert(0); // There are only three token types.
            return 1;
        }
    }


    // TODO: print out `sum` to std::cout with three decimal digits
    std::cout << std::fixed << std::setprecision(3) << sum << std::endl;

    std::vector<std::pair<std::string,double> > sorted(histogram.begin(), histogram.end());

    std::sort(sorted.begin(), sorted.end(), [](const std::pair<std::string,double> &a, const std::pair<std::string,double> &b){
        if(a.second > b.second)
            return true;
        if(a.second < b.second)
            return false;
        return a.first < b.first;
    });

    auto it=sorted.begin();
    while(it!=sorted.end()){
        std::string name=it->first;
        unsigned count=it->second;
        // TODO: Print out `name` and `count` to std::cout
        std::cout << "\"" << name << "\""<< " " << count << std::endl;
	
        
        ++it;
    }

    return 0;
}
