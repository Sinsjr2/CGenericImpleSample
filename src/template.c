#define Name_IGeneric(T) IGeneric_##T;

typedef struct {
    size_t Begin;
    size_t Size;
} Alignment;

#define IGeneric(T) \
    struct Name_IGeneric(T) {                   \
        System_Object *base;\
    };

struct MemberPos_GenericClass {
    const Alignment value;
};

#define Name_GenericClass_GenericReturn(T) GenericClass_GenericReturn_##T

#define GenericClass_GenericReturn_EXECUTION_FRAME(T) \
    typedef struct { \
        const IL2C_EXECUTION_FRAME* pNext__; \
        const uint16_t objRefCount__; \
        const uint16_t valueCount__; \
        /* -------------------- objref */ \
        T *stack0_0__;  \
    } GenericClass_##T##_GenericReturn_EXECUTION_FRAME__;

typedef struct {
    const MemberPos_GenericClass this;
    const size_t typeT;
} ExecPos_GenericClass_T_GenericReturn;


struct Extensions_CallOtherGeneric_T_Align {
    const size_t GenecricClass_T;
    const size_t sizeT;
};

void Extensions_CallOtherGeneric_T(size_t sizeT,
                                   void* value) {
    GenericClass_T_ALIGN align = GetGenericClass_T_ALIGN(sizeT);
    void* foo = alloca(align->TotalSize);

    GenericClass_T_GenericAction(sizeT, foo, value);
}
