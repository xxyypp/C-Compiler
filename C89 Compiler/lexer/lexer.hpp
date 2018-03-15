#ifndef histogram_hpp
#define histogram_hpp

#include <string>

enum TokenType{
    None   = 0, // This indicates there are no more tokens
    Constant = 1, // token codes must be positive
    Keyword = 2,
    Identifier = 3,
    Operator =4,
    StringLiteral = 5,
    Invalid = 6,
    Preprocess = 7
};

union TokenValue{
    double numberValue;
    std::string *wordValue;
};

// This is a global variable used to move the
// attribute value from the lexer back to the
// main program.
// By convention it is called yylval, as that is
// the name that will be automatially generated
// by Bison (see next lab).
extern TokenValue yylval;
extern int LineNo;
extern int ColNo;
extern std::string SourceLocation;
extern int SourceLineNo;
//extern std::string wValue;

// This is the lexer function defined by flex. Each
// time it is called, a token type value will be
// returned.
extern int yylex();

#endif
