/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-24 11:31:48
* 
* File: assert.h
* Description: Standard C library assert
*/

#ifndef _ASSERTY_H_INCLUDED
#define _ASSERTY_H_INCLUDED


#include <sys/cdefs.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _cplusplus
	extern "C" {
#endif


#ifndef NDEBUG
	#define assert(expression) if (!(expression))\
	{ printf("ASSERTION (%s) FAILED AT FILE %s, LINE NUMBER-> %d", #expression, __FILE__, __LINE__); abort();}
#else
#	define assert(expr)

#endif

#ifdef _cplusplus
}
#endif

#endif
