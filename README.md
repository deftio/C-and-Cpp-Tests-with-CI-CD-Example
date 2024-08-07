[![Build Status](https://app.travis-ci.com/deftio/C-and-Cpp-Tests-with-CI-CD-Example.svg?token=Pc8RELtY2RwRuTT1tezA&branch=master)](https://app.travis-ci.com/deftio/C-and-Cpp-Tests-with-CI-CD-Example)
[![Coverage Status](https://coveralls.io/repos/github/deftio/travis-ci-cpp-example/badge.svg?branch=master)](https://coveralls.io/github/deftio/travis-ci-cpp-example?branch=master)
[![License](https://img.shields.io/badge/License-BSD%202--Clause-blue.svg)](https://opensource.org/licenses/BSD-2-Clause)
[![Github Actions Ci](https://github.com/deftio/C-and-Cpp-Tests-with-CI-CD-Example/actions/workflows/ci.yml/badge.svg)](https://github.com/deftio/C-and-Cpp-Tests-with-CI-CD-Example/actions/workflows/ci.yml/badge.svg)

# Simple Example for C/C++ Tests with Continuous Integration (CI)

This repository demonstrates setting up a basic testing suite with GitHub badges for a C/C++ library. It covers the basics of setting up unit tests, coverage tests, and continuous integration using GitHub Actions or Travis-CI. The repository contains a simple library tested for coverage and integration.

## Motivation

This project provides a small standalone example to show continuous integration tools and workflows for C (or C++) language testing without the overhead of a much larger project. 

## Features

The lib.h and lib.c files are examples of testing an embedded library. Many of the projects I work on are for embedded systems, so I wanted a way to get a build badge for these projects. This example abstracts how the CI process works without the complexities of a "real" project.

## How It Works

This demo project includes a C library with a few demo functions in lib.h and lib.c. The code doesn't do much but serves as a simple abstraction of what is necessary to build a larger project. This repository provides an overview of testing and how to get build badges working on GitHub.

## Quick Overview of Testing

Testing helps tell us if the software is working as intended.  This means understanding what we want to test in to a few key areas.

### Common Testing Questions

* Does it run as intended?
* Does it have side effects when running?
** Are resources tied up such as ports blocked, thread contention?  
** Are other programs or services affected unintentionally?
* Are all possible execution paths tested?  (coverage)
* How much memory or resources are used? Is memory freed correctly / are their leaks?
* Does it exit gracefully?

### Unit Testing

Unit Testing involves writing small tests to ensure that a piece of code, typically a module or library, passes a set of tests to verify it runs as intended. The goal is to craft tests that cover all possible paths of execution in the code.

Example function:

```c
int add5ifGreaterThan2(int a) {
    int r;
    if (a > 2)
        r = a + 5;
    else
        r = a;
    return r;
}
```

Test code:

```c
ASSERT(add5ifGreaterThan2(1) == 1) // tests if (a <= 2) case
ASSERT(add5ifGreaterThan2(3) == 8) // tests if (a > 2) case
```

#### More Info

Here is a link to the wikipedia article for more depth on unit testing practice and history: [Unit_testing](https://en.wikipedia.org/wiki/Unit_testing).


### Testing Frameworks

Unit testing frameworks make it easier to automate testing. Many languages have frameworks named like JUnit (for Java) or PyUnit (for Python). In C/C++, several frameworks are available, including:

* [CppUTest](http://cpputest.github.io/) - A unit test framework for C++
* [Boost C++ Unit Test Framework](http://www.boost.org/doc/libs/1_35_0/libs/test/doc/components/utf/index.html) - This is the test framework used by the popular Boost library for C++
* [Typemock](https://www.typemock.com/) - a commercial Test Package
* [Cantata](http://www.qa-systems.com/tools/cantata) - a commercial Test Package
* [Google Test](https://github.com/google/googletest) - we'll be using this here.  Google Test is a free opensource framework using special macros for asserting when code doesn't perform as expected.
* [Catch](https://github.com/philsquared/Catch) - Catch is a test framework for C

We'll be using Google Test (gtest) in this example.

Here is the link to the project source
[Google Test](https://github.com/google/googletest)

### Installing Google Test

On Ubuntu Linux, install gtest using the following commands:

```bash
sudo apt-get install libgtest-dev
sudo apt-get install cmake
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
sudo mkdir /usr/local/lib/googletest
sudo ln -s /usr/lib/libgtest.a /usr/local/lib/gtest/libgtest.a
sudo ln -s /usr/lib/libgtest_main.a /usr/local/lib/gtest/libgtest_main.a
```

You can read more about the Google Test project here: [Testing Primer](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md)  

### Testing vs Continuous Integration

Once you've written unit tests and run them locally, CI services (such as Travis-CI, GitHub Actions, Circle-CI, Jenkins, and others) can automatically run your test suites and report the results **every time you check in**. CI can be configured to accept or reject your code based on the tests passing, and can even deploy your code automatically if it passes all the tests.  This is called Continuous Deployment, or CD.

### Using Travis-CI as a CI Provider
Travis-CI
Travis-CI looks in the .travis.yml file to see how to run the code. It compiles lib.c and example.c into lib.o and example.o, and then links them to produce the executable example.out. The test suite is run, and the exit code is used to determine if the build passes.

### Using Github Actions as CI Provider

GitHub Actions work similarly. When code is pushed to the main branch, GitHub triggers an action to look at the ./github/workflows/ci.yml file, which specifies the environment, builds the code, runs the test script, and reports success or failure.

### Code Coverage

Code coverage is achieved using gcov from the gcc test suite. To see the code coverage:

```bash
make clean
make
./test-library.out
gcov lib.c
```

This generates the file lib.c.gcov, which can be viewed in any text editor. Lines with #### have never been run.

## FAQ

Q: What's the point of this repo if it doesn't do anything?
A: It's a simple example of using Travis-CI for testing purposes.

Q: How can I make it fail for testing purposes?
A: Modify a line in main.c to make it fail, or use other methods to test failure cases.

Q: Why isn't there a proper unit test framework?
A: This is a barebones test of integration and badge service.

## License

(OSI Approved BSD 2-clause)

version 1.0.3 (added GitHub Actions support)
version 1.0.2 (updated for travis-ci.com transition) M. A. Chatterjee

(c) 2016 and later M. A. Chatterjee <deftio [at] deftio [dot] com>
