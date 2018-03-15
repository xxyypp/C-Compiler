
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
%token T_FLOAT T_CHAR T_DOUBLE T_VOID T_STARPTR T_ADD T_MINUS T_MULT T_DIVID T_MOD T_COMMA
%token  T_LSQRBRACKET T_RSQRBRACKET T_IF T_ELSE ELLIPSIS RIGHT_ASSIGN LEFT_ASSIGN T_WHILE
%token  ADD_ASSIGN  SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN AND_ASSIGN XOR_ASSIGN RIGHT_OP
%token OR_ASSIGN LEFT_OP INC_OP DEC_OP PTR_OP AND_OP OR_OP LE_OP GE_OP EQ_OP NE_OP T_COLON
%token T_AND  T_EXC T_WAVE T_XOR T_OR T_QUESTION T_DO T_FOR T_GOTO T_CONTINUE T_BREAK
%token T_LESS T_GREATER T_DOT T_SHORT T_LONG T_SIGNED T_UNSIGNED

%nonassoc "next"
%nonassoc T_ELSE

%type <expr> PROGRAM FULL_DECLEAR DECLEAR DECLARATOR INIT_DECLARATOR INIT_DECLARATOR_LIST DIRECT_DECLARATOR
%type <expr> ASSIGN_EXPR EXPR PRIMARY_EXPR NOTARRAY_EXPR INITIALIZER BLOCK_ITEM BLOCK_ITEM_LIST COMP_STAT
%type <expr> FUNC_LIST FUNCTION  STATEMENT IF_STATEMENT EXPR_STATEMENT /* COND_EXPR MULT_EXPR ADD_EXPR SHIFT_EXPR RELATIONAL_EXPR EQUA_EXPR*/
%type <expr> JUMP_STATEMENT ITERATION_STATEMENT POSTFIX_EXPR RE_DECLEAR
%type <number> T_NUMBER
%type <string> TYPE_SPECIFIER DECLEAR_SPECIFIERS T_INT T_ID T_ADD T_MINUS T_MULT T_DIVID T_MOD OPERATOR T_IF
%type <string> ASSIGN_OP
%start ROOT

%%
ROOT : PROGRAM { g_root = $1; }

PROGRAM: FULL_DECLEAR { $$ = $1;}
       | PROGRAM FULL_DECLEAR { $$ = new ProgramOther($1,$2);}
       | RE_DECLEAR {$$ = $1;}

FULL_DECLEAR : DECLEAR { $$ = $1;}
             | FUNCTION {$$ = $1;}

FUNCTION : DECLEAR_SPECIFIERS DECLARATOR T_LBRACKET FUNC_LIST T_RBRACKET COMP_STAT {$$ = new Function_Four_Comp($1, $2, $4, $6);}
         | DECLEAR_SPECIFIERS DECLARATOR T_LBRACKET T_RBRACKET COMP_STAT {$$ = new Function_Three_Comp(*$1,$2,$5);}
         | DECLARATOR T_LBRACKET FUNC_LIST T_RBRACKET COMP_STAT {$$ = new Function_Three_Comp_Program($1,$3,$5);}
         | DECLARATOR T_LBRACKET T_RBRACKET COMP_STAT {$$ = new Function($1,$4);}

FUNC_LIST :  DECLEAR_SPECIFIERS DECLARATOR {$$ = new Func_List(*$1,$2);}
          |  DECLEAR_SPECIFIERS DECLARATOR T_COMMA FUNC_LIST {$$ = new Func_List_Rec(*$1,$2,$4);}


COMP_STAT : T_LCURLYBRACKET BLOCK_ITEM_LIST T_RCURLYBRACKET {$$ = new Comp_Stat($2);}
          | T_LCURLYBRACKET T_RCURLYBRACKET  { $$ = new NotUsed();}

BLOCK_ITEM_LIST : BLOCK_ITEM {$$ = new Block_Item_List($1);}
                | BLOCK_ITEM_LIST BLOCK_ITEM {$$ = new Block_Item_List_Rec($1,$2);}

BLOCK_ITEM : DECLEAR                {$$ = $1;}
           | STATEMENT  {$$=$1;}
        //start again

RE_DECLEAR : DECLARATOR T_SEMI {$$ =new NotUsed();}

STATEMENT : IF_STATEMENT {$$ = $1;}
          | ITERATION_STATEMENT {$$ = $1;}
          | JUMP_STATEMENT {$$ = $1;}
          | COMP_STAT {$$ = $1;}

EXPR_STATEMENT : T_SEMI {$$ = new NotUsed(); }
               | EXPR T_SEMI {$$ = new NotUsed(); }

ITERATION_STATEMENT : T_WHILE T_LBRACKET EXPR T_RBRACKET  STATEMENT  {$$ = new While_Stat($5);}
                    | T_DO  STATEMENT  T_WHILE T_LBRACKET EXPR T_RBRACKET {$$ = new While_Stat($2);}
                    | T_FOR T_LBRACKET EXPR_STATEMENT EXPR_STATEMENT T_RBRACKET  STATEMENT  {$$ = new For_Stat($3,$4,$6);}
                    | T_FOR T_LBRACKET EXPR_STATEMENT EXPR_STATEMENT EXPR T_RBRACKET  STATEMENT  {$$ = new For_Stat_Four($3,$4,$5,$7);}
          //in c99          //| T_FOR T_LBRACKET DECLEAR EXPR_STATEMENT EXPR T_RBRACKET  STATEMENT  {$$ = new For_Stat_Four($3,$4,$5,$7);}

JUMP_STATEMENT : T_GOTO T_ID T_SEMI {$$ = new NotUsed(); }
               | T_CONTINUE T_SEMI {$$ = new NotUsed(); }
               | T_BREAK T_SEMI {$$ = new NotUsed(); }
               | T_RETURN T_SEMI {$$ = new NotUsed(); }
               | T_RETURN EXPR T_SEMI {$$ = new NotUsed(); }


IF_STATEMENT : T_IF T_LBRACKET EXPR T_RBRACKET  STATEMENT  T_ELSE  STATEMENT  {$$ = new Else_Stat($5,$7);}
             | T_IF T_LBRACKET EXPR T_RBRACKET  STATEMENT  {$$ = new If_Stat($5);} %prec "next"

DECLEAR : DECLEAR_SPECIFIERS T_SEMI { $$ = new NotUsed();}
        | DECLEAR_SPECIFIERS INIT_DECLARATOR_LIST T_SEMI { $$ = new Declear($2);}

DECLEAR_SPECIFIERS : TYPE_SPECIFIER { $$ = $1;}
                      // | TYPE_SPECIFIER DECLARATION_SPECIFIERS { $$ = new declaration_specifiers(*$1,*$2);}

INIT_DECLARATOR_LIST : INIT_DECLARATOR { $$ = $1;}
                     //| INIT_DECLARATOR T_COMMA INIT_DECLARATOR_LIST

INIT_DECLARATOR : DECLARATOR { $$ = $1;}
                | DECLARATOR T_EQUAL INITIALIZER {$$ = new InitDeclar($1,$3);}

INITIALIZER : ASSIGN_EXPR      {$$ = $1;}

ASSIGN_EXPR : NOTARRAY_EXPR       {$$ = $1;}
/*ASSIGN_EXPR : NOTARRAY_EXPR ASSIGN_OP PRIMARY_EXPR {$$ = new Declare_Declare($1,$3);}*/

NOTARRAY_EXPR : POSTFIX_EXPR {$$=$1;}
              | INC_OP NOTARRAY_EXPR  {$$=$2;}
              | DEC_OP NOTARRAY_EXPR  {$$=$2;}
              | PRIMARY_EXPR OPERATOR NOTARRAY_EXPR {$$=$3;}

POSTFIX_EXPR : PRIMARY_EXPR  {$$=$1;}
             | POSTFIX_EXPR T_LSQRBRACKET EXPR T_RSQRBRACKET {$$=$1;}
             | POSTFIX_EXPR T_LBRACKET T_RBRACKET {$$=$1;}
             | POSTFIX_EXPR INC_OP  {$$= $1;}
             | POSTFIX_EXPR DEC_OP {$$=$1;}
             | POSTFIX_EXPR PTR_OP T_ID {$$=$1;}
             | POSTFIX_EXPR T_DOT T_ID {$$ = $1;}


PRIMARY_EXPR : T_NUMBER         {$$ = new Number($1);}
             | T_ID              {$$ = new Variable(*$1);}
            // | T_LBRACKET EXPR T_RBRACKET   {$$=$2;}

EXPR : INITIALIZER  {$$=$1;}
     | T_LBRACKET ASSIGN_EXPR T_RBRACKET {$$=$2;}
     | PRIMARY_EXPR ASSIGN_OP INITIALIZER {$$ = $3;}

OPERATOR : T_AND      {$$ = new std::string("&");}
         | T_MINUS    {$$ = new std::string("+");}
         | T_MULT     {$$ = new std::string("-");}
         | T_DIVID    {$$ = new std::string("*");}
         | T_EXC      {$$ = new std::string("/");}
         | T_EQUAL    {$$ = new std::string("=");}
         | T_MOD      {$$ = new std::string("%%");}
         | T_GREATER  {$$ = new std::string(">");}
         | T_LESS     {$$ = new std::string("<");}

ASSIGN_OP : NE_OP               {$$ = new std::string("!=");}
          | EQ_OP               {$$ = new std::string("==");}
          | GE_OP               {$$ = new std::string(">=");}
          | LE_OP               {$$ = new std::string("<=");}
          | OR_OP               {$$ = new std::string("||");}
          | AND_OP              {$$ = new std::string("&&");}
          | ADD_ASSIGN          {$$ = new std::string("+=");}
          | SUB_ASSIGN          {$$ = new std::string("-=");}
          | MUL_ASSIGN          {$$ = new std::string("*=");}
          | DIV_ASSIGN          {$$ = new std::string("/=");}
          | MOD_ASSIGN          {$$ = new std::string("%=");}
          | AND_ASSIGN          {$$ = new std::string("&=");}
          | XOR_ASSIGN          {$$ = new std::string("");}
          | OR_ASSIGN           {$$ = new std::string("|=");}
          /*| PTR_OP              {$$ = new std::string("->"  );}
          | DEC_OP              {$$ = new std::string("--");}
          | INC_OP              {$$ = new std::string("++");}*/
          | LEFT_OP             {$$ = new std::string("<<");}
          | RIGHT_OP            {$$ = new std::string(">>");}


DECLARATOR : T_STARPTR DIRECT_DECLARATOR { $$ = $2;}
           | DIRECT_DECLARATOR {$$ = $1;}


DIRECT_DECLARATOR : T_ID { $$ = new Variable(*$1); }

TYPE_SPECIFIER : T_INT { $$ = new std::string("int"); }
               | T_VOID { $$ = new std::string("void"); }
               | T_CHAR { $$ = new std::string("char"); }
               | T_SHORT { $$ = new std::string("short"); }
               | T_LONG { $$ = new std::string("long"); }
               | T_FLOAT { $$ = new std::string("float"); }
               | T_DOUBLE { $$ = new std::string("double"); }
               | T_SIGNED { $$ = new std::string("signed"); }
               | T_UNSIGNED{ $$ = new std::string("unsigned"); }

   /*CAST_EXPR : NOTARRAY_EXPR {$$ = $1;}*/
   /*
   NOTARRAY_EXPR : PRIMARY_EXPR      {$$ = $1;}
   | PRIMARY_EXPR OPERATOR NOTARRAY_EXPR {$$ = new OperatorProgram($1,$2,$3);}


   PRIMARY_EXPR : T_LBRACKET EXPR T_RBRACKET  {$$ = $2;}
   | T_NUMBER         {$$ = new Number($1);}
   | T_ID INC_OP             {$$ = new Variable(*$1);}


   EXPR : ASSIGN_EXPR              {$$ = $1;}
   | EXPR ASSIGN_EXPR         {$$ = new ProgramOther($1,$2);}
   */
   /*
   OPERATOR : T_ADD               {$$ = new std::string("+");}
   | T_MINUS             {$$ = new std::string("-");}
   | T_MULT              {$$ = new std::string("*");}
   | T_DIVID             {$$ = new std::string("/");}
   | T_EQUAL             {$$ = new std::string("=");}
   | T_MOD               {$$ = new std::string("%%");}
   | NE_OP               {$$ = new std::string("!=");}
   | EQ_OP               {$$ = new std::string("==");}
   | GE_OP               {$$ = new std::string(">=");}
   | LE_OP               {$$ = new std::string("<=");}
   | OR_OP               {$$ = new std::string("||");}
   | AND_OP              {$$ = new std::string("&&");}
   | PTR_OP              {$$ = new std::string("->");}
   | DEC_OP              {$$ = new std::string("--");}
   | INC_OP              {$$ = new std::string("++");}
   | LEFT_OP             {$$ = new std::string("<<");}
   | RIGHT_OP            {$$ = new std::string(">>");}
   | T_LESS              {$$ = new std::string("<");}
   | T_GREATER           {$$ = new std::string(">");}*/

   /*ASSIGN_OP : T_ADD               {$$ = new std::string("+");}
   | T_MINUS             {$$ = new std::string("-");}
   | T_MULT              {$$ = new std::string("*");}
   | T_DIVID             {$$ = new std::string("/");}
   | T_EQUAL             {$$ = new std::string("=");}
   | T_MOD               {$$ = new std::string("\\");}*/

%%

const Program *g_root; // Definition of variable (to match declaration earlier)

const Program *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
