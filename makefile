# Makefile for C/C++ Testing Example with Code Coverage
# Author: M A Chatterjee <deftio [at] deftio [dot] com>
# 
# This makefile builds the library and test suite with coverage instrumentation
# using gcov (part of the GCC suite) via -ftest-coverage -fprofile-arcs flags
# 
# C Standard: This code is compatible with C99 and all later standards (C11, C17, C23)
# To specify a standard, use: make CFLAGS="-std=c11 $(CFLAGS)"

# Compiler and flags
CC = gcc
CFLAGS = -I. -Wall -Wextra -ftest-coverage -fprofile-arcs
LDFLAGS = -lm -lncurses
OPTIMIZATION = -O0  # Use -O0 for accurate coverage, -Os for size optimization

# Files
DEPS = lib.h
SOURCES = lib.c test-library.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = test-library.out

# Coverage files
COVERAGE_FILES = *.gcda *.gcno *.gcov *.info

# Default target
all: $(TARGET)

# Build object files
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(OPTIMIZATION)

# Link the test executable
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(OPTIMIZATION)

# Run tests
test: $(TARGET)
	./$(TARGET)

# Generate coverage report
coverage: test
	gcov lib.c
	@echo "Coverage report generated in lib.c.gcov"

# Clean build artifacts and coverage files
clean:
	rm -f $(OBJECTS) $(TARGET) $(COVERAGE_FILES)
	rm -f *.asm *.lst *.sym *.rel *.s

# Clean everything including the executable
distclean: clean
	rm -f $(TARGET)

.PHONY: all test coverage clean distclean

