
%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const Program *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Program *expr;
  double number;
  std::string *string;
}

%token T_NUMBER T_VARIABLE T_INT T_LBRACKET T_RBRACKET T_SEMI T_LCURLYBRACKET T_RCURLYBRACKET T_EQUAL T_RETURN

%type <expr> PROGRAM VARIABLE PARAMETER SCOPE FUNCTION
%type <number> T_NUMBER
%type <string> T_VARIABLE T_INT T_RETURN

%start ROOT

%%

ROOT : PROGRAM { g_root = $1; }

PROGRAM : |FUNCTION                   { $$ = $1; }
          |VARIABLE                 	{ $$ = $1; }
          |PROGRAM VARIABLE          { $$ = new ProgramOther($1,$2); }
          |PROGRAM FUNCTION           { $$ = new ProgramOther($1,$2);}

FUNCTION : T_INT T_VARIABLE PARAMETER T_LCURLYBRACKET SCOPE T_RCURLYBRACKET { $$ = new Function($1,$2,$3,$5);}
          |T_INT T_VARIABLE T_LBRACKET T_RBRACKET T_LCURLYBRACKET SCOPE T_RCURLYBRACKET                   { $$ = new FunctionNoParam($1,$2,$6);}
          |T_INT T_VARIABLE T_LBRACKET T_RBRACKET T_LCURLYBRACKET T_RCURLYBRACKET                   { $$ = new FunctionNoParamNoScope($1,$2);}
          |T_RETURN T_VARIABLE T_SEMI              {$$ = new NotUsed($1);}        

PARAMETER : VARIABLE                  { $$ = $1; }
          |T_LBRACKET T_INT T_VARIABLE T_RBRACKET { $$ = new Parameter(*$3); }

SCOPE : VARIABLE                           { $$ = new Scope($1);}
        |FUNCTION                          { $$ = $1;}

VARIABLE : T_INT T_VARIABLE T_SEMI         { $$ = new Variable( *$2 );}
          |T_INT T_VARIABLE T_EQUAL T_VARIABLE T_SEMI {$$ = new Variable(*$2);}







%%

const Program *g_root; // Definition of variable (to match declaration earlier)

const Program *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
