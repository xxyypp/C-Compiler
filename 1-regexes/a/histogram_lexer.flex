%option noyywrap

%{
/* Now in a section of C that will be embedded
   into the auto-generated code. Flex will not
   try to interpret code surrounded by %{ ... %} */

/* Bring in our declarations for token types and
   the yylval variable. */
#include "histogram.hpp"
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <string>
/* End the embedded code section. */
%}


%%
-?[0-9]+[.][0-9]+|-?[0-9]+              { fprintf(stderr, "Number\n"); 

			/* TODO: get value out of yytext and into yylval.number */;  
			yylval.numberValue = atof(yytext);

			return Number; }

["][^"\n]*["]|[A-Za-z]+          	{ fprintf(stderr, "Word\n"); 

			/* TODO: get value out of yytext and into yylval.wordValue */; 
			std::string textstr(yytext);
			yylval.wordValue = new std::string();
			*yylval.wordValue=textstr;

			 return Word; }

\n             		 { fprintf(stderr, "Newline\n", *yytext); }

 . 
%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}
