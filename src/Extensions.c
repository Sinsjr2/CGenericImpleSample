#include "Extensions.h"
#include "System_Int32.h"

void Extensions_GenericAction_T(IL2C_RUNTIME_TYPE generic_T, void *value) {
}

void Extensions_GenericAction_T1_T2(IL2C_RUNTIME_TYPE generic_T, IL2C_RUNTIME_TYPE generic_T2,
                                    void *a, void *b) {
}

void Extensions_GenericReturn_T(IL2C_RUNTIME_TYPE generic_T, void *result) {
    void *local_0;
    void *local_1;

    void **stack_0_0;
    void *stack_0_1;
    void *stack_1_0;
    uint32_t runtimeSize_T;

    runtimeSize_T = il2c_sizeof__(generic_T)

    local_0 = alloca(runtimeSize_T);
    local_1 = alloca(runtimeSize_T);
    stack_0_1 = alloca(runtimeSize_T);

    // IL_0001: ldloca.s 0
    stack_0_0 = &local_0;
    // IL_0003: initobj !!T
    memset(stack_0_0, 0x00, runtimeSize_T);
    // IL_0009: ldloc.0
    memcpy(stack_0_1, local_0, runtimeSize_T);
    // IL_000a: stloc.1
    memcpy(local_1, stack_0_1, runtimeSize_T);
    // IL_000b: br.s IL_000d
    // IL_000d: ldloc.1
    memcpy(stack_1_0, local_1, runtimeSize_T);
    // IL_000e: ret
    memcpy(result, stack_1_0, runtimeSize_T);
}

System_Type Extensions_GetGenericType_T(IL2C_RUNTIME_TYPE generic_T) {
    // .locals init (
    //     [0] class [System.Runtime]System.Type
    // )
    System_Type local_0;
    System_RuntimeTypeHandle stack_0_0;
    System_Type stack_0_1;
    System_Type stack_0_2;

    local_0 = NULL;

    // IL_0000: nop
    // IL_0001: ldtoken !!T
    stack_0_0 = generic_T;
    // IL_0006: call class [System.Runtime]System.Type [System.Runtime]System.Type::GetTypeFromHandle(valuetype [System.Runtime]System.RuntimeTypeHandle)
    stack_0_1 = System_Type_GetTypeFromHandle(stack_0_0);
    // IL_000b: stloc.0
    local_0 = stack_0_1;
    // IL_000c: br.s IL_000e

    // IL_000e: ldloc.0
    stack_0_2 = local_0;
    // IL_000f: ret
    return stack_0_2;
}

void Extensions_GenericPassThrough_T(IL2C_RUNTIME_TYPE generic_T, void *result, void *x) {
    // .locals init (
    //     [0] !!T
    // )
    void *local_0;
    void *stack_0;
    void *stack_1;
    uint32_t runtimeSize_T;

    runtimeSize_T = il2c_sizeof__(generic_T)

    local_0 = NULL;
    stack_0 = alloca(runtimeSize_T);

    // IL_0000: nop
    // IL_0001: ldarg.0
    memcpy(stack_0, genericArg_x, runtimeSize_T);
    // IL_0002: stloc.0
    memcpy(local_0, stack_0, runtimeSize_T);
    // IL_0003: br.s IL_0005

    // IL_0005: ldloc.0
    memcpy(stack_1, local_0, runtimeSize_T);
    // IL_0006: ret
    memcpy(result, stack_1, runtimeSize_T);
}

void Extensions_GenericPassThroughTest() {
    // .locals init (
    //     [0] int32 a
    // )
    System_Int32 a_System_Int32;
    System_Int32 stack_0_0;

    // IL_0000: nop
    // IL_0001: ldc.i4.s 10
    stack_0_0 = 10;
    // IL_0003: call !!0 Extensions::GenericPassThrough<int32>(!!0)
    Extensions_GenericPassThrough_T(il2c_typeof(System_Int32), &stack_0_0, &stack_0_0);
    // IL_0008: stloc.0
    a_System_Int32 = stack_0_0;
    // IL_0009: ret
}

void Extensions_GenericPassThroughTestObj() {
    // .locals init (
    //     [0] object a
    // )

    // IL_0000: nop
    System_Object* a_System_Object;
    System_Object* stack_0_0;

    // IL_0001: newobj instance void [System.Runtime]System.Object::.ctor()
    stack_0_0 = il2c_get_uninitialized_object(System_Object);
    System_Object__ctor(stack_0_0);
    // IL_0006: call !!0 C::GenericPassThrough<object>(!!0)
    // pass pointer of pointer
    Extensions_GenericPassThrough_T(il2c_typeof(System_Object), &stack_0_0, &stack_0_0);
    // IL_000b: stloc.0
    a_System_Object = stack_0_0;
    // IL_000c: ret
}

void Extensions_GenericSwap_T(IL2C_RUNTIME_TYPE generic_T, void **a, void **b) {
    // .locals init (
    //     [0] !!T temp
    // )
    void *temp;
    void **stack_0_0;
    void *stack_0_1;
    void **stack_1_0;
    void *stack_1_1;
    uint32_t runtimeSize_T;

    runtimeSize_T = il2c_sizeof__(generic_T)

    temp = alloca(runtimeSize_T);
    stack_0_1 = alloca(runtimeSize_T);
    stack_1_1 = alloca(runtimeSize_T);

    // IL_0000: nop
    // IL_0001: ldarg.0
    stack_0_0 = a;
    // IL_0002: ldobj !!T
    memcpy(stack_0_1, *stack_0_0, runtimeSize_T);
    // IL_0007: stloc.0
    memcpy(temp, stack_0_1, runtimeSize_T);
    // IL_0008: ldarg.0
    stack_0_0 = a;
    // IL_0009: ldarg.1
    stack_1_0 = b;
    // IL_000a: ldobj !!T
    memcpy(stack_1_1, *stack_1_0, runtimeSize_T);
    // IL_000f: stobj !!T
    memcpy(*stack_0_0, stack_1_1, runtimeSize_T);
    // IL_0014: ldarg.1
    stack_0_0 = b;
    // IL_0015: ldloc.0
    memcpy(stack_1_1, temp, runtimeSize_T);
    // IL_0016: stobj !!T
    memcpy(*stack_0_0, stack_1_1, runtimeSize_T)
    // IL_001b: ret
}

void Extensions_GenericSwapTest() {
    // .locals init (
    //     [0] int32 a,
    //     [1] int32 b,
    //     [2] string a,
    //     [3] string b
    // )
    System_Int32 a_System_Int32;
    System_Int32 b_System_Int32;
    System_String a_SystemString;
    System_String b_SystemString;

    System_Int32 stack_0_0;
    System_Int32 *stack_0_1;
    System_Int32 *stack_1_0;
    System_String stack_0_1;

    // IL_0000: nop
    // IL_0001: nop
    // IL_0002: ldc.i4.s 9
    stack_0_0 = 9;
    // IL_0004: stloc.0
    a_System_Int32 = stack_0_0;
    // IL_0005: ldc.i4.5
    stack_0_0 = 5;
    // IL_0006: stloc.1
    b_System_Int32 = stack_0_0;
    // IL_0007: ldloca.s 0
    stack_0_1 = &a_System_Int32;
    // IL_0009: ldloca.s 1
    stack_1_0 = &b_System_Int32;
    // IL_000b: call void Extensions::GenericSwap<int32>(!!0&, !!0&)
    Extensions_GenericSwap_T(&System_Int32TypeInfo, stack_0_1, stack_1_0);
    // IL_0010: nop
    // IL_0011: nop
    // IL_0012: nop
    // IL_0013: ldstr "abc"
    // IL_0018: stloc.2
    // IL_0019: ldstr "de"
    // IL_001e: stloc.3
    // IL_001f: ldloca.s 2
    // IL_0021: ldloca.s 3
    // IL_0023: call void Extensions::GenericSwap<string>(!!0&, !!0&)
    // IL_0028: nop
    // IL_0029: nop
    // IL_002a: ret

}


void Extensions_CallOtherGeneric_T(IL2C_RUNTIME_TYPE generic_T, void* result,
                                   void* value) {
    // .locals init (
    //     [0] class GenericClass`1<!!T> foo,
    //     [1] !!T x,
    //     [2] !!T
    // )
    void *foo;
    void *x;
    void *local1;

    void *stack_0_0;
    void *stack_1_0;


    // IL_0000: nop
    // IL_0001: newobj instance void class GenericClass`1<!!T>::.ctor()
    stack_0_0 = il2c_malloc(CalcTotalSizeGenericClass_T(generic_T));
    GenericClass_T_ctor(generic_T, stack_0_0);
    // IL_0006: stloc.0
    foo = stack_0_0;
    // IL_0007: ldloc.0
    stack_0_0 = foo;
    // IL_0008: ldarg.0
    memcpy(stack_1_0, value, generic_T->size);
    // IL_0009: callvirt instance void class GenericClass`1<!!T>::GenericAction(!0)
    // IL_000e: nop
    // IL_000f: ldloc.0
    // IL_0010: callvirt instance !0 class GenericClass`1<!!T>::GenericReturn()
    // IL_0015: stloc.1
    // IL_0016: ldloc.1
    // IL_0017: stloc.2
    // IL_0018: br.s IL_001a

    // IL_001a: ldloc.2
    // IL_001b: ret
    GenericClass_T_ALIGN align = GetAlign_GenericClass_T(sizeT);
    void* foo = alloca(align.TotalSize);

    GenericClass_T_GenericAction(sizeT, foo, value);

    void* x = alloca(sizeT);
    GenericClass_T_GenericReturn(sizeT, x);
    memcpy(result, x, sizeT);
}
