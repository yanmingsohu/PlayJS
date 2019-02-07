#include "vm.h"

#include <sstream>
#include <codecvt>
#include <locale>

// wstring_convert 在 c++17 中声明废弃
#pragma warning(disable: 4996) 
using std::wstring_convert;
using std::codecvt_byname;
using std::wstring;
using std::codecvt_utf8;
using std::string;

#ifdef WIN32
const char* GBK_LOCALE_NAME = ".936";
#else
const char* GBK_LOCALE_NAME = "zh_CN.GBK";
#endif


void gbk2utf8(char* from, int fromLenth, string &out) {
    wstring_convert<codecvt_byname<wchar_t, char, mbstate_t>> cv1(
            new codecvt_byname<wchar_t, char, mbstate_t>(GBK_LOCALE_NAME));
    wstring_convert<codecvt_utf8<wchar_t>> cv2;

    wstring tmp_wstr = cv1.from_bytes(from, from + fromLenth);
    out = cv2.to_bytes(tmp_wstr);
}


static JsValueRef js_utf8string(JsValueRef callee, JsValueRef *args, unsigned short ac,
                                JsNativeFunctionInfo *info, void *d)
{
    if (ac != 2 && ac != 3) {
        pushException("bad arguments, toUtf8String(TypedArray, length)");
        return 0;
    }
    LocalTypedArray arr(args[1]);
    size_t len = intValue(args[2], arr.length());
    JsValueRef str;
    JsCreateString(arr.buffer(), min(arr.length(), len), &str);
    return str;
}


static JsValueRef js_gbkstring(JsValueRef callee, JsValueRef *args, unsigned short ac,
                               JsNativeFunctionInfo *info, void *d)
{
    if (ac != 2 && ac != 3) {
        pushException("bad arguments, toUtf8String(TypedArray, length)");
        return 0;
    }
    LocalTypedArray arr(args[1]);
    size_t len = intValue(args[2], arr.length());
    JsValueRef str = 0;
    string utf8_str;
    gbk2utf8(arr.buffer(), min(len, arr.length()), utf8_str);

    JsCreateString(utf8_str.c_str(), utf8_str.length(), &str);
    return str;
}


void installUtf(VM *vm) {
    LocalVal utf = vm->createObject();
    vm->getGlobal().put("Unicode", utf);
    utf.put("toUtf8String", vm->createFunction(&js_utf8string, "toUtf8String"));
    utf.put("toGbkString",  vm->createFunction(&js_gbkstring,  "toGbkString"));
}