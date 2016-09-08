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
#include <stdbool.h>

#ifdef _cplusplus
	extern "C" {
#endif


double atof(const char*);
int atoi(const char*);
long strtol(const char *, char**, int);


char* itoa(long long, char*, int);
char* lltoa(long long, char*, int);
char* ldtoa(long double, char*, int, const bool);

__attribute__((__noreturn__)) void abort(void);				//__noreturn__ that means that the function won't ever returnn
void* malloc(unsigned int);
void free(void*);

#ifdef _cplusplus
}
#endif


#endif // STDLIB_H