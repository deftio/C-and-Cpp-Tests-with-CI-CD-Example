# makefile for  posix tests (simple test lib coverage for embedded systems)
# @author M A Chatterjee <deftio [at] deftio [dot] com>

# test coverage is achieved usding gcov (part of gcc suite)
# this is done with the flags  -ftest-coverage -fprofile-arcs 
# see run_coverage_test.sh to see how to call code coverage tests        
CC=gcc
CFLAGS = -I. -Wall -ftest-coverage -fprofile-arcs 
DEPS   = lib.h
OBJ    = lib.o test-library.o
                  
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

test-library.out: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -lm -lncurses -Os 

clean :
	rm  *.o  *.asm  *.lst *.sym *.rel *.s *.gc* -f *.info

