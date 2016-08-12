/*
* Author: Manuel Ángel Suárez Álvarez
* E-mail Manuel_Angel99@outlook.com
* Created: 2016-08-11 21:48:03
* 
* File: math.h
* Description: Defines some mathematical utilities
*/

#ifndef _ADDI_MATH_H
#define _ADDI_MATH_H

#include <sys/cdefs.h>
#include <stddef.h>

#ifdef _cplusplus
	extern "C" {
#endif

double floor(double);
double ceil(double);
double round(double);
double pow(double, double);
double precise_round(double, size_t);
double modf(double, double*);

#ifdef _cplusplus
}
#endif

#endif // _MATH_H
