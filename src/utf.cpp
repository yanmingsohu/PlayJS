#include "vm.h"


static JsValueRef js_tostring(JsValueRef callee, JsValueRef *args, unsigned short ac,
                              JsNativeFunctionInfo *info, void *d)
{
    if (ac != 2) {
        pushException("bad arguments length, toString(TypedArray)");
        return 0;
    }
    LocalArray arr(args[1]);
    JsValueRef str;
    JsCreateString((char*)arr.buffer(), arr.length(), &str);
    return str;
}


void installUtf(VM *vm) {
    LocalVal utf = vm->createObject();
    vm->getGlobal().put("Unicode", utf);
    utf.put("toUtf8String", vm->createFunction(&js_tostring, "toString"));
}