/*
* Author: manuel
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 13:43:33
* 
* File: string.h
* Description: Defines the c library string utilities
*/

#ifndef STRING_H
#define STRING_H

#include <sys/cdefs.h>
#include <stddef.h>

#ifdef _cplusplus
	extern "C" {
#endif

int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);
size_t strlen(const char*);
char* reverse(char*, const size_t);

#ifdef _cplusplus
}
#endif

#endif // STRING_H