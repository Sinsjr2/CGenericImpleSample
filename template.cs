public interface IGenericParent<out T> {
    T GenericReturn();
}

public interface IGeneric<T>: IGenericParent<T> {
    void GenericAction(T x);
}

class GenericClass<T> : IGeneric<T> {
    T value;
    int integer;

    // .locals init (
    //     [0] !T
    // )

    // IL_0000: nop
    // IL_0001: ldarg.0
    // IL_0002: ldfld !0 class GenericClass`1<!T>::'value'
    // IL_0007: stloc.0
    // IL_0008: br.s IL_000a

    // IL_000a: ldloc.0
    // IL_000b: ret
    public T GenericReturn() {
        return value;
    }

    // .locals init (
    //     [0] !T temp,
    //     [1] string toString,
    //     [2] string str
    // )

    // IL_0000: nop
    // IL_0001: ldarg.0
    // IL_0002: ldfld !0 class GenericClass`1<!T>::'value'
    // IL_0007: stloc.0
    // IL_0008: ldarg.0
    // IL_0009: call instance string [System.Runtime]System.Object::ToString()
    // IL_000e: stloc.1
    // IL_000f: ldarg.0
    // IL_0010: ldflda int32 class GenericClass`1<!T>::integer
    // IL_0015: call instance string [System.Runtime]System.Int32::ToString()
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
    public void GenericAction(T x) {
        T temp = value;
        string toString = base.ToString();
        var str = integer.ToString();
        integer += 10;
        value = x;
    }
}

public struct GenericStruct<T> : IGenericParent<T> {
    // .locals init (
    //     [0] !T,
    //     [1] !T
    // )

    // IL_0000: nop
    // IL_0001: ldloca.s 0
    // IL_0003: initobj !T
    // IL_0009: ldloc.0
    // IL_000a: stloc.1
    // IL_000b: br.s IL_000d

    // IL_000d: ldloc.1
    // IL_000e: ret
    public T GenericReturn() {
        return default;
    }
}

static class Extensions {

    // IL_0000: nop
    // IL_0001: ret
    public static void GenericAction<T>(T x) { }

    public static void GenericAction<T1, T2>(T1 a, T2 b) { }

    // [0] !!T,
    // [1] !!T

    // IL_0000: nop
    // IL_0001: ldloca.s 0
    // IL_0003: initobj !!T
    // IL_0009: ldloc.0
    // IL_000a: stloc.1
    // IL_000b: br.s IL_000d

    // IL_000d: ldloc.1
    // IL_000e: ret
    public static T GenericReturn<T>() {
        return default(T);
    }

    // .locals init (
    //     [0] class [System.Runtime]System.Type
    // )

    // IL_0000: nop
    // IL_0001: ldtoken !!T
    // IL_0006: call class [System.Runtime]System.Type [System.Runtime]System.Type::GetTypeFromHandle(valuetype [System.Runtime]System.RuntimeTypeHandle)
    // IL_000b: stloc.0
    // IL_000c: br.s IL_000e

    // IL_000e: ldloc.0
    // IL_000f: ret
    public static System.Type GetGenericType<T>() {
        return typeof(T);
    }

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

    // .locals init (
    //     [0] !!T
    // )

    // IL_0000: nop
    // IL_0001: call !!0 [System.Runtime]System.Activator::CreateInstance<!!T>()
    // IL_0006: stloc.0
    // IL_0007: br.s IL_0009

    // IL_0009: ldloc.0
    // IL_000a: ret
    public static T GenericNew<T>() where T : new() {
        return new T();
    }

    // .locals init (
    //     [0] !!T temp
    // )

    // IL_0000: nop
    // IL_0001: ldarg.0
    // IL_0002: ldobj !!T
    // IL_0007: stloc.0
    // IL_0008: ldarg.0
    // IL_0009: ldarg.1
    // IL_000a: ldobj !!T
    // IL_000f: stobj !!T
    // IL_0014: ldarg.1
    // IL_0015: ldloc.0
    // IL_0016: stobj !!T
    // IL_001b: ret
    public static void GenericSwap<T>(ref T a, ref T b) {
        var temp = a;
        a = b;
        b = temp;
    }

        // .locals init (
        //     [0] int32 a,
        //     [1] int32 b,
        //     [2] string a,
        //     [3] string b
        // )

        // IL_0000: nop
        // IL_0001: nop
        // IL_0002: ldc.i4.s 9
        // IL_0004: stloc.0
        // IL_0005: ldc.i4.5
        // IL_0006: stloc.1
        // IL_0007: ldloca.s 0
        // IL_0009: ldloca.s 1
        // IL_000b: call void Extensions::GenericSwap<int32>(!!0&, !!0&)
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
    public static void GenericSwapTest() {
        {
            int a = 9;
            int b = 5;
            GenericSwap(ref a, ref b);
        }

        {
            string a = "abc";
            string b = "de";
            GenericSwap(ref a, ref b);
        }
    }

    public static void GenericWhere<T, T2>(T obj) where T : IGeneric<T2> {
        var x = obj.GenericReturn();
    }

    // .locals init (
    //     [0] class GenericClass`1<!!T> foo,
    //     [1] !!T x,
    //     [2] !!T
    // )

    // IL_0000: nop
    // IL_0001: newobj instance void class GenericClass`1<!!T>::.ctor()
    // IL_0006: stloc.0
    // IL_0007: ldloc.0
    // IL_0008: ldarg.0
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
    public static T CallOtherGeneric<T>(T value) {
        GenericClass<T> foo = new GenericClass<T>();
        foo.GenericAction(value);
        var x = foo.GenericReturn();
        return x;
    }
}

class MainClass {

    public static void Main() {
        Extensions.GenericAction<int>(20);
        int v1 = Extensions.GenericReturn<int>();
        Extensions.CallOtherGeneric<int>(40);

        IGeneric<string> obj = new GenericClass<string>();
        obj.GenericAction("str");
        string v2 = obj.GenericReturn();
        IGenericParent<string> upcasted = obj;
        IGenericParent<object> parentObj = upcasted;
        int val = 10;
        object intObj = 20;
        IGenericParent<string> structObj = new GenericStruct<string>();
        structObj.GenericReturn();
    }
}
