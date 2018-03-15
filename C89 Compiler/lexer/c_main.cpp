#include "lexer.hpp"

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <regex>
#include <string>
// Define the instance of the variable that is declared in the header
TokenValue yylval;
int LineNo = 1;
int ColNo = 0;
std::string SourceLocation;
int SourceLineNo = 1;
std::string Srcline;

int main(){
    std::string tmp;
    std::cout << "[ "<<std::endl;
    while(1){
        TokenType type=(TokenType)yylex();

        if(type==None){
            break; // No more tokens

        }else if(type==Constant){
            std::string StrC = *yylval.wordValue;
            if((SourceLocation.empty()&&Srcline.empty())){
              std::cout << "{ " << "\"Class\"" << " : " << "\"Constant\"" << " , " << "\"Text\"" << " : " << "\""<< StrC << "\"" << " , " << "\"StreamLine\"" << " : " << LineNo << ", " << "\"SourceCol\"" << " : "  << ColNo-StrC.size()+1 << " }," << std::endl;
            }else{
              std::cout << "{ " << "\"Class\"" << " : " << "\"Constant\"" << " , " << "\"Text\"" << " : " << "\""<< StrC << "\"" << " , " << "\"StreamLine\"" << " : " << LineNo << ", " << "\"SourceCol\"" << " : "  << ColNo-StrC.size()+1 << ", " << "\"SourceFile\" : " << SourceLocation << ", " << "\"SourceLine\" : " << SourceLineNo <<" }," << std::endl;
            }
            delete yylval.wordValue;
        }else if (type==Keyword){
                std::string StrK = *yylval.wordValue;
            if((SourceLocation.empty()&&Srcline.empty())){
              std::cout << "{ " << "\"Class\"" << " : " << "\"Keyword\"" << " , " << "\"Text\"" << " : " << "\""<< StrK << "\"" << " , " << "\"StreamLine\"" << " : " << LineNo << ", " << "\"SourceCol\"" << " : "  << ColNo-StrK.size()+1 << " }," << std::endl;
            }else{
              std::cout << "{ " << "\"Class\"" << " : " << "\"Keyword\"" << " , " << "\"Text\"" << " : " << "\""<< StrK << "\"" << " , " << "\"StreamLine\"" << " : " << LineNo << ", " << "\"SourceCol\"" << " : "  << ColNo-StrK.size()+1 << ", " << "\"SourceFile\" : " << SourceLocation << ", " << "\"SourceLine\" : " << SourceLineNo <<" }," << std::endl;
            }
          delete yylval.wordValue;
        }else if (type == Operator){
            std::string StrO = *yylval.wordValue;
          if((SourceLocation.empty()&&Srcline.empty())){
            std::cout << "{ " << "\"Class\"" << " : " << "\"Operator\"" << " , " << "\"Text\"" << " : " << "\""<< StrO << "\"" << " , " << "\"StreamLine\"" << " : " << LineNo << ", " << "\"SourceCol\"" << " : "  << ColNo-StrO.size()+1 << " }," << std::endl;
          }else{
              std::cout << "{ " << "\"Class\"" << " : " << "\"Operator\"" << " , " << "\"Text\"" << " : " << "\""<< StrO << "\"" << " , " << "\"StreamLine\"" << " : " << LineNo << ", " << "\"SourceCol\"" << " : "  << ColNo-StrO.size()+1 << ", " << "\"SourceFile\" : " << SourceLocation << ", " << "\"SourceLine\" : " << SourceLineNo << " }," << std::endl;
          }
          delete yylval.wordValue;
        }else if(type == StringLiteral){
            std::string StrS = *yylval.wordValue;
            StrS.erase(std::remove(StrS.begin(),StrS.end(),'\"'),StrS.end());
          if((SourceLocation.empty()&&Srcline.empty())){
            std::cout << "{ " << "\"Class\"" << " : " << "\"StringLiteral\"" << " , " << "\"Text\"" << " : " << "\""<< StrS << "\"" << " , " << "\"StreamLine\"" << " : " << LineNo << ", " << "\"SourceCol\"" << " : "  << ColNo-StrS.size()+1 << " }," << std::endl;
          }else{
            std::cout << "{ " << "\"Class\"" << " : " << "\"StringLiteral\"" << " , " << "\"Text\"" << " : " << "\""<< StrS << "\"" << " , " << "\"StreamLine\"" << " : " << LineNo << ", " << "\"SourceCol\"" << " : "  << ColNo-StrS.size()+1 << ", " << "\"SourceFile\" : " << SourceLocation << ", " << "\"SourceLine\" : " << SourceLineNo << " }," << std::endl;
          }
          delete yylval.wordValue;
        }else if(type == Identifier){
          std::string StrI = *yylval.wordValue;
   	      //StrI.erase(std::remove(StrI.begin(),StrI.end(),'\"'),StrI.end());
          if((SourceLocation.empty()&&Srcline.empty())){
            std::cout << "{ " << "\"Class\"" << " : " << "\"Identifier\"" << " , " << "\"Text\"" << " : " << "\""<< StrI << "\"" << " , " << "\"StreamLine\"" << " : " << LineNo << ", " << "\"SourceCol\"" << " : "  << ColNo-StrI.size()+1 << " }," << std::endl;
          }else{
            std::cout << "{ " << "\"Class\"" << " : " << "\"Identifier\"" << " , " << "\"Text\"" << " : " << "\""<< StrI << "\"" << " , " << "\"StreamLine\"" << " : " << LineNo << ", " << "\"SourceCol\"" << " : "  << ColNo-StrI.size()+1 << ", " << "\"SourceFile\" : " << SourceLocation << ", " << "\"SourceLine\" : " << SourceLineNo  << " }," << std::endl;
          }
          delete yylval.wordValue;
        }else if(type == Invalid){
                std::string StrIN = *yylval.wordValue;
   	      //StrIN.erase(std::remove(StrIN.begin(),StrIN.end(),'\"'),StrIN.end());
          if((SourceLocation.empty()&&Srcline.empty())){
            std::cout << "{ " << "\"Class\"" << " : " << "\"Invalid\"" << " , " << "\"Text\"" << " : " << "\""<< StrIN << "\"" << " , " << "\"StreamLine\"" << " : " << LineNo << ", " << "\"SourceCol\"" << " : "  << ColNo-StrIN.size()+1 << " }," << std::endl;
          }else{
            std::cout << "{ " << "\"Class\"" << " : " << "\"Invalid\"" << " , " << "\"Text\"" << " : " << "\""<< StrIN << "\"" << " , " << "\"StreamLine\"" << " : " << LineNo << ", " << "\"SourceCol\"" << " : "  << ColNo-StrIN.size()+1 << ", " << "\"SourceFile\" : " << SourceLocation << ", " << "\"SourceLine\" : " << SourceLineNo << " }," << std::endl;
          }
          delete yylval.wordValue;
        }else if(type == Preprocess){
          std::string StrP= *yylval.wordValue;
   	      //StrP.erase(std::remove(StrP.begin(),StrP.end(),'\"'),StrP.end());
					size_t startOfFileName = StrP.find_first_of('"');
					size_t endOfFileName = StrP.find_last_of('"');
					size_t fileNameSize = endOfFileName - startOfFileName;
					SourceLocation = strdup(StrP.substr(startOfFileName,fileNameSize+1).c_str());

          size_t startOfLineName = StrP.find_first_of('#');
					size_t endOfLineName = StrP.find_first_of('"');
					size_t fileLineSize = endOfLineName - startOfLineName;
          Srcline = strdup(StrP.substr(startOfLineName+2,fileLineSize-3).c_str());
          //SourceLineNo = atoi(StrP[2])-1;
          SourceLineNo = stoi(Srcline);
      //  std::cout << Srcline << std::endl;

          //std::cout << "{ " << "\"Class\"" << " : " << "\"Preprocess\"" << " , " << "\"Text\"" << " : " << "\""<< StrP << "\"" << " , " << "\"StreamLine\"" << " : " << LineNo << ", " << "\"SourceCol\"" << " : "  << ColNo-StrP.size()+1 << " }," << std::endl;
          //std::cout << "sourcefile and location: " << SourceLocation << " " << SourceLineNo << std::endl;
          delete yylval.wordValue;
        }
        else{
            //assert(0); // There are only three token types.
            //return 1;
            std::cout << "{ \"Text\" : \"Invalid\" }" << std::endl;
        }
    }
    std::cout << "{}"<<std::endl;
    std::cout << "] "<<std::endl;
    return 0;
}
