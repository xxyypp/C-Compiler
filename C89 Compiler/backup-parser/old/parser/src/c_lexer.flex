%option noyywrap

%{
// Avoid error "error: �fileno� was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "c_parser.tab.hpp"
%}

%%
[{]             { return T_CURLYLB; }
[}]             { return T_CURLYRB; }
[(]             { return T_LBRACKET; }
[)]             { return T_RBRACKET; }

(int)           { return T_INT;}
(if)|(for)|(while)            { return T_CTRFLOW;   }
[,]             {return T_COMMA;}

[a-z]+          { yylval.string=new std::string(yytext); return T_VARIABLE; }

[ \t\r\n]+		{;}

.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
