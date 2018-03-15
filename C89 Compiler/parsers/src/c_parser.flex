%option noyywrap

%{
// Avoid error "error: �fileno� was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "c_parser.tab.hpp"
%}


%%

int             {return T_INT;}
void            {return T_VOID;}
long            {return T_LONG;}
short           {return T_SHORT;}
char            {return T_CHAR;}
float           {return T_FLOAT;}
double          {return T_DOUBLE;}
signed          {return T_SIGNED;}
unsigned        {return T_UNSIGNED;}
return          {return T_RETURN;}
if              {return T_IF;}
else            {return T_ELSE;}
while           {return T_WHILE;}
do              {return T_DO;}
for             {return T_FOR;}
goto            {return T_GOTO;}
continue        {return T_CONTINUE;}
break           {return T_BREAK;}


[(]             {return T_LBRACKET;}
[)]             {return T_RBRACKET;}
[{]             {return T_LCURLYBRACKET;}
[}]             {return T_RCURLYBRACKET;}
[[]             {return T_LSQRBRACKET;}
[]]             {return T_RSQRBRACKET;}
[<]             {return T_LESS;}
[>]             {return T_GREATER;}

[=]             {return T_EQUAL;}
[+]             {return T_ADD;}
[-]             {return T_MINUS;}
[*]             {return T_MULT;}
[/]             {return T_DIVID;}
[%]             {return T_MOD;}
[,]             {return T_COMMA;}
[;]             {return T_SEMI;}
[.]             {return T_DOT;}

(\.\.\.)				{ return ELLIPSIS; }
(\>\>\=)				{ return RIGHT_ASSIGN; }
(\<\<\=)				{ return LEFT_ASSIGN; }
(\+\=)					{ return ADD_ASSIGN; }
(\-\=)				  { return SUB_ASSIGN; }
(\*\=)					{ return MUL_ASSIGN; }
(\/\=)					{ return DIV_ASSIGN; }
(\%\=)					{ return MOD_ASSIGN; }
(\&\=)					{ return AND_ASSIGN; }
(\^\=)					{ return XOR_ASSIGN; }
(\|\=)					{ return OR_ASSIGN; }
(\>\>)				  { return RIGHT_OP; }
(\<\<)					{ return LEFT_OP; }
(\+\+)					{ return INC_OP; }
(\-\-)					{ return DEC_OP; }
(\-\>)					{ return PTR_OP; }
(\&\&)					{ return AND_OP; }
(\|\|)					{ return OR_OP; }
(\<\=)					{ return LE_OP; }
(\>\=)					{ return GE_OP; }
(\=\=)					{ return EQ_OP; }
(\!\=)				  { return NE_OP; }
(\:)			      { return T_COLON; }
(\&)					  { return T_AND; }
(\!)				    { return T_EXC;}
(\~)					  { return T_WAVE;}
(\|)					  { return T_OR;}
(\?)					  { return T_QUESTION;}


[-]?[0-9]+([.][0-9]*)? { yylval.number=strtod(yytext, 0); return T_NUMBER;}
[a-zA-Z]([a-zA-Z]|[0-9])*          { yylval.string=new std::string(yytext); return T_ID; }


[ \t\r\n]+		{;}
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
