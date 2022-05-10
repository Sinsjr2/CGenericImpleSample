#ifndef alloca_H
#define alloca_H

#include <alloca.h>

#define IL2C_LOCAL_ALLOCATOR_INIT(varName) /* nothing */
#define IL2C_LOCAL_ALLOC(allocator, size) alloca(size)
#define IL2C_LOCAL_ALLOCATOR_FREE(allocator) /* nothing */

#endif
