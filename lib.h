/*

  @lib.h - header file for  travis-ci example for github

  @copy Copyright (C) <2017>  <M. A. Chatterjee>
  @author M A Chatterjee <deftio [at] deftio [dot] com>
  @version 1.0 M. A. Chatterjee
 
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

#ifndef __lib_h__
#define __lib_h__


#ifdef __cplusplus
extern "C"
{
#endif

/** The "libary" begins here  */

/* integer bitwise AND */
int  op_and 	(int x, int y);

/* integer bitwise OR */
int  op_or 		(int x, int y);

/* integer bitwise XOR */
int  op_xor 	(int a, int b);

/* integer bitwise XNOR */
int  op_xnor 	(int a, int b);

/* integer add 			 */
int  op_add 	(int x, int y);

/* integer sub 			 */
int  op_sub 	(int x, int y);

/* integer mul 			 */
int  op_mul 	(int x, int y);


#ifdef __cplusplus
}
#endif

#endif /* __lib_h__ */

