#include <stddef.h>
#include <math>
#include "GenericClass_T.h"
#include "TypeInfo.h"

typedef struct {
    const TypeInfo *generic_T;
    /* struct total size */
    const size_t size;
    struct {
        const size_t base;
        const size_t value;
        const size_t integer;
    } pos;
    /* layout info */
} GenericClass_T_Layout;

typedef union AlignmentGenericClass_T {
    System_Object* __1_base;
    System_Int32 __2_integer;
    GenericClass_T_Layout layout;
}

inline size_t CalcTotalSizeGenericClass_T(const TypeInfo *generic_T) {
    return il2c_calc_field_pos(
             il2c_calc_field_pos(
               il2c_calc_field_pos(
                 il2c_calc_field_pos(
                   sizeof(System_Object*),
                   generic_T->alignment) + generic_T->size,
                 sizeof(System_Int32)) + sizeof(System_Int32),
               alignof(GenericClass_T_Layout)) + sizeof(GenericClass_T_Layout),
               max(alignof(AlignmentGenericClass_T), generic_T->alignment);
}

inline GenericClass_T_Layout CreateLayout_GenericClass_T(const TypeInfo *generic_T) {
    return {
        generic_T,
        CalcTotalSizeGenericClass_T(generic_T),
        {
            0,
            il2c_calc_field_pos(sizeof(System_Object*), generic_T->alignment),
            il2c_calc_field_pos(il2c_calc_field_pos(sizeof(System_Object*), generic_T->alignment) + generic_T->size, sizeof(System_Int32))
        }
    };
}

void GenericClass_T_ctor(const TypeInfo *generic_T, void *this) {
    void *stack0_0;
    GenericClass_T_Layout layout;

    layout = CreateLayout_GenericClass_T(generic_T);
    *GetLayoutGenericClass_T(this) = layout;

    /* IL_0000: ldarg.0 */
    stack0_0 = this;
    /* IL_0001: call instance void [System.Runtime]System.Object::.ctor() */
    System_Object__ctor((System_Object*)stack0_0);
    /* IL_0006: nop */
    /* IL_0007: ret */
}

inline const GenericClass_T_Layout *GetLayoutGenericClass_T(void *obj) {
    return (const GenericClass_T_Layout *)((uint8_t*)obj)[il2c_calc_field_pos(
               il2c_calc_field_pos(
                 il2c_calc_field_pos(
                   sizeof(System_Object*),
                   generic_T->alignment) + generic_T->size,
                 sizeof(System_Int32)) + sizeof(System_Int32),
               alignof(GenericClass_T_Layout))];
}

inline System_Object **GetGenericClass_T_base(void *obj, const GenericClass_T_Layout *layout) {
    return (System_Object*)((char*)obj)[layout->pos.base];
}

inline void **GetGenericClass_T_value(void *obj, const GenericClass_T_Layout *layout) {
    return (void*)((char*)obj)[layout->pos.value];
}

inline System_Int32 *GetGenericClass_T_integer(void *obj, const GenericClass_T_Layout *layout) {
    return (System_Int32 *)((char*)obj)[layout->pos.integer];
}


typedef struct {
    const MemberPos_GenericClass this;
    const size_t typeT;
} ExecPos_GenericClass_T_GenericReturn;


void GenericClass_T_GenericReturn(void *result, void *this) {
    // .locals init (
    //     [0] !T
    // )
    void *local_0;


    void *stack_0_0;
    void *stack_1_0;
    const GenericClass_T_Layout *layout = GetLayoutGenericClass_T(this);

    local_0 = alloca(layout->generic_T->size);
    stack_1_0 = alloca(layout->generic_T->size);

    // IL_0000: nop
    // IL_0001: ldarg.0
    stack_0_0 = this;
    // IL_0002: ldfld !0 class GenericClass`1<!T>::'value'
    memcpy(stack_1_0, GetGenericClass_T_value(this, layout), layout->generic_T->size);
    // IL_0007: stloc.0
    memcpy(local_0, stack_1_0, layout->generic_T->size);
    // IL_0008: br.s IL_000a

    // IL_000a: ldloc.0
    memcpy(stack_1_0, local_0, layout->generic_T->size);
    // IL_000b: ret
    memcpy(result, stack_1_0, layout->generic_T->size);
}

void GenericClass_T_GenericAction(void *this, void *x) {
    // .locals init (
    //     [0] !T temp,
    //     [1] string toString,
    //     [2] string str
    // )
    void *temp;
    System_String toString;
    System_String str;
    const GenericClass_T_Layout *layout = GetLayoutGenericClass_T(this);

    void *stack_0_0;
    void *stack_1_0;
    void *stack_1_1;
    System_Int32 stack2_1;

    temp = alloca(layout->generic_T->size);

    // IL_0000: nop
    // IL_0001: ldarg.0
    stack_0_0 = this;
    // IL_0002: ldfld !0 class GenericClass`1<!T>::'value'
    memcpy(stack_1_0, GetGenericClass_T_value(this, layout), layout->generic_T);
    // IL_0007: stloc.0
    memcpy(temp, stack_1_0, layout->generic_T);
    // IL_0008: ldarg.0
    stack_1_1 = this;
    // IL_0009: call instance string [System.Runtime]System.Object::ToString()
    /* TODO add base class method call */

    // IL_000e: stloc.1
    // IL_000f: ldarg.0
    stack_1_1 = this;
    // IL_0010: ldflda int32 class GenericClass`1<!T>::integer
    stack2_1 = *GetGenericClass_T_integer(this, layout);
    // IL_0015: call instance string [System.Runtime]System.Int32::ToString()
    /* TODO add tostring */
    // IL_001a: stloc.2
    // IL_001b: ldarg.0
    // IL_001c: ldarg.0
    // IL_001d: ldfld int32 class GenericClass`1<!T>::integer
    // IL_0022: ldc.i4.s 10
    // IL_0024: add
    // IL_0025: stfld int32 class GenericClass`1<!T>::integer
    // IL_002a: ldarg.0
    // IL_002b: ldarg.1
    // IL_002c: stfld !0 class GenericClass`1<!T>::'value'
    // IL_0031: ret
}

IGenericParent_T_VTABLE_DECL__ GenericClass_T_IGnericParent_VTABLE__ = {
    il2c_adjustor_offset(Il2CSandBox_Hoge, Il2CSandBox_IHoge),
    GenericClass_T_GenericReturn,
};
