CXXFLAGS += -std=c++11 -w -Wall -g
CXXFLAGS += -I include

bin/% : src/%.cpp
	mkdir -p bin
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

bin/interpreter : src/ast_parse.o src/ast_pretty_print.o src/ast_interpret.o

bin/compiler : src/ast_parse.o src/ast_pretty_print.o src/ast_compile.o

bin/pretty_print : src/ast_parse.o src/ast_pretty_print.o

bin/constant_fold : src/ast_parse.o src/ast_pretty_print.o

bin/dead_branch_removal : src/ast_parse.o src/ast_pretty_print.o

bin/constant_propagation : src/ast_parse.o src/ast_pretty_print.o

bin/generate_mips : src/ast_parse.o src/ast_pretty_print.o src/ast_generate_mips.o

clean :
	-rm bin/*
	-rm src/*.o
	-rm working/*/*.txt
