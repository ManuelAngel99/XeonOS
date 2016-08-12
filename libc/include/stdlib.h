/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 15:26:37
* 
* File: stdlib.h
* Description: Common language utilities
*/

#ifndef STDLIB_H
#define STDLIB_H

#include <sys/cdefs.h>

#ifdef _cplusplus
	extern "C" {
#endif

__attribute__((__noreturn__))
void abort(void);				//__noreturn__ that means that the function won't ever returnn
char* itoa(int, char*, int);

#ifdef _cplusplus
}
#endif


#endif // STDLIB_H