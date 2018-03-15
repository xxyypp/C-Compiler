%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const Expression *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Expression *expr;
  double number;
  std::string *string;
}

%token T_TIMES T_PLUS T_DIVIDE T_MINUS T_LBRACKET T_RBRACKET T_LOG T_EXP T_SQRT T_NUMBER T_VARIABLE

%type <expr> EXPR TERM FACTOR
%type <number> T_NUMBER
%type <string> T_VARIABLE T_LOG T_EXP T_SQRT FUNCTION_NAME

%start ROOT

%%

ROOT : EXPR { g_root = $1; }

EXPR : TERM                 		{ $$ = $1; }
	|EXPR T_PLUS TERM 		{ $$ = new AddOperator($1, $3);}
	|EXPR T_MINUS TERM		{ $$ = new SubOperator($1, $3);}

TERM : FACTOR               		{ $$ = $1; }
	|TERM T_DIVIDE FACTOR 		{ $$ = new DivOperator($1,$3);}
	|TERM T_TIMES FACTOR 		{ $$ = new MulOperator($1,$3);}

FACTOR : T_NUMBER           		{ $$ = new Number( $1 ); }
       | T_LBRACKET EXPR T_RBRACKET 	{ $$ = $2; }
       | T_VARIABLE 	   		{ $$ = new Variable(*$1); }
       | FUNCTION_NAME T_LBRACKET EXPR T_RBRACKET {if (*$1 == "log")
						{$$ = new LogFunction($3);}

						else if (*$1 == "exp")
						{$$ = new ExpFunction($3);}

						else if (*$1 == "sqrt")
						{$$ = new SqrtFunction($3);}}

FUNCTION_NAME : T_LOG 			{ $$ = new std::string("log"); }
		|T_EXP 			{ $$ = new std::string("exp"); }
		|T_SQRT 			{ $$ = new std::string("sqrt"); }

%%

const Expression *g_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
