#include "GenericStruct_T.h"

#include "local_stack_allocator.h"


static void VirtGenericStruct_T_GenericReturn(void *result, void *this);

static void VirtGenericStruct_T_GenericReturn(void *result, void *this) {
    GenericStruct_T_GenericReturn(il2c_get_header__(this)->type, result, il2c_unsafe_unbox__(this));
}

void GenericStruct_T_GenericReturn(IL2C_RUNTIME_TYPE generic_T,
                                   void *result, void *this) {
    // .locals init (
    //     [0] !T,
    //     [1] !T
    // )
    void *local_0;
    void *local_1;

    void **stack_0_0;
    void *stack_0_1;
    uint32_t runtimeSize_T;

    runtimeSize_T = il2c_sizeof__(generic_T)


    IL2C_LOCAL_ALLOCATOR_INIT(allocator)

    local_0 = IL2C_LOCAL_ALLOC(allocator, runtimeSize_T);
    local_1 = IL2C_LOCAL_ALLOC(allocator, runtimeSize_T);

    stack_0_1 = IL2C_LOCAL_ALLOC(allocator, runtimeSize_T);

    // IL_0000: nop
    // IL_0001: ldloca.s 0
    stack_0_0 = &local_0;
    // IL_0003: initobj !T
    memset(*stack_0_0, 0x00, runtimeSize_T);
    // IL_0009: ldloc.0
    memcpy(stack_0_1, local_0, runtimeSize_T);
    // IL_000a: stloc.1
    memcpy(local_1, stack_0_1, runtimeSize_T);
    // IL_000b: br.s IL_000d

    // IL_000d: ldloc.1
    memcpy(stack_0_1, local_1, runtimeSize_T);
    // IL_000e: ret
    memcpy(result, stack_0_1, runtimeSize_T);

    IL2C_LOCAL_ALLOCATOR_FREE(allocator);
}
