[![Build Status](https://travis-ci.org/deftio/travis-ci-cpp-example.svg?branch=master)](https://travis-ci.org/deftio/travis-ci-cpp-example)
[![Coverage Status](https://coveralls.io/repos/github/deftio/travis-ci-cpp-example/badge.svg?branch=master)](https://coveralls.io/github/deftio/travis-ci-cpp-example?branch=master)
[![License](https://img.shields.io/badge/License-BSD%202--Clause-blue.svg)](https://opensource.org/licenses/BSD-2-Clause)

# Simple Example for C/C++ Testing

This repo covers setting up a basic testing suite with github badges for a C/C++ library.  Its not meant to be deep tutorial on testing but just cover some basics of setting up unit tests, coverage tests, and continuous integration (in this case using Travis-CI).  The repo doesn't have a lot of code - there is a simple library which is tested for coverage and integration.  

### Motivation
I just wanted to make a small standalone test project to see tools and workflow for C (or C++) language testing.  


copyright (C) 2016-  <M. A. Chatterjee>  <deftio [at] deftio [dot] com>
version 1.0 M. A. Chatterjee


## Features

The lib.h / lib.c files are broken out as examples of testing an embedded library.   Most of the projects I work on are for embedded systems so I wanted a way to get a build badge for these embedded projects.  Since many of those compilers and environments are not on Linux I wanted just a simple abstraction of how the Travis build project works without all the complexities of a "real" project.


## How it works

In this demo project there is a C library (could also be C++ etc).  The library code is just a few demo functions which are in the lib.h and lib.c files.  They don't really do anything but allow for simple abstraction of what is necessary to build a larger project.  This repo and project are meant to provide a quick overview of testing and how to get build badges working on Github.




### Quick Overview of Testing

Installing google test suite (a unit test framework)  -- could have used other test frameworks such as CppUnit or etc.

Common Testing "Questions" about a project:
* Does it run as intended?  (is it funcitonally correct)
* Does it have side effects when running? (are resources tied up such as ports blocked, thread contention?)
* Are all the possible permutations of execution tested? (code coverage)
* How much memory or resources are used? (is memmory efficiently used?  Is memory freed correctly after use?)
* Does it exit gracefully? (are any resources requested released before the code exits?)



### Unit Testing 
Unit Testing is a practice of writting small tests to see that piece of code, typically a full module or library, passes a set of tests to make sure it runs as intended.  The simple unit tests are done after writing function.  We then make a small program (the Unit test program) which calls our new function with as many different example parameters as we think are appropriate to make sure it works correctly.  If the results returned match the expected results we can say the function passes the test.  If the results for a given set of parameters don't agree we call an assertion (usually via a special ASSERT type macro) which records the failure and attempts to keep running then test in our test program.  The goal is to be able to craft a set of these tests which test all the possible paths of execution in our code and passes all the test.  

Note that its not the goal to create a test that passes every possible permutation of the input parameters - as this could be an impossibly large number or variations even for just a few parameters.  This idea of testing all the possible paths of exeuction is called code coverage.  Testing code coverage is done with tools which see if the test program has successfully "challenged" the target library code by examing whether each execution path (or line of code) has been run.  For example if there is a function like this:

```C
int add5ifGreaterThan2 (int a) {
	int r;

	if (a>2)
		r = a + 5;
	else
		r = a;

	return r;
}
```

Our test program for add5ifGreaterThan2() needs to supply values of a that are both less and great than 2 so both paths of the if statement 
```C
	if (a<2)
```

are tested.

We do this with test code such as this:

```C
	//code in test program ...
	ASSERT (add5ifGreaterThan2(1) == 1)   // supplies value of 'a' that tests the if (a<2) case
	ASSERT (add5ifGreaterThan2(3) == 8)   // supplies value of 'a' that tests the if (a>2) case

```

Of course this example is very simple but it gives a general idea of how the parameters need to be chosen to make sure both sides of the if clause in the example are run by the test program.


#### More info

Here is a link to the wikipedia article for more depth on unit testing practice and history: [Unit_testing](https://en.wikipedia.org/wiki/Unit_testing).

### Frameworks
To make Unit Testing easier to automate, unit testing frameworks have been written to help test results from function calls, gather statistics about passing/failing test cases, and 

Unit testing frameworks are available in most languages and many have names like JUnit (for Java) or (PyUnit for Python etc).  In C/C++ there are many excellent frameworks available many of which are open source.  Here we'll be using the well regard googletest (an open source unit test framework).  A few other well known C++ testing frameworks are shown in the list below.  Many provide features well beyond unit testing and some work in special enviroments such as small microcontrollers or embedded systems.


* [CppUTest](http://cpputest.github.io/) - A unit test framework for C++
* [Boost C++ Unit Test Framework](http://www.boost.org/doc/libs/1_35_0/libs/test/doc/components/utf/index.html) - This is the test framework used by the popular Boost library for C++
* [Typemock](https://www.typemock.com/) - a commercial Test Package
* [Cantata](http://www.qa-systems.com/tools/cantata) - a commercial Test Package
* [Google Test](https://github.com/google/googletest) - we'll be using this here.  Google Test is a free opensource framework using special macros for asserting when code doesn't perform as expected.
* [Catch](https://github.com/philsquared/Catch) - Catch is a test framework for C


### Installing Google Test 
We'll be using Google Test (called gtest) here so first we need to install it.  

Here is the link to the project source
[Google Test](https://github.com/google/googletest)

On Ubuntu Linux you can install gtest using this command.  If you are developing on another sytem refer to the documentation link for install procedures.  Other than installing, all of the commands and test procedures we'll be using later will be the same (whether Windows / MacOS / POSIX / Linux).


```bash
sudo apt-get install libgtest-dev

sudo apt-get install cmake # install cmake

cd /usr/src/gtest

sudo cmake CMakeLists.txt

sudo make

sudo cp *.a /usr/lib

sudo mkdir /usr/local/lib/googletest

sudo ln -s /usr/lib/libgtest.a /usr/local/lib/gtest/libgtest.a

sudo ln -s /usr/lib/libgtest_main.a /usr/local/lib/gtest/libgtest_main.a

```

You can read more about the Google Test project here:
[Test Primer.md](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md)  


===========================


## Features

The lib.h / lib.c files are broken out as examples of testing an embedded library.   Most of the projects I work on are for embedded systems so I wanted a way to get a build badge for these embedded projects.  Since many of those compilers and environments are not on Linux I wanted just a simple abstraction of how the Travis build project works without all the complexities of a "real" project.


## How it works

In this demo project there is a C library (could also be C++ etc).  The library code is just a few demo functions which are in the lib.h and lib.c files.  They don't really do anything but allow for simple abstraction of what is necessary to build a larger project.

Travis-CI looks in the .travis.yml  (note that is dot travis dot yml) to see how to run the code.  In this case it first calls make which compiles lib.c and example.c in to lib.o and example.o and then links them to produce the final executable called example.out.    If you look inside the file example.c  you will see there are few hand written test cases.  They are not meant to be a complete example of how to write test cases just a simple view of how the tests will be run in general.   The main() function calls local function run_tests() which in turn calls each individual test case.   Rather than link in a larger test case environment such as cppUnit etc there is a trivial set of test functions, one for each function in the lib.c library.  If run_tests() is able to run all the tests successfully it will return to main() with a value of S_OK else it will return some failure code.  This value is then returned from the main() program in example.out on exit.

Travis-CI then runs the example.out and looks for the exit code from the main() function.   Being a Posix style of system an exit code of zero from example.out is considered passing and hence Travis-ci will then declare the build passing.  If a non zero value is returned travis will declare the build failing.  So to sum up, the primary means for travis knowing whether the test suite passes is getting the proper exit code from the test suite executable which in our case here is running example.out.

## Code Coverage
Code coverage is achieved using gcov from the gcc test suite.   The example.out test program is compiled with the flags -ftest-coverage -fprofile-arcs.  To see the code coverage run gcov:

```bash
make clean
make
./test-library.out
gcov lib.c
```

which will generate the file

```bash
lib.c.gcov
```

This can be viewed in any text editor.

Lines that appear with #### have never been run.    



### FAQ:  

Q: What's the point this repo doesn't do anything.  
A: Exactly!  Its just a simple example of the travis service for test purposes.  I was looking for a simple repo that just had this basic stuff but was having trouble finding one.  

Q: I see the badge says passing can I make fail for simple purposes?   
A: Just clone it modify a commented line in the main.c to make it fail.  Of course there are other ways to make it fail too but this is just for test purposes.  

Q: Why isn't there a proper unit test framework?  
A: I just wanted a barebones test of the integration and badge service. 


## License 

(OSI Approved BSD 2-clause)

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


