This is sample programs for implementaition of il2c generics.

Each c file is translated template.cs manually.
These codes are to show ideas, and unfinished, so it can't compile.

It's possible to implement "generic virtual method" of interface by the following.
(ex limit: il2cpp https://docs.unity3d.com/2018.4/Documentation/Manual/ScriptingRestrictions.html )
Also, this method is probably smaller program size then C++ template.
But, perhaps this is low performance because of memcpy.

# Generic example
template.cs
``` cs
static class Extensions {
    // .locals init (
    //     [0] !!T
    // )

    // IL_0000: nop
    // IL_0001: ldarg.0
    // IL_0002: stloc.0
    // IL_0003: br.s IL_0005

    // IL_0005: ldloc.0
    // IL_0006: ret
    public static T GenericPassThrough<T>(T x) {
        return x;
    }

    // .locals init (
    //     [0] int32 a
    // )

    // IL_0000: nop
    // IL_0001: ldc.i4.s 10
    // IL_0003: call !!0 Extensions::GenericPassThrough<int32>(!!0)
    // IL_0008: stloc.0
    // IL_0009: ret
    public static void GenericPassThroughTest() {
        var a = GenericPassThrough(10);
    }
}
```

src/Extensions.c
``` c
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
```

include/TypeInfo.h
``` C
typedef struct {
    /* struct size */
    size_t size;
    /* struct alignment ex. 1, 2, 4, 8 */
    size_t alignment;
    /* generic type */
    const IL2C_RUNTIME_TYPE *typeHandle;
} TypeInfo;
```

Implemention policy is following.
- Convert Generic Type T/List\<T\> to void*
- TypeInfo is runtime infomation for generic type.
- Use memcpy() to asign instance.
- Allocate local heap for generic instance. (ex alloca())
- Return a value with out parameter because can't return local heap pointer.

# Local heap allocator
Some C compilers does not support VLA or alloca().
(ex: Renesus cc-rx.)

so, I suggest 3 methods.
1. Use alloca() function (local_stack_allocator/alloca_allocator.h) 
   I think this is fastest of the theree.
1. Use "TLS: thread Local Strage". and Imitate stack.  (local_stack_allocator/local_storage_allocator.h)
   tls windows: https://docs.microsoft.com/ja-jp/cpp/parallel/thread-local-storage-tls?view=msvc-170
   tls freertos: https://www.freertos.org/thread-local-storage-pointers.html
1. Use malloc and free. (local_stack_allocator/malloc_allocator.h)
    Use TLS and malloc/free.
