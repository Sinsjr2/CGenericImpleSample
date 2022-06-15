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
```

# Generic Member Sample

target c# code.
template.cs

``` csharp
class GenericClass<T> {
    T value;
    int integer;

    public void GenericAction(T x) {
        T temp = value;
        string toString = base.ToString();
        var str = integer.ToString();
        integer += 10;
        value = x;
    }
}
```
The `il2c_calc_field_pos` is used to dynamically calculate the offset of the "class" containing the Generic field.

Some CPUs may not work correctly when reading variables with incorrect alignment.
For example, if int32_t is not placed in 4-byte alignment, an exception will be thrown on Arm CPUs, but on
On x86-based CPUs, it can be read correctly only because the access speed will be slower.
Therefore, the `alignment` can be adjusted to any alignment.

TypeInfo.h
``` c
#define il2c_calc_field_pos(prev_size, alignment) \
    ((prev_size) + ((prev_size) % alignment))
```

The `GenericClass_T_Layout` is used to get the offset of the `GenericClass<T>` field.
Note that if the field of `GenericClass<T>` does not contain T, the dynamic calculation of the offset is not necessary and
It may be converted to the following structure.

``` c
typedef struct {
    System_Object* base;
    System_Int32 integer;
} GenericClass_T;
```
I don't have a detailed implementation of the function "GetLayoutGenericClass_T", but
get `IL2C_RUNTIME_TYPE` from variable `this`(refobj), and get a dictionary with `IL2C_RUNTIME_TYPE` as key
(expressed in c#: `Dictionary<IL2C_RUNTIME_TYPE, GenericClass_T_Layout>`) to get GenericClass_T_Layout from it.

On the other hand, if the variable `this` is a struct, `IL2C_RUNTIME_TYPE` is passed directly to the function argument, so it is got from the global variable `runtimeDictionary_XXXX` using that as the key.

The reason why `GenericClass_T_Layout` is needed is that `Generic<T>` contains `T value` inside, so the offset of the variable `integer` changes depending on the size of `T`.
This is because the offset needs to be calculated dynamically.

Example of how define cannot compute layout dynamically

``` c++
# define DEFGenericClass(T)¥
struct GenericClass_##T { ¥
    T value; ¥
    int integeer; ¥
  };
void Do() {
    IL2C_RUNTIME_TYPE generic_T;
    DEFGenericClass(generic_T-> /* how can I write ?*/);
}
```

The purpose of creating a `GenericClass_T_Layout` is also to increase readability, since member variables are clearly visible.

GenericClass_T.c
``` c
typedef struct {
    const size_t base;
    const size_t value;
    const size_t integer;
} GenericClass_T_Layout;

static il2c_Dictionary runtimeDictionary_GenericClass_T;

GenericClass_T_Layout CreateLayout_GenericClass_T(IL2C_RUNTIME_TYPE generic_T) {
    return {
        0,
        il2c_calc_field_pos(sizeof(System_Object*), sizeof(size_t) * 2),
        il2c_calc_field_pos(il2c_calc_field_pos(sizeof(System_Object*), sizeof(size_t) * 2) + generic_T->size, sizeof(System_Int32))
    };
}

inline System_Int32 *GetGenericClass_T_integer(void *obj, const GenericClass_T_Layout *layout) {
    return (System_Int32 *)((char*)obj)[layout->integer];
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
```

# Generic static variable
Target C# code.
template.cs

``` csharp
public class GenericClass<T> {
    public static string Str;
}

public class MainClass {
    public void GetGenericStaticVar() {
        var str = GenericClass<string>.Str;
        var integer = GenericClass<int>.Str;
    }
}
```

`GenericClass_T__TryIntialize__` initializes static fields, when `runtimeDictionary_GenericClass_T` doesn't have key.
Also, dictionary operations need to be thread-safe, but this is not consideration now.

``` c
typedef struct GenericClass_T_STATIC_FIELDS_DECL__ {
    SystemString* Str;
} GenericClass_T_STATIC_FIELDS;

typedef struct GenericClass_T_RUNTIME_TYPE_DECL__ {
    IL2C_RUNTIME_TYPE_DECL runtimeType;
    uintptr_t interfaces[2][1];
    IL2C_RUNTIME_TYPE_DECL genericParams[1];
} GenericClass_T_RUNTIME_TYPE;

typedef struct GenericClass_T_GENERIC_CONTEXT_DECL {
    GenericClass_T_RUNTIME_TYPE runtimeType;
    GenericClass_T_Layout layout;
    GenericClass_T_STATIC_FIELDS fields
} GenericClass_T_GENERIC_CONTEXT;

// Dictionary<IL2C_RUNTIME_TYPE, GenericClass_T_GENERIC_CONTEXT>
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
```
`context_GenericClass_T` is used to prevent multiple dictionary lookups from `runtimeDictionary_GenericClass_T`.
In the example below, `T` is `string` and `int`, but there are cases where `T` is `GenericClass<int>`.
In that case, you need to get the `Int32` type, then get the `GenericClass<int>` and twice from the dictionary.
So I would like to be able to look up the dictionary with the Generic part and the T parameter as one key.

~~~ c
IL2C_RUNTIME_TYPE key[] = { il2c_typeof(GenericClass_T), il2c_typeof(System_Int32) };
GenericClass_T_Str_HANDLER__(key);
~~~

MainClass.c
``` c
void MainClass_GetGenericStaticVar() {
    System_String* str;
    System_String* integer;
    System_String* stack_0_0;

    GenericClass_T_GENERIC_CONTEXT* context_GenericClass_T = NULL;
    // // Method begins at RVA 0x220c
    // // Code size 14 (0xe)
    // .maxstack 1
    // .locals init (
    //     [0] string str,
    //     [1] string integer
    // )

    // IL_0000: nop
    // IL_0001: ldsfld string class GenericClass`1<string>::Str
    stack_0_0 = GenericClass_T_Str_HANDLER__(il2c_typeof(System_String), &context_GenericClass_T);
    // IL_0006: stloc.0
    str = stack_0_0;
    // IL_0007: ldsfld string class GenericClass`1<int32>::Str
    stack_0_0 = GenericClass_T_Str_HANDLER__(il2c_typeof(System_Int32), &context_GenericClass_T);
    // IL_000c: stloc.1
    integer = stack_0_0;
    // IL_000d: ret
}
```

# Generic virtual call

Virtual function calls are implemented different way with objref and value.

refobj is not particularly considered since `IL2C_RUNTIME_TYPE_DECL` can be obtained from `this`.
"value" can be obtained from `this` since it is always `ValueType` when a virtual call is made.
However, `IL2C_RUNTIME_TYPE_DECL` cannot be obtained from `this` when it becomes a normal function call.
Therefore, the function for virtual call and the function for normal call are separated.

stc/GenericStruct_T.c
``` c
static void VirtGenericStruct_T_GenericReturn(void *result, void *this) {
    GenericStruct_T_GenericReturn(il2c_get_header__(this)->type, result, il2c_unsafe_unbox__(this));
}

void GenericStruct_T_GenericReturn(IL2C_RUNTIME_TYPE generic_T,
                                   void *result, void *this) {
}
```

# Implementation policy
Implementation policy is following.
- Convert Generic Type T/List\<T\> to void*
  case T is value type: copy member filelds to new instance
  case T is object reference type: copy pointer to new local variable with memcpy.
     so, this is **not **`Object.MemberwiseClone` https://docs.microsoft.com/ja-jp/dotnet/api/system.object.memberwiseclone?view=net-6.0
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
