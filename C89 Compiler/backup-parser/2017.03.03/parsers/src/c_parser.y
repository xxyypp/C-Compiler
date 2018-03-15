
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

%token T_NUMBER T_ID T_INT T_LBRACKET T_RBRACKET T_SEMI T_LCURLYBRACKET T_RCURLYBRACKET T_EQUAL T_RETURN
%token T_FLOAT T_CHAR T_DOUBLE T_VOID
%token FUNCTION PARAMETER

%type <expr> PROGRAM DECLARATION
%type <number> T_NUMBER
%type <string> T_ID TYPE

%start ROOT

%%

ROOT : PROGRAM { g_root = $1; }

PROGRAM : DECLARATION         {$$ = $1;}
        | PROGRAM DECLARATION {$$ = new ProgramOther($1,$2);}

TYPE : T_INT                {$$ = new std::string("int");}
      //|FLOAT                {$$ = new std::string("float");}
      //|CHAR                 {$$ = new std::string("char");}
      //|DOUBLE               {$$ = new std::string("double");}
      //|VOID                 {$$ = new std::string("void");}

//FUNCTION: TYPE T_ID T_LBRACKET ARG_LIST_OPTION T_RBRACKET COMPOUND_STAT

DECLARATION: TYPE T_ID T_SEMI { $$ = new Variable(*$2);}
          //  | ASSIGNMENT T_SEMI
          //  | FUNCTIONCALL T_SEMI
            //| ARRAYUSE T_SEMI
          //  | TYPE ARRAYUSE T_SEMI
            //| STRUCTSTMT;
            ;

//ASSIGNMENT: T_ID T_EQUAL ASSIGNMENT
        //  | T_ID T_EQUAL FUNCTIONCALL
        //  | T_ID T_EQUAL ARRAYUSE
          //| ARRAYUSE T_EQUAL ASSIGNMENT
          //| ID T_COMMA ASSIGNMENT
          //| T_NUMBER T_COMMA ASSIGNMENT
          //| T_ID PLUS ASSIGNMENT
        //  | T_ID MINUS ASSIGNMENT
        //  | T_ID MULT ASSIGNMENT
          //| T_ID DIV ASSIGNMENT
          //| T_NUMBER PLUS ASSIGNMENT
          //| T_NUMBER MINUS ASSIGNMENT
          //| T_NUMBER MULT ASSIGNMENT
          //| T_NUMBER DIV ASSIGNMENT
          //| T_NUMBER          {$$ = $1;}
          //| T_ID              {$$ = $1;}
          //;
/*
COMPOUND_STAT: T_LCURLYBRACKET STATMENT_LIST T_RCURLYBRACKET ;

ARG_LIST_OPTION: ARG_LIST
                |
                ;

ARG_LIST: ARG_LIST T_COMMA ARG
        | ARG;

ARG: TYPE T_ID;*/




%%

const Program *g_root; // Definition of variable (to match declaration earlier)

const Program *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
