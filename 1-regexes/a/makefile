CPPFLAGS += -W -Wall -g -std=gnu++11

histogram_lexer.yy.cpp : histogram_lexer.flex
	flex -o histogram_lexer.yy.cpp  histogram_lexer.flex

histogram : histogram_lexer.yy.cpp histogram_main.cpp
	g++ $(CPPFLAGS) -o histogram  histogram_lexer.yy.cpp histogram_main.cpp

clean :
<<<<<<< HEAD
	-rm histogram histogram
=======
	-rm histogram histogram.exe
>>>>>>> 9a7eb46fe741214ed4e448aff0d8728c1fe2fe5c
	-rm *.yy.cpp
	-rm test/out/*
