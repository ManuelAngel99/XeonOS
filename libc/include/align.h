#ifndef _ALIGN_H_INCLUDED
#define _ALIGN_H_INCLUDED

/*
 * Note:
 * Adress can be a memory adress or a size
 * Alignment must be a power of two!
 */

#include <sys/cdefs.h>

#define ALIGN_DOWN(adress, alignment)  ((adress) & ~((alignment) - 1))
#define ALIGN_UP(adress, alignment)  (((adress) + ((alignment) - 1)) & ~((alignment) - 1))

#define IS_ALIGNED(adress, alignment) (ALIGN_UP(addess,alignment) == adress)

#endif
