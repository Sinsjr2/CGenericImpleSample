#include "GenericStruct_T.h"

#include "local_stack_allocator.h"

typedef struct {
    const TypeInfo *generic_T;
} GenericStructGenericTypes;

typedef union {
    GenericStructGenericTypes __1;
} AlignmentGenericStruct_T;

static void VirtGenericStruct_T_GenericReturn(void *result, void *this);

inline size_t CalcAlignmentGenericStruct_T(const TypeInfo *generic_T) {
    return 1;
}


/* ValueType は含まない */
inline size_t CalcTotalSizeGenericStruct_T_Boxed(const TypeInfo *generic_T) {
    return il2c_calc_field_pos(sizeof(GenericStructGenericTypes), il2c_MAX(CalcAlignmentGenericStruct_T(generic_T), il2c_alignof(AlignmentGenericStruct_T)));
}

inline void *GetGenericStruct_T_Boxed_body(void *obj) {
    return NULL;
}

static void VirtGenericStruct_T_GenericReturn(void *result, void *this) {
    GenericStructGenericTypes* generic_types = il2c_unsafe_unbox__(this, GenericStructGenericTypes);
    GenericStruct_T_GenericReturn(generic_types->generic_T, result, GetGenericStruct_T_Boxed_body(generic_types));
}

void GenericStruct_T_GenericReturn(const TypeInfo *generic_T,
                                   void *result, void *this) {
    // .locals init (
    //     [0] !T,
    //     [1] !T
    // )
    void *local_0;
    void *local_1;

    void **stack_0_0;
    void *stack_0_1;

    IL2C_LOCAL_ALLOCATOR_INIT(allocator)

    local_0 = IL2C_LOCAL_ALLOC(allocator, generic_T->size);
    local_1 = IL2C_LOCAL_ALLOC(allocator, generic_T->size);

    stack_0_1 = IL2C_LOCAL_ALLOC(allocator, generic_T->size);

    // IL_0000: nop
    // IL_0001: ldloca.s 0
    stack_0_0 = &local_0;
    // IL_0003: initobj !T
    memset(*stack_0_0, 0x00, generic_T->size);
    // IL_0009: ldloc.0
    memcpy(stack_0_1, local_0, generic_T->size);
    // IL_000a: stloc.1
    memcpy(local_1, stack_0_1, generic_T->size);
    // IL_000b: br.s IL_000d

    // IL_000d: ldloc.1
    memcpy(stack_0_1, local_1, generic_T->size);
    // IL_000e: ret
    memcpy(result, stack_0_1, generic_T->size);

    IL2C_LOCAL_ALLOCATOR_FREE(allocator);
}
