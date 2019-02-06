#include "shared.h"

#include <string>

using std::string;


class _Undefined : public CppVal {
public:
    _Undefined() {}

    LocalVal wrap() {
        JsValueRef val = 0;
        JsGetUndefinedValue(&val);
        return val;
    }
};


class _Null : public CppVal {
public:
    _Null() {}

    LocalVal wrap() {
        JsValueRef val = 0;
        JsGetNullValue(&val);
        return val;
    }
};


class _Number : public CppVal {
private:
    double num;
public:
    _Number(LocalVal& v) {
        JsNumberToDouble(v.js(), &num);
    }

    LocalVal wrap() {
        JsValueRef val = 0;
        JsDoubleToNumber(num, &val);
        return val;
    }
};


class _Boolean : public CppVal {
private:
    bool b;
public:
    _Boolean(LocalVal& v) {
        JsBooleanToBool(v.js(), &b);
    }
    
    LocalVal wrap() {
        JsValueRef val = 0;
        JsBoolToBoolean(b, &val);
        return val;
    }
};


class _String : public CppVal {
private:
    string str;
public:
    _String(LocalVal& v) {
        size_t len = 0;
        JsCopyString(v.js(), 0, 0, &len);
        str.resize(len+1, 0);
        size_t wlen = 0;
        JsCopyString(v.js(), (char*)str.c_str(), len, &wlen);
    }

    LocalVal wrap() {
        JsValueRef val = 0;
        JsCreateString(str.c_str(), str.length(), &val);
        return val;
    }
};


CppVal* wrapCppVal(LocalVal& v) {
    JsValueType t = getJsType(v.js());
    switch (t) {
        case JsUndefined:
            return new _Undefined();
        case JsNull:
            return new _Null();
        case JsNumber:
            return new _Number(v);
        case JsString:
            return new _String(v);
        case JsBoolean:
            return new _Boolean(v);

        case JsObject:
        case JsFunction:
        case JsError:
        case JsArray:
        case JsSymbol:
        case JsArrayBuffer:
        case JsTypedArray:
        case JsDataView:
        default:
            pushException("Cannot wrap js object to non-vm data");
            return 0;
    }
}


LocalVal& SharedValue::js() {
    if (cpp) {
        return cpp->wrap();
    }
    return _Undefined().wrap();
}


JS_FUNC_TPL(js_primitive, callee, args, ac, info, _vm) {
    return 0;
}


void installShared(VM* vm) {
    DEF_GLOBAL(vm, shared);
    DEF_JS_FUNC(vm, vm, shared, primitive, js_primitive);
}