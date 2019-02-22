#include "vm.h"

// 生化危机2 扩展, 必要时头文件可以注释
#include "../vs/adt/adt.h"


#ifdef BIO2_ADT_EXT
JSS_FUNC(bio2_adt_unpack_img, args, ac) {
    JSS_CHK_ARG(1, bio2_adt_unpack_img(TypedArray));
    LocalTypedArray arr(args[1]);
    unsigned char* out = 0;
    int len = 0;
    unpackImage((unsigned char*) arr.buffer(), arr.length(), &out, &len);

    if (len > 0 && out) {
        JsValueRef arr = 0;
        JsCreateArrayBuffer(len, &arr);
        BYTE *innerPtr = 0;
        unsigned int innerLen = 0;
        JsGetArrayBufferStorage(arr, &innerPtr, &innerLen);

        if (innerPtr && innerLen == len) {
            memcpy(innerPtr, out, len);
            return arr;
        } else {
            pushException("bad ArrayBuffer length");
        }
    } else {
        pushException("result get null buff");
    }
    return 0;
}
#endif


//
// 针对特定游戏安装的本机方法
//
void installSpecial(VM *vm) {
    JSS_MOD(special);
#ifdef BIO2_ADT_EXT
    JSS_BIND(bio2_adt_unpack_img);
#endif
}
