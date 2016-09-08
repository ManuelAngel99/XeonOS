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

void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
char* strcpy(char*, const char*);
char* strncpy(char*, const char*, size_t);

char* strcat(char*, const char*);
char* strncat(char*, const char*, size_t);

int memcmp(const void*, const void*, size_t);
int strcmp(const char*, const char*);
int strncmp(const char*, const char*, size_t);
size_t strxfrm ( char * __restrict, const char * __restrict, size_t);

void*  memchr(const void*, int, size_t);
char*  strchr(const char*, int);
char * strrchr(char*, int);
size_t strcspn(const char*, const char*);
size_t strspn(const char *, const char*);
char*  strpbrk(const char*, const char *);
char*  strstr(char*, const char*);
char*  strtok(char*, const char*);

void*  memset(void*, int, size_t);
size_t strlen(const char*);

char*  reverse(char*, const size_t);
void string_to_upper(char* string);
char* insert_char(char*, const size_t, const char, const int);

#ifdef _cplusplus
}
#endif

#endif // STRING_H