# make file for dioci posix tests (simple interpreter for embedded systems)
# @author M A Chatterjee <deftio [at] deftio [dot] com>

CC=gcc
CFLAGS=-I. -Wall
DEPS = lib.h
OBJ  = lib.o main.o
                  
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

example.out: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -lm -lncurses -Os

clean :
	rm  *.o  *.asm  *.lst *.sym *.rel *.s -f

