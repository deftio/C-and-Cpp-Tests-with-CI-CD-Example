[![Language](https://img.shields.io/badge/Language-C%2FC%2B%2B-blue.svg)](https://github.com/deftio/C-and-Cpp-Tests-with-CI-CD-Example)
[![Build Status](https://img.shields.io/badge/Build-Passing-brightgreen.svg)](https://github.com/deftio/C-and-Cpp-Tests-with-CI-CD-Example)
[![CI](https://github.com/deftio/C-and-Cpp-Tests-with-CI-CD-Example/actions/workflows/ci.yml/badge.svg)](https://github.com/deftio/C-and-Cpp-Tests-with-CI-CD-Example/actions/workflows/ci.yml)
[![Coverage Status](https://coveralls.io/repos/github/deftio/C-and-Cpp-Tests-with-CI-CD-Example/badge.svg?branch=master)](https://coveralls.io/github/deftio/C-and-Cpp-Tests-with-CI-CD-Example?branch=master)
[![License](https://img.shields.io/badge/License-BSD%202--Clause-blue.svg)](https://opensource.org/licenses/BSD-2-Clause)

# C/C++ Testing with CI/CD Example

A quick overview of testing C/C++ code, covering basic unit tests to continuous integration. In this repo we'll go through concepts such as unit testing and coverage to CI with a simple working example.

## What's In This Repository

This repository shows testing concepts using a simple C library. We'll explore:

- Unit testing basics
- Code coverage and what it tells us
- Test-driven development concepts
- Continuous integration with GitHub Actions
- How these pieces fit together in practice

## Project Structure

```
.
├── lib.h                  # Library header with function declarations
├── lib.c                  # Library implementation (math & bitwise operations)
├── test-library.c         # Test suite with assertions
├── makefile              # Build rules with coverage flags
├── CMakeLists.txt        # CMake build configuration (alternative to make)
├── run_coverage_test.sh  # Script to generate coverage reports
├── .github/
│   └── workflows/
│       └── ci.yml        # GitHub Actions CI configuration
├── codecov.yml           # Coverage service configuration
└── .gitignore            # Git ignore patterns
```

## Getting Started with Testing

### Why Test?

When we write a function, we usually run it a few times manually to check it works. Testing just formalizes this process. Instead of manual checks, we write code that does the checking for us.

Testing helps us understand:

- **Does it work?** - Does the code do what we intended?
- **Does it handle edge cases?** - What about negative numbers? Zero? Maximum values? (or even more complex inputs)
- **Will it keep working?** - When we change other code, did we break this?
- **Is it completely tested?** - Did we miss any scenarios?

### A Simple Test Example

Let's look at a basic test. In this repo we have a small math operations library.  Here's one of our library functions:

```c
// From lib.c
int op_add(int x, int y) {
    int r = x + y;
    return r;
}
```

To test this, we write a function that calls our function in dedicated test program:

```c
// From test-library.c
if (op_add(2, 3) != 5) {
    printf("TEST FAILED: op_add(2, 3) should equal 5\n");
    return 1;  // Exit with error
}
printf("TEST PASSED: op_add works correctly\n");
```

This is a test! It's simple but powerful:
- It calls the function with known inputs
- It checks if the output is correct
- It reports success or failure

### Chapter 3: Testing All Paths

Now let's look at a slightly more complex example:

```c
int add5ifGreaterThan2(int a) {
    int r;
    if (a > 2)
        r = a + 5;    // Path 1: When a > 2
    else
        r = a;        // Path 2: When a <= 2
    return r;
}
```

This function has **two execution paths**. If we only test with `a = 10`, we only test Path 1. We've missed half the function! 

To test completely, we need to test **every path**:

```c
// Test Path 1: When a > 2
assert(add5ifGreaterThan2(3) == 8);   // 3 + 5 = 8 ✓
assert(add5ifGreaterThan2(10) == 15); // 10 + 5 = 15 ✓

// Test Path 2: When a <= 2  
assert(add5ifGreaterThan2(1) == 1);   // Returns 1 unchanged ✓
assert(add5ifGreaterThan2(2) == 2);   // Boundary: exactly 2 ✓

// Test edge cases
assert(add5ifGreaterThan2(0) == 0);   // Zero ✓
assert(add5ifGreaterThan2(-5) == -5); // Negative ✓
```

**Key Insight**: Every `if` statement creates paths. The same is true for switch statements. Every path needs tests.

### Chapter 4: Enter Code Coverage

But how do we know we've tested all paths? That's where **code coverage** comes in.  We can use a tool to find what paths have been taken in our tests and which ones have not been tested.

Code coverage is like a GPS tracker for your tests - it shows you exactly which lines of code were executed during testing. Let's see it in action:

```bash
# Run tests with coverage tracking
make clean
make
./test-library.out
gcov lib.c
cat lib.c.gcov
```

The coverage report shows:

```
        2:    9:int op_and(int x, int y) {
        2:   10:    return x & y;
        -:   11:}
        -:   12:
        3:   17:int op_xor(int a, int b){
        3:   18:    int r = a ^ b;
        3:   19:    return r;
        -:   20:}
        -:   21:
    #####:   22:int op_xnor(int a, int b){
    #####:   23:    return ~(a ^ b);
        -:   24:}
```

What do these symbols mean?
- `2:` - This line ran 2 times ✓
- `3:` - This line ran 3 times ✓
- `#####:` - **This line NEVER ran!** ⚠️
- `-:` - Non-executable line (comments, brackets)

**The smoking gun**: Lines 22-23 (`op_xnor` function) were never tested! Our test suite has a gap.

#### Coverage Metrics

From this report, we calculate:
- **Lines of code**: 10 executable lines
- **Lines tested**: 8 lines executed
- **Coverage**: 8/10 = 80%

To achieve 100% coverage, we need to add:
```c
assert(op_xnor(0x0F, 0xF0) == ~(0x0F ^ 0xF0));  // Test the missing function
```

### Chapter 5: The Coverage Paradox

**Warning**: 100% coverage ≠ bug-free code!

Consider this function with 100% line coverage:
```c
int divide(int a, int b) {
    return a / b;  // 100% covered if we test divide(10, 2)
}
```

But what about `divide(10, 0)`? 💥 Division by zero!

Coverage tells you what you tested, not what you missed. As Dijkstra famously said: *"Testing shows the presence, not the absence of bugs."*

Research shows (Namin & Andrews, 2009):
- **< 50% coverage**: Many bugs remain
- **70-80% coverage**: Good balance of effort vs benefit
- **> 90% coverage**: Diminishing returns

### Testing Frameworks for C/C++

While this example uses simple assertions to keep things clear, there are many testing frameworks available that provide more features:

#### Popular C/C++ Testing Frameworks

- **[Google Test](https://github.com/google/googletest)** - Feature-rich, widely used in industry
- **[Catch2](https://github.com/catchorg/Catch2)** - Header-only, simple to integrate
- **[Unity](http://www.throwtheswitch.org/unity)** - Minimal framework, perfect for embedded systems
- **[CppUTest](http://cpputest.github.io/)** - Designed specifically for embedded development
- **[Check](https://libcheck.github.io/check/)** - Unit testing framework for C
- **[CUnit](http://cunit.sourceforge.net/)** - Lightweight C testing framework
- **[Boost.Test](https://www.boost.org/doc/libs/release/libs/test/)** - Part of the Boost libraries

#### Why We Use Simple Assertions Here

This repository intentionally uses basic assertions rather than a framework to:
- Focus on testing concepts rather than framework syntax
- Keep the example accessible to embedded developers
- Show that testing doesn't require complex tools
- Minimize dependencies

Once you understand the concepts, you can easily adopt any framework that suits your needs.

### Chapter 6: Test-Driven Development (TDD)

TDD flips the script: write tests BEFORE code. 

1. **Red** 🔴 - Write a failing test
2. **Green** 🟢 - Write minimal code to pass
3. **Refactor** 🔄 - Clean up while tests stay green

Example:
```c
// Step 1: Write test first (RED - fails because function doesn't exist)
assert(op_multiply(3, 4) == 12);

// Step 2: Write minimal code (GREEN - just enough to pass)
int op_multiply(int a, int b) {
    return a * b;
}

// Step 3: Refactor if needed (keep it GREEN)
```

### Chapter 7: Continuous Integration - Automating Trust

Now imagine you're working with a team. How do you ensure everyone's code is tested? **Enter CI/CD**.

#### The Manual Way (Error-Prone)
1. Developer writes code
2. Developer remembers to run tests (maybe)
3. Developer commits code
4. Other developers pull broken code
5. 😱 Everything breaks

But we can do better.  In fact we can *force* the tests to be run every time code is checkedin to the repo.   This is what CI (continuosu integration) is about.

#### The CI Way (Automated)
1. Developer writes code
2. Developer commits code
3. CI automatically runs all tests
4. If tests fail, the commit is rejected
5. ✅ Main branch stays clean

With CI you can have some assurance that the test suites are being run and even how much coverage there is with each check-in.

Look at the badges at the top of this README:
- **Green CI badge**: All tests passing, safe to use
- **Red CI badge**: Tests failing, something's broken
- **Coverage badges**: Show test coverage percentage

These update **automatically** with every commit!

### Chapter 8: When CI Fails - The Safety Net

What happens when CI detects a failure?

```yaml
# From .github/workflows/ci.yml
- name: Run tests
  run: |
    ./test-library.out
    # If this fails, the build stops here!
```

If tests fail:
1. CI stops immediately ❌
2. Badge turns red 🔴
3. GitHub can block the merge 
4. Team gets notified
5. **No broken code reaches production**

This is why CI exists - it's a safety net that never forgets to test.

### Chapter 9: From CI to CD

- **CI (Continuous Integration)**: Automatically test every change
- **CD (Continuous Deployment)**: If tests pass, automatically deploy

The full pipeline:
```
Code → Test → Build → Deploy
      ↑
      CI ensures this never fails
```

If CI fails, deployment stops. This prevents broken code from reaching users.

## Running the Examples

### Quick Start

```bash
# Clone this repository
git clone https://github.com/deftio/C-and-Cpp-Tests-with-CI-CD-Example.git
cd C-and-Cpp-Tests-with-CI-CD-Example

# Build and run tests
make
./test-library.out

# Check coverage
./run_coverage_test.sh
cat lib.c.gcov  # Shows which lines were tested
```

### Things to Try

- Run coverage and see if any functions are missing tests
- Add a test for any untested functions (hint: check `op_xnor`)
- Modify a function to break its test, then fix it
- Fork the repo and watch GitHub Actions run your tests automatically

## The Bigger Picture

This simple example demonstrates principles that scale to massive projects:

- **Linux Kernel**: ~30 million lines, extensive test suites
- **Chrome Browser**: Thousands of tests run on every commit
- **Embedded Systems**: Safety-critical code with 100% coverage requirements

The task of writing tests, check coverage, automate with CI are the same ones used by professional developers worldwide.

## Testing Concepts

Beyond CI and CD are many other types of tests, such as integration tests which show how well code connects together, system and endurance tests which test how robust code is to certain types of errors or whether it can run a long time.  Often small memory leaks are not caught early on because it takes a long time to for enough memory to be lost to make the system unstable.   Knowing your domain well is key to avoiding many classes of errors.

### Frequently Asked Questions

**Q: How much testing is enough?**
A: Generally, when you feel confident making changes without breaking things.

**Q: Should I test simple/obvious code?**
A: It's often worth it - simple code can have surprising bugs.

**Q: What if code is hard to test?**
A: This often suggests the code could be structured better.


## Build Instructions - The code in this repo

The code in this repo is written in C (but build tools can also handle C++)

### Prerequisites
- **Compiler**: GCC or Clang (C99+)
- **Tools**: Make and/or CMake
- **Coverage**: gcov (included with GCC)

### Using Make
```bash
make clean    # Clean build artifacts
make          # Build project
make test     # Run tests  
make coverage # Generate coverage report
```

### Using CMake
```bash
mkdir build && cd build
cmake ..
make
make test
make coverage
```

### Platform Installation

**Ubuntu/Debian:**
```bash
sudo apt-get install gcc make cmake lcov
```

**macOS:**
```bash
brew install gcc cmake lcov
```

**Windows:**
Use WSL or MinGW

## Coverage Services Setup

To get coverage badges working:

### Codecov
1. Visit [codecov.io](https://codecov.io)
2. Sign in with GitHub
3. Add your repository
4. (Optional) Add CODECOV_TOKEN to GitHub secrets

### Coveralls  
1. Visit [coveralls.io](https://coveralls.io)
2. Sign in with GitHub
3. Enable your repository

Both services are free for open source projects.

## References

### Online Resources
- [Unit Testing](https://en.wikipedia.org/wiki/Unit_testing) - Wikipedia
- [Continuous Integration](https://www.martinfowler.com/articles/continuousIntegration.html) - Martin Fowler
- [Google Test Primer](https://google.github.io/googletest/primer.html) - Google

## Contributing

Pull requests are welcome! This repository is meant to be educational, so contributions that improve clarity or add examples are especially valued.

## Version History

- **1.0.4** (2025) - Added CMake, enhanced documentation, focus on testing narrative
- **1.0.3** (2024) - Added GitHub Actions
- **1.0.2** (2021) - Travis CI updates
- **1.0.0** (2016) - Initial release

## License

BSD 2-Clause License - see [LICENSE.txt](LICENSE.txt)

© 2016-2025 M. A. Chatterjee <deftio [at] deftio [dot] com>