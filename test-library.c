/*

  @main.c - simple test file example file for travis-ci example library

  @copy Copyright (C) <2012>  <M. A. Chatterjee>
  @author M A Chatterjee <deftio [at] deftio [dot] com>
 
  This file contains header defintions for travis-ci code testing example.

  @license: 
	Copyright (c) 2011-2016, M. A. Chatterjee <deftio at deftio dot com>
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

 */

#include <stdio.h>
#include "lib.h"

#define S_OK (0)
#define E_FAIL (-1)


/* ************************************************
	simple test cases for the library functions 
   ************************************************
*/


/*   test cases for op_and() function  */
int test_and() {
	
	if (op_and(3,4) != (3&4))
		return E_FAIL;

	if (op_and(2,7) != (2&7))
		return E_FAIL;

	// un comment me to make this fail!
	//if ((f_ib_and(2,7) == (2&7))
	//	return E_FAIL;)

	return S_OK;
}

/*   test cases for op_or() function  */
int test_or() {
	if (op_or(3,4) != (3|4)) 
		return E_FAIL;
	
	return S_OK;
}

/*   test cases for op_xor() function  */
int test_xor() {
	if (op_xor(3,4) != ((3^4))) 
		return E_FAIL;
	return S_OK;
}


/*   test cases for op_xnor() function  */
int test_xnor() {
	if (op_xnor(3,4) != (~(3^4))) 
		return E_FAIL;
	return S_OK;
}

/*   test cases for op_add() function  */
int test_add() {
	if (op_add(3,4) != (3+4)) 
		return E_FAIL;
	return S_OK;
}


/*   test cases for op_sub() function  */
int test_sub() {
	if (op_sub(3,4) != (3-4)) 
		return E_FAIL;
	return S_OK;
}


/*   test cases for op_mul() function  */
int test_mul() {
	if (op_mul(3,4) != (3*4)) 
		return E_FAIL;
	return S_OK;
}

/* 	************************************************
	this is a simple test suite.  
	normally you would run cppUnit or some other 
	more general purpose test framework.
*/
int run_tests() {
	if (E_FAIL == test_and()) {
		printf("failed test_and()\n");
		return E_FAIL;
	}

	if (E_FAIL == test_or()) {
		printf("failed test_or()\n");
		return E_FAIL;
	}
	
	if (E_FAIL == test_xor()){
		printf("failed test_xor()\n");
		return E_FAIL;
	}

	if (E_FAIL == test_xnor()){
			printf("failed test_xnor()\n");
			return E_FAIL;
		}

	if (E_FAIL == test_add()){
			printf("failed test_add()\n");
			return E_FAIL;
		}

	if (E_FAIL == test_sub()){
			printf("failed test_sub()\n");
			return E_FAIL;
		}


	if (E_FAIL == test_mul()){
			printf("failed test_mul()\n");
			return E_FAIL;
		}

	return S_OK;
}


/* 
	This main function only runs all the test code.
    If successful it returns S_OK which is equal to the numerical value of 0.
 	Any other value is considered a failure.
 	
 */
int main()
{
	int result;
	
	printf("Running Example tests .. \n");
	result = run_tests();

	if (result == S_OK) 
		printf ("tests passed.\n");
	else
		printf ("tests failed.\n");

    return result;  /* remember the value 0 is considered passing in a travis-ci sense */

}