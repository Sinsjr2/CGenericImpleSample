#ifndef IGenericParent_T_H
#define IGenericParent_T_T

typedef const struct IGenericParent_T_VTABLE_DECL___ IGenericParent_T_VTABLE_DECL__;


struct IGenericParent_T_VTABLE_DECL___
{
    intptr_t offset__; // Adjustor offset
    void (*T GenericReturn(void* result, void* this__);
};

struct IGenericParent_T {
    IGenericParent_T_VTABLE_DECL___* vptr0__;
};

IL2C_DECLARE_RUNTIME_TYPE(IGenericParent_T);

#endif
