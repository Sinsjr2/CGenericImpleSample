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


void MainClass_Main(void) {
    const GenericClass_T_ALIGN align = GetAlign_GenericClass_T(sizeT);
    int stack0_0;
    int v1;
    int stack2;

    stack0_0 = 20;
    Extensions_GenericAction(sizeof int32_t, &stack0_0);
    Extensions_GenericReturn(sizeof int32_t, &v1);
    stack2 = 40;
    Extensions_CallOtherGeneric(sizeof int32_t, stack2);

    memset(stack0_0, 0, sizeT);
    memcpy(result, stack0_0, sizeT);
}
