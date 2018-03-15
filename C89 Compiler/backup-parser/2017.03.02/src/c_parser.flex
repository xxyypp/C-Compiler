%option noyywrap

%{
// Avoid error "error: �fileno� was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "c_parser.tab.hpp"
%}

%%

int             {return T_INT;}
return          {return T_RETURN;}
[(]             {return T_LBRACKET;}
[)]             {return T_RBRACKET;}
[{]             {return T_LCURLYBRACKET;}
[}]             {return T_RCURLYBRACKET;}
[=]             {return T_EQUAL;}

[-]?[0-9]+([.][0-9]*)? { yylval.number=strtod(yytext, 0); return T_NUMBER; }
[a-zA-Z]+          { yylval.string=new std::string(yytext); return T_VARIABLE; }
[;]             {return T_SEMI;}
[ \t\r\n]+		{;}

.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
