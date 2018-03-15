CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include

src/c_parser.tab.cpp src/c_parser.tab.hpp : src/c_parser.y
	bison -v -d src/c_parser.y -o src/c_parser.tab.cpp

src/c_parser.yy.cpp : src/c_parser.flex src/c_parser.tab.hpp
	flex -o src/c_parser.yy.cpp  src/c_parser.flex

bin/c_parser : src/c_parser.o src/c_parser.tab.o src/c_parser.yy.o src/c_parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/c_parser $^

clean :
	rm src/*.o
	rm bin/*
	rm src/*.tab.cpp
	rm src/*.yy.cpp
	rm src/*.tab.hpp
	rm src/*.output
