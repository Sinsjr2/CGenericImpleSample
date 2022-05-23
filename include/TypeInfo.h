#ifndef TypeInfo_H
#define TypeInfo_H

#include <stddef.h>
#include "il2c.h"

typedef struct {
    /* struct size */
    size_t size;
    uint8_t isValueType;
} TypeInfo;

#define il2c_calc_field_pos(prev_size, alignment) \
    ((prev_size) + ((prev_size) % alignment))

inline void* il2c_get_generic_body(IL2C_RUNTIME_TYPE runtimeType, /* System_Object* */ void *obj) {
    return runtimeType->flags & IL2C_TYPE_VALUE ?
        il2c_unsafe_unbox__(obj) :
        obj;
}

#define il2c_runtimetype(typeName) \
    (typeName##_RUNTIME_TYPE__)

#define il2c_MAX(a, b)\
    ((a) > (b) ? a : b)

#define il2c_alignof(type) offsetof(struct { char a; type b; }, b)

inline size_t il2c_adjustAlignment(size_t offset, size_t alignment) {
    // case of power of 2.
    if ((alignment & 0x1) == 0) {
        return (offset + (alignment-1)) & -alignment;
    }
    return offset + ((alignment - (offset % alignment)) % alignment);
}
#endif
