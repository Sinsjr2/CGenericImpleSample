#define IL2C_TYPE_GENERIC_DEF // Like IEnumerable<T>
#define IL2C_TYPE_GENERIC_INSTANCE // Like IEnumerable<int> or IEnumerable<string>

#define IL2C_RUNTIME_TYPE_GENERIC_DEF_BEGIN(typeName, typeNameString, flags, baseType, genericParamsCount, markTarget, interfaceCount) \
    IL2C_RUNTIME_TYPE_BEGIN__(typeName, typeNameString, flags | IL2C_TYPE_GENERIC_DEF, 0, il2c_typeof(baseTypeName), il2c_vptrof(typeName), \
                              sizeof(IL2C_RUNTIME_TYPE_DECL) + markTarget * sizeof(IL2C_MARK_TARGET) + interfaceCount * sizeof(IL2C_IMPLEMENTED_INTERFACE), \
                              genericParamsCount, markTarget, interfaceCount)

const uintptr_t typeName##_RUNTIME_TYPE__[] = { \
    (uintptr_t)(typeNameString), \
    flags, \
    0x00, \
    (uintptr_t)baseType, \
    (uintptr_t)vptr0, \
    (uintptr_t)markTarget, \
    interfaceCount,

struct IL2C_RUNTIME_TYPE_DECL {
    const char* pTypeName;
    const uintptr_t flags;
    // if IL2C_TYPE_GENERIC_DEFINE : 0
    // if IL2C_TYPE_GENERIC_INSTANCE : return field size
    const uintptr_t bodySize;       // uint32_t
    const IL2C_RUNTIME_TYPE baseType;
    const void* vptr0;
    const uintptr_t genericParamsOffset; // offset from head of IL2C_RUNTIME_TYPE_DECL.
    const uintptr_t genericParamsCount; // count of element length
    const uintptr_t markTarget;     // mark target count / custom mark handler (only variable type)
    const uintptr_t interfaceCount;
    //IL2C_MARK_TARGET markTargets[markTarget];
    //IL2C_IMPLEMENTED_INTERFACE interfaces[interfaceCount];
    // if generic type define: all elements is NULL.
    //IL2C_RUNTIME_TYPE genericParams[genericParamsCount];
};

struct MyGenericClass_DECL {
    GenericClass_T_Layout layout;
    IL2C_RUNTIME_TYPE_DECL runtimeType;
};
