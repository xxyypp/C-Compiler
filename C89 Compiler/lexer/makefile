
CPPFLAGS += -W -Wall -g -std=gnu++11

c_lexer.yy.cpp : c_lexer.flex
	flex -o c_lexer.yy.cpp  c_lexer.flex

bin/c_lexer : c_lexer.yy.cpp c_main.cpp
g++ $(CPPFLAGS) -o bin/c_lexer c_lexer.yy.cpp c_main.cpp
