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
