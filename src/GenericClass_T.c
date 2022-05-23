#include <stddef.h>
#include <math>
#include "GenericClass_T.h"
#include "TypeInfo.h"

typedef struct {
    const size_t base;
    const size_t value;
    const size_t integer;
} GenericClass_T_Layout;

typedef struct GenericClass_T_STATIC_FIELDS_DECL__ {
    SystemString* Str;
} GenericClass_T_STATIC_FIELDS;

typedef struct GenericClass_T_RUNTIME_TYPE_DECL__ {
    IL2C_RUNTIME_TYPE_DECL runtimeType;
    uintptr_t interfaces[2][1];
} GenericClass_T_RUNTIME_TYPE;

typedef struct GenericClass_T_GENERIC_CONTEXT_DECL {
    GenericClass_T_RUNTIME_TYPE runtimeType;
    GenericClass_T_Layout layout;
    GenericClass_T_STATIC_FIELDS fields
} GenericClass_T_GENERIC_CONTEXT;

typedef union AlignmentGenericClass_T {
    System_Object* __1_base;
    System_Int32 __2_integer;
    GenericClass_T_Layout layout;
};

GenericClass_T_GENERIC_CONTEXT* CreateGenericClass_T_GENERIC_CONTEXT(IL2C_RUNTIME_TYPE generic_T);

inline size_t CalcTotalSizeGenericClass_T(IL2C_RUNTIME_TYPE generic_T) {
    return il2c_calc_field_pos(
             il2c_calc_field_pos(
               il2c_calc_field_pos(
                 il2c_calc_field_pos(
                   sizeof(System_Object*),
                   sizeof(size_t) * 2) + il2c_sizeof__(generic_T),
                 sizeof(System_Int32)) + sizeof(System_Int32),
               alignof(GenericClass_T_Layout)) + sizeof(GenericClass_T_Layout),
               max(alignof(AlignmentGenericClass_T), sizeof(size_t) * 2));
}

inline GenericClass_T_Layout CreateLayout_GenericClass_T(IL2C_RUNTIME_TYPE generic_T) {
    return {
        0,
        il2c_calc_field_pos(sizeof(System_Object*), sizeof(size_t) * 2),
        il2c_calc_field_pos(il2c_calc_field_pos(sizeof(System_Object*), sizeof(size_t) * 2) + generic_T->size, sizeof(System_Int32))
    };
}

typedef struct GenericClass_T_RUNTIME_EXECUTION_STATIC_FIELDS_DECL__ /* IL2C_STATIC_FIELDS */
{
    IL2C_STATIC_FIELDS* pNext__;
    const uint16_t objRefCount__;
    const uint16_t valueCount__;
    //-------------------- objref
    Il2CSandBox_Hoge* hogehoge;
} GenericClass_T_RUNTIME_EXECUTION_STATIC_FIELDS;


static il2c_Dictionary runtimeDictionary_GenericClass_T;

static GenericClass_T_GENERIC_CONTEXT* GenericClass_T__TryIntialize__(IL2C_RUNTIME_TYPE generic_T) {
    GenericClass_T_GENERIC_CONTEXT** staticFields = (GenericClass_T_GENERIC_CONTEXT**)il2c_dic_getValue(&runtimeDictionary_GenericClass_T, generic_T);
    if (staticFields != NULL) {
        return *staticFields;
    }
    GenericClass_T_GENERIC_CONTEXT* newField = CreateGenericClass_T_GENERIC_CONTEXT(generic_T);
    // TODO try catch
    GenericClass_T__cctor(newField->fields);

    il2c_dic_set(&runtimeDictionary_GenericClass_, generic_T, newField);
    return newField;
}

SystemString** GenericClass_T_Str_HANDLER__(IL2C_RUNTIME_TYPE generic_T, GenericClass_T_GENERIC_CONTEXT** genericContext)
{
    if (*genericContext == NULL) {
        *genericContext = GenericClass_T__TryIntialize__(generic_T);
    }
    return &(*genericContext)->fields->Str;
}

void GenericClass_T_ctor(IL2C_RUNTIME_TYPE generic_T, void *this) {
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

inline const GenericClass_T_Layout* GetLayoutGenericClass_T(void *obj) {
    return (const GenericClass_T_Layout *)((uint8_t*)obj)[il2c_calc_field_pos(
               il2c_calc_field_pos(
                 il2c_calc_field_pos(
                   sizeof(System_Object*),
                   generic_T->alignment) + generic_T->size,
                 sizeof(System_Int32)) + sizeof(System_Int32),
               alignof(GenericClass_T_Layout))];
}

inline System_Object **GetGenericClass_T_base(void *obj, const GenericClass_T_Layout *layout) {
    return (System_Object*)((char*)obj)[layout->base];
}

inline void **GetGenericClass_T_value(void *obj, const GenericClass_T_Layout *layout) {
    return (void*)((char*)obj)[layout->value];
}

inline System_Int32 *GetGenericClass_T_integer(void *obj, const GenericClass_T_Layout *layout) {
    return (System_Int32 *)((char*)obj)[layout->integer];
}

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

static GenericClass_T_GENERIC_CONTEXT* CreateGenericClass_T_GENERIC_CONTEXT(IL2C_RUNTIME_TYPE generic_T) {
    GenericClass_T_GENERIC_CONTEXT* info;
    uintptr_t totalSize = CalcTotalSizeGenericClass_T(generic_T);
    IL2C_RUNTIME_TYPE_BEGIN(RuntimeInfo, "GenericClass<T>", IL2C_TYPE_REFERENCE, totalSize, System_Object, 0, 1)
        IL2C_RUNTIME_TYPE_INTERFACE(Il2CSandBox_Hoge, Il2CSandBox_IHoge)
    IL2C_RUNTIME_TYPE_END();

    info = (GenericClass_T_GENERIC_CONTEXT*)il2c_malloc(sizeof(GenericClass_T_GENERIC_CONTEXT));

    info->layout = CreateLayout_GenericClass_T(generic_T);
    info->runtimeType = *il2c_typeof(RuntimeInfo);
    info->fields = {};

    return info;
}
