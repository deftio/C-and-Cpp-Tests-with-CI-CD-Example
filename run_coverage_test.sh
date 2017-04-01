#!/bin/bash

#this script calls the code coverage testing program gcov (part of the gcc suite)

#fist clean all object files
make clean

#compile all the c files, link etc
make 

# run the example.out program ... with test coverage (see makefile for flags)
./test-library.out

# gcov is the gcc suite test coverage program.  We're interested in the coverage
# the lib.c file.  
gcov lib.c

# now the code coverage is in this file:
# lib.c.gcov  
# which can be viewed in any text editor 
