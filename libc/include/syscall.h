/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 14:00:08
* 
* File: stdio.h
* Description: Defines the basic input and output functions
*/
#ifndef _SYSCALL_H_INCLUDED
#define _SYSCALL_H_INCLUDED


#include <sys/cdefs.h>
#include <stddef.h>
#include <stdint.h>

size_t read(int, void*, size_t);

#ifdef _cplusplus
}
#endif

#endif