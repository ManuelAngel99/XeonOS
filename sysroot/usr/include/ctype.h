/*
 * Author: Manuel
 * Email: Manuel_Angel99@outlook.com 
 * Created: 2016-08-30 20:02:09 
 * @Last Modified by: Manuel
 * @Last Modified time: 2016-09-01 11:37:34
 * 
 * Description: This header defines macros and functions used to test and manipule characters
 */

#ifndef CTYPE_H_INCLUDED
#define CTYPE_H_INCLUDED


#include <sys/cdefs.h>
#include <stddef.h>

#ifdef _cplusplus
	extern "C" {
#endif

#include <sys/cdefs.h>

#define __istype( c, mask) (__ctype[(unsigned)(c)]  & (mask))

#define _U		0x01 // UPPER CASE CHAR
#define _L		0x02 // LOWER CASE CHAR
#define _N 		0x04 // DIGIT (0-9)
#define _S   	0x08 // TABS(VER OR HOR) - CARRIAGE RETURN - NEWLINE
#define _P   	0x10 // PUNCTUATION CHAR
#define _C		0x20 // CONTROL CHARACTER
#define _X		0x40 // HEXADECIMAL CHAR (0-F)
#define _B		0x80 // SPACE

extern const char __ctype[];

#define isalnum( c )	__istype( (c) ,( _U | _L | _N ))
#define isalpha( c )	__istype((c), ( _U | _L ))
#define isblank( c )	__istype((c), ( _S ))
#define iscntrl( c )	__istype((c), ( _C ))
#define isdigit( c )	__istype((c), ( _N ))
#define islower( c )	__istype((c), ( _L ))
#define ispunct( c )	__istype((c), ( _P ))
#define isspace( c )	__istype((c), ( _B ))
#define isupper( c )	__istype((c), ( _U ))
#define isxdigit( c )	__istype( (c),( _X | _N ))

#define tolower(c)		(isupper(c) ? ((c) - 32) : (c))
#define toupper(c)		(islower(c) ? ((c) + 32) : (c))
#define digit_to_int(c)	((c) - 0x30)
#define int_to_digit(n) ((n) + 0x30)

int atob(size_t*, char*, int);

#ifdef _cplusplus
}
#endif

#endif