
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
%token T_FLOAT T_CHAR T_DOUBLE T_VOID  T_ADD T_MINUS T_MULT T_DIVID T_MOD T_COMMA
%token  T_LSQRBRACKET T_RSQRBRACKET T_IF T_ELSE ELLIPSIS RIGHT_ASSIGN LEFT_ASSIGN T_WHILE
%token  ADD_ASSIGN  SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN AND_ASSIGN XOR_ASSIGN RIGHT_OP
%token OR_ASSIGN LEFT_OP INC_OP DEC_OP PTR_OP AND_OP OR_OP LE_OP GE_OP EQ_OP NE_OP T_COLON
%token T_AND  T_EXC T_WAVE T_XOR T_OR T_QUESTION T_DO T_FOR T_GOTO T_CONTINUE T_BREAK
%token T_LESS T_GREATER T_DOT T_SHORT T_LONG T_SIGNED T_UNSIGNED T_TYPEDEF T_EXTERN T_STATIC T_AUTO T_REGISTER


%nonassoc "next"
%nonassoc T_ELSE

%type <expr> PROGRAM FULL_DECLEAR DECLEAR DECLARATOR INIT_DECLARATOR INIT_DECLARATOR_LIST DIRECT_DECLARATOR
%type <expr> ASSIGN_EXPR EXPR PRIMARY_EXPR NOTARRAY_EXPR INITIALIZER BLOCK_ITEM BLOCK_ITEM_LIST COMP_STAT
%type <expr> FUNC_LIST FUNCTION  STATEMENT IF_STATEMENT EXPR_STATEMENT
%type <expr> JUMP_STATEMENT ITERATION_STATEMENT POSTFIX_EXPR CAST_EXPR
%type <expr> COND_EXPR LOGIC_OR_EXPR LOGIC_AND_EXPR INCLU_OR_EXPR EXCLU_OR_EXPR
%type <expr> AND_EXPR EQUA_EXPR RELATIONAL_EXPR SHIFT_EXPR ADDITIVE_EXPR MULT_EXPR
%type <number> T_NUMBER
%type <string> TYPE_SPECIFIER DECLEAR_SPECIFIERS T_INT T_ID T_ADD T_MINUS T_MULT T_DIVID T_MOD T_IF
%type <string> ASSIGN_OP //STORAGE_CLASS_SPEC
%start ROOT

%%
ROOT : PROGRAM { g_root = $1; }

PROGRAM : FULL_DECLEAR {$$=$1;}//{$$ = new Full_Declear($1);}
        | PROGRAM FULL_DECLEAR { $$ = new Program_Declear($1,$2);}

FULL_DECLEAR : DECLEAR  {$$ = new Global_Declear($1);}
             | FUNCTION {$$ = $1;}

DECLEAR : DECLEAR_SPECIFIERS T_SEMI { $$ = new NotUsed();}
        | DECLEAR_SPECIFIERS INIT_DECLARATOR_LIST T_SEMI { $$ = new Declear($2);}

DECLEAR_SPECIFIERS : TYPE_SPECIFIER { $$ = $1;}
                  /* | TYPE_SPECIFIER DECLEAR_SPECIFIERS //{$$ = $1;}
                   | STORAGE_CLASS_SPEC //{$$ = $1;}
                   | STORAGE_CLASS_SPEC DECLEAR_SPECIFIERS //{$$ =$1;}*/

INIT_DECLARATOR_LIST : INIT_DECLARATOR { $$ = $1;}
                     | INIT_DECLARATOR_LIST T_COMMA INIT_DECLARATOR {$$ = new Init_Dec_List($1,$3);}

INIT_DECLARATOR : DECLARATOR { $$ = new InitDeclar_1($1);}
                | DECLARATOR T_EQUAL INITIALIZER {$$ = new InitDeclar($1,$3);}

DECLARATOR : T_MULT DIRECT_DECLARATOR { $$ = $2;}
           | DIRECT_DECLARATOR {$$ = $1;}

DIRECT_DECLARATOR : T_ID { $$ = new Variable(*$1); }
                  | DIRECT_DECLARATOR T_LSQRBRACKET NOTARRAY_EXPR T_RSQRBRACKET {$$ = new Declar_array($1);}
                  | DIRECT_DECLARATOR T_LSQRBRACKET T_RSQRBRACKET {$$ = new Declar_array($1);}

INITIALIZER : ASSIGN_EXPR {$$ = $1;}

/*ASSIGN_EXPR : COND_EXPR*/

EXPR : ASSIGN_EXPR {$$=$1;}
     | EXPR T_COMMA ASSIGN_EXPR {$$ = new Expr($1,$3);}

ASSIGN_EXPR : COND_EXPR {$$=$1;}
            | NOTARRAY_EXPR ASSIGN_OP ASSIGN_EXPR {$$ = new Assign_Expr($1,$2,$3);} //redeclare

COND_EXPR : LOGIC_OR_EXPR {$$=$1;}
          | LOGIC_OR_EXPR T_QUESTION EXPR T_COLON COND_EXPR

LOGIC_OR_EXPR : LOGIC_AND_EXPR {$$=$1;}
              | LOGIC_OR_EXPR OR_OP LOGIC_AND_EXPR {$$ = new Expr($1,$3);} //||

LOGIC_AND_EXPR : INCLU_OR_EXPR {$$=$1;}
               | LOGIC_AND_EXPR AND_OP INCLU_OR_EXPR {$$ = new Expr($1,$3);} //&&

INCLU_OR_EXPR : EXCLU_OR_EXPR {$$=$1;}
              | INCLU_OR_EXPR T_OR EXCLU_OR_EXPR {$$ = new OR($1,$3);} //|

EXCLU_OR_EXPR : AND_EXPR {$$=$1;}
              | EXCLU_OR_EXPR T_XOR AND_EXPR {$$ = new XOR($1,$3);}//^

AND_EXPR : EQUA_EXPR {$$=$1;}
         | AND_EXPR T_AND EQUA_EXPR {$$ =new AND($1,$3);}//&

EQUA_EXPR : RELATIONAL_EXPR {$$=$1;}
          | RELATIONAL_EXPR EQ_OP RELATIONAL_EXPR {$$ = new EQ_Operator($1,$3);}// ==
          | RELATIONAL_EXPR NE_OP RELATIONAL_EXPR {$$ = new NE_OPerator($1,$3);} //!=

RELATIONAL_EXPR : SHIFT_EXPR {$$=$1;}
                | RELATIONAL_EXPR T_LESS SHIFT_EXPR {$$ =new LESS($1,$3);}//<
                | RELATIONAL_EXPR T_GREATER SHIFT_EXPR {$$ =new GREATER($1,$3);}// >
                | RELATIONAL_EXPR LE_OP SHIFT_EXPR {$$ =new LE($1,$3);}//<=
                | RELATIONAL_EXPR GE_OP SHIFT_EXPR {$$ =new GE($1,$3);}// >=

SHIFT_EXPR : ADDITIVE_EXPR {$$=$1;}
           | SHIFT_EXPR LEFT_OP ADDITIVE_EXPR {$$ =new LEFT($1,$3);}//<<
           | SHIFT_EXPR RIGHT_OP ADDITIVE_EXPR {$$ =new RIGHT($1,$3);}//>>


ADDITIVE_EXPR : MULT_EXPR {$$=$1;}
              | ADDITIVE_EXPR T_ADD MULT_EXPR {$$ = new AddOperator($1,$3);}
              | ADDITIVE_EXPR T_MINUS MULT_EXPR {$$ = new SubOperator($1,$3);}

MULT_EXPR : CAST_EXPR {$$=$1;}
          | MULT_EXPR T_MULT CAST_EXPR  {$$ = new MultOperator($1,$3);}
          | MULT_EXPR T_DIVID CAST_EXPR  {$$ = new DividOperator($1,$3);}
          | MULT_EXPR T_MOD CAST_EXPR  {$$ = new ModOperator($1,$3);}

CAST_EXPR : NOTARRAY_EXPR {$$=$1;}

NOTARRAY_EXPR : POSTFIX_EXPR {$$=$1;}
              /*| INC_OP NOTARRAY_EXPR  //{$$=$2;}
              | DEC_OP NOTARRAY_EXPR  //{$$=$2;}
              | PRIMARY_EXPR OPERATOR NOTARRAY_EXPR //{$$=$3;}*/

POSTFIX_EXPR : PRIMARY_EXPR  {$$=$1;}
             /*| POSTFIX_EXPR T_LSQRBRACKET EXPR T_RSQRBRACKET //{$$=$1;}
             | POSTFIX_EXPR T_LBRACKET T_RBRACKET //{$$=$1;}*/
             //| POSTFIX_EXPR INC_OP  {$$= new INC_OP($1,$2); }
            /* | POSTFIX_EXPR DEC_OP //{$$=$1;}
             | POSTFIX_EXPR PTR_OP T_ID //{$$=$1;}
             | POSTFIX_EXPR T_DOT T_ID //{$$ = $1;}*/


PRIMARY_EXPR : T_NUMBER         {$$ = new Number($1);}
             | T_ID              {$$ = new Variable(*$1);}

TYPE_SPECIFIER : T_INT { $$ = new std::string("int"); }
               /*| T_VOID { $$ = new std::string("void"); }
               | T_CHAR { $$ = new std::string("char"); }
               | T_SHORT { $$ = new std::string("short"); }
               | T_LONG { $$ = new std::string("long"); }
               | T_FLOAT { $$ = new std::string("float"); }
               | T_DOUBLE { $$ = new std::string("double"); }
               | T_SIGNED { $$ = new std::string("signed"); }
               | T_UNSIGNED{ $$ = new std::string("unsigned"); }*/


/*STORAGE_CLASS_SPEC : T_TYPEDEF {$$ = new std::string("typedef");}
                   | T_EXTERN {$$ = new std::string("extern");}
                   | T_STATIC {$$ = new std::string("static");}
                   | T_AUTO {$$ = new std::string("auto");}
                   | T_REGISTER {$$ = new std::string("register");}*/

ASSIGN_OP : T_EQUAL             {$$ = new std::string("=");}
          | ADD_ASSIGN          {$$ = new std::string("+=");}
          | SUB_ASSIGN          {$$ = new std::string("-=");}
          | MUL_ASSIGN          {$$ = new std::string("*=");}
          | DIV_ASSIGN          {$$ = new std::string("/=");}
          | MOD_ASSIGN          {$$ = new std::string("%=");}
          | LEFT_ASSIGN         {$$ = new std::string("<<=");}
          | RIGHT_ASSIGN        {$$ = new std::string(">>=");}
          | OR_ASSIGN           {$$ = new std::string("|=");}
          | AND_ASSIGN          {$$ = new std::string("&=");}
          | XOR_ASSIGN          {$$ = new std::string("^=");}


FUNCTION : DECLEAR_SPECIFIERS DECLARATOR T_LBRACKET FUNC_LIST T_RBRACKET COMP_STAT {$$ = new Function_Four_Comp($1, $2, $4, $6);}
         | DECLEAR_SPECIFIERS DECLARATOR T_LBRACKET T_RBRACKET COMP_STAT {$$ = new Function_Three_Comp(*$1,$2,$5);}
         | DECLARATOR T_LBRACKET FUNC_LIST T_RBRACKET COMP_STAT {$$ = new Function_Three_Comp_Program($1,$3,$5);}
         | DECLARATOR T_LBRACKET T_RBRACKET COMP_STAT {$$ = new Function($1,$4);}

FUNC_LIST :  DECLEAR_SPECIFIERS DECLARATOR {$$ = new Func_List(*$1,$2);} //int
          |  DECLEAR_SPECIFIERS DECLARATOR T_COMMA FUNC_LIST  {$$ = new Func_List_Rec(*$1,$2,$4);}


COMP_STAT : T_LCURLYBRACKET BLOCK_ITEM_LIST T_RCURLYBRACKET {$$ = new Comp_Stat($2);}
          | T_LCURLYBRACKET T_RCURLYBRACKET { $$ = new NotUsed();}

BLOCK_ITEM_LIST : BLOCK_ITEM {$$ = new Block_Item_List($1);}
                | BLOCK_ITEM_LIST BLOCK_ITEM {$$ = new Block_Item_List_Rec($1,$2);}

BLOCK_ITEM : DECLEAR    {$$ = new Block_Item($1);}
           | STATEMENT  {$$ = new Block_Item_Stat($1);}

STATEMENT : IF_STATEMENT {$$ = $1;}
          | ITERATION_STATEMENT {$$ = $1;}
          | JUMP_STATEMENT {$$ = $1;}
          | COMP_STAT {$$ = $1;}
          | EXPR_STATEMENT {$$ = $1;}

EXPR_STATEMENT : T_SEMI {$$ = new NotUsed(); }
               | EXPR T_SEMI {$$ = $1; }

ITERATION_STATEMENT : T_WHILE T_LBRACKET EXPR T_RBRACKET STATEMENT  {$$ = new While_Stat($3, $5);} //{$$ = new NotUsed();}
                    | T_DO STATEMENT T_WHILE T_LBRACKET EXPR T_RBRACKET {$$ = new DoWhile_Stat($2,$5);} //{$$ = new While_Stat($2);}
                    | T_FOR T_LBRACKET EXPR_STATEMENT EXPR_STATEMENT T_RBRACKET  STATEMENT  {$$ = new For_Stat($3,$4,$6);}
                    | T_FOR T_LBRACKET EXPR_STATEMENT EXPR_STATEMENT EXPR T_RBRACKET  STATEMENT  {$$ = new For_Stat_Four($3,$4,$5,$7);}
          //in c99          //| T_FOR T_LBRACKET DECLEAR EXPR_STATEMENT EXPR T_RBRACKET  STATEMENT  {$$ = new For_Stat_Four($3,$4,$5,$7);}

JUMP_STATEMENT : T_GOTO T_ID T_SEMI {$$ = new NotUsed(); }
               | T_CONTINUE T_SEMI {$$ = new NotUsed(); }
               | T_BREAK T_SEMI {$$ = new NotUsed(); }
               | T_RETURN T_SEMI {$$ = new Return_Null(); }
               | T_RETURN EXPR T_SEMI {$$ = new Return($2); }


IF_STATEMENT : T_IF T_LBRACKET EXPR T_RBRACKET  STATEMENT  T_ELSE  STATEMENT  {$$ = new Else_Stat($3,$5,$7);}
             | T_IF T_LBRACKET EXPR T_RBRACKET  STATEMENT  {$$ = new If_Stat($3, $5);} %prec "next"











%%

const Program *g_root; // Definition of variable (to match declaration earlier)

const Program *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
