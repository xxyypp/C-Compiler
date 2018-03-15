%option noyywrap
%option yylineno

%{
#include "lexer.hpp"
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <string>
void countcol();

%}
TKeyword (auto)|(break)|(case)|(char)|(const)|(continue)|(default)|(do)|(double)|(else)|(enum)|(extern)|(float)|(for)|(goto)|(if)|(int)|(long)|(register)|(return)|(short)|(signed)|(sizeof)|(static)|(struct)|(switch)|(typedef)|(union)|(unsignedv)|(void)|(volatile)|(while)

TConst1 0[xX][a-fA-F0-9]+((u|U|l|L)*)?
TConst2 0[0-9]+((u|U|l|L)*)?
TConst3 [\.]?[0-9]+((u|U|l|L)*)?
TConst4 [a-zA-Z_]?'(\\.|[^\\'])+'
TConst5 [0-9]+[Ee][+-]?[0-9]+(f|F|l|L)?
TConst6 [0-9]+[\.][0-9]*([Ee][+-]?[0-9]+)?(f|F|l|L)?
TConst7 [0-9]*[\.][0-9]+([Ee][+-]?[0-9]+)?(f|F|l|L)?
Operator (\.\.\.)|(\>\>\=)|(\<\<\=)|(\+\=)|(\-\=)|(\*\=)|(\/\=)|(\%\=)|(\&\=)|(\^\=)|(\|\=)|(\>\>)|(\<\<)|(\+\+)|(\-\-)|(\-\>)|(\&\&)|(\|\|)|(\<\=)|(\>\=)|(\=\=)|(\!\=)|(\;)|(\{)|(\})|(\,)|(\:)|(\=)|(\()|(\))|(\[)|(\])|(\.)|(\&)|(\!)|(\~)|(\-)|(\+)|(\*)|(\/)|(\%)|(\<)|(\>)|(\^)|(\|)|(\?)
TStringLiteral [a-zA-Z_]?\"(\\.|[^\\"])*\"
TIdentifier [\_]?[a-zA-Z_]+[a-zA-Z0-9]*
Preprocess #[ ][0-9]+[ ]\"(.)*\"([ ][1-4]){0,4}$
%%

{TKeyword} 	{LineNo = yylineno;
		std::string textstr(yytext);
		yylval.wordValue = new std::string();
		*yylval.wordValue=textstr;
		countcol();
		return Keyword;}
{TIdentifier}   {LineNo = yylineno;
		std::string textstr(yytext);
		yylval.wordValue = new std::string();
		*yylval.wordValue=textstr;
		countcol();
		return Identifier;}
{Operator}	{LineNo = yylineno;
		std::string textstr(yytext);
		yylval.wordValue = new std::string();
		*yylval.wordValue=textstr;
		countcol();
		return Operator;}
{TConst1}|{TConst2}|{TConst3}|{TConst4}|{TConst5}|{TConst6}|{TConst7}           { 	LineNo = yylineno;
			std::string textstr(yytext);
			yylval.wordValue = new std::string();
			*yylval.wordValue=textstr;
			countcol();
			return Constant;
                    }
{TStringLiteral} {LineNo = yylineno;
		std::string textstr(yytext);
		yylval.wordValue = new std::string();
		*yylval.wordValue=textstr;
		countcol();
		return StringLiteral;}

[\n]		{LineNo+=1;ColNo = 0;}
[ \t\v\n\f] {}
{Preprocess} 	{LineNo = yylineno;
		std::string textstr(yytext);
		yylval.wordValue = new std::string();
		*yylval.wordValue=textstr;
		countcol();
		return Preprocess;}

 . 		{LineNo = yylineno;
		std::string textstr(yytext);
		yylval.wordValue = new std::string();
		*yylval.wordValue=textstr;
		countcol();
		return Invalid;}
%%
/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}


void countcol(){
	int i;
	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n'){
			ColNo = 0;
		}else if (yytext[i] == '\t'){
			ColNo += 8 - (ColNo % 8);
		}else{
			ColNo++;
		}

}
