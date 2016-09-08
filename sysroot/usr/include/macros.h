#ifndef _MACROS_H_INCLUDED
#define _MACROS_H_INCLUDED

#include <sys/cdefs.h>

#define min(a, b)  ((a) < (b) ? (a) : (b))

#define set_flag(variable, flag)   ( (variable) |= (flag) )
#define check_flag(variable, flag) ( (variable) & (flag) )
#define clear_flag(variable, flag) ( (variable) &= ~(flag) )

#endif
