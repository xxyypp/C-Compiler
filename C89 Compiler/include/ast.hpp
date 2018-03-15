#ifndef ast_hpp
#define ast_hpp

#include "ast/ast_program.hpp"
#include "ast/ast_variable_num.hpp"
#include "ast/ast_notused.hpp"
#include "ast/ast_declear.hpp"
#include "ast/ast_operator.hpp"
#include "ast/ast_function.hpp"
#include "ast/ast_selection.hpp"
#include "ast/ast_assign.hpp"
#include "ast/ast_statement.hpp"
#include "ast/ast_expr.hpp"


extern const Program *parseAST();

#endif
