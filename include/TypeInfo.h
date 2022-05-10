#ifndef TypeInfo_H
#define TypeInfo_H

#include <stddef.h>
#include "il2c.h"

typedef struct {
    /* struct size */
    size_t size;
    /* struct alignment ex. 1, 2, 4, 8 */
    size_t alignment;
    /* generic type */
    const IL2C_RUNTIME_TYPE *typeHandle;
} TypeInfo;

#define il2c_calc_field_pos(prev_size, alignment) \
    ((prev_size) + ((prev_size) % alignment))

#define il2c_MAX(a, b)\
    ((a) > (b) ? a : b)

#define il2c_alignof(type) offsetof(struct { char a; type b; }, b)

#endif
