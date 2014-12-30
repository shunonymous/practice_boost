BINDIR = ../boost_practice_bin/
CC = clang++

option:program_option.cpp
	$(CC) -o $(BINDIR)program.options program_option.cpp -lboost_program_options

dir:
	mkdir -p $(BINDIR)
