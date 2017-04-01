[![Build Status](https://travis-ci.org/deftio/travis-ci-cpp-example.svg?branch=master)](https://travis-ci.org/deftio/travis-ci-cpp-example)
[![Coverage Status](https://coveralls.io/repos/github/deftio/travis-ci-cpp-example/badge.svg?branch=master)](https://coveralls.io/github/deftio/travis-ci-cpp-example?branch=master)
[![License](https://img.shields.io/badge/License-BSD%202--Clause-orange.svg)](https://opensource.org/licenses/BSD-2-Clause)

# Travis-CI Simple Stand Alone Example for C/C++

copyright (C) <2016>  <M. A. Chatterjee>  <deftio [at] deftio [dot] com>
version 1.0 M. A. Chatterjee



## About 

Travis-CI is a test coverage service common for open source projects.  This repo is just a stand alone example of how to call it for small C/C++ libraries


## Features

The lib.h / lib.c files are broken out as examples of testing an embedded library.   Most of the projects I work on are for embedded systems so I wanted a way to get a build badge for these embedded projects.  Since many of those compilers and environments are not on Linux I wanted just a simple abstraction of how the Travis build project works without all the complexities of a "real" project.



## How it works

In this demo project there is a C library (could also be C++ etc).  The library code is just a few demo functions which are in the lib.h and lib.c files.  They don't really do anything but allow for simple abstraction of what is necessary to build a larger project.

Travis-CI looks in the .travis.yml  (note that is dot travis dot yml) to see how to run the code.  In this case it first calls make which compiles lib.c and example.c in to lib.o and example.o and then links them to produce the final executable called example.out.    If you look inside the file example.c  you will see there are few hand written test cases.  They are not meant to be a complete example of how to write test cases just a simple view of how the tests will be run in general.   The main() function calls local function run_tests() which in turn calls each individual test case.   Rather than link in a larger test case environment such as cppUnit etc there is a trivial set of test functions, one for each function in the lib.c library.  If run_tests() is able to run all the tests successfully it will return to main() with a value of S_OK else it will return some failure code.  This value is then returned from the main() program in example.out on exit.

Travis-CI then runs the example.out and looks for the exit code from the main() function.   Being a Posix style of system an exit code of zero from example.out is considered passing and hence Travis-ci will then declare the build passing.  If a non zero value is returned travis will declare the build failing.  So to sum up, the primary means for travis knowing whether the test suite passes is getting the proper exit code from the test suite executable which in our case here is running example.out.

## Code Coverage
Code coverage is achieved using gcov from the gcc test suite.   The example.out test program is compiled with the flags -ftest-coverage -fprofile-arcs.  To see the code coverage run gcov:

```
make clean
make
./test-library.out
gcov lib.c
```

which will generate the file

```
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


