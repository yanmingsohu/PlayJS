#pragma once

#include "ChakraCore/lib/Jsrt/ChakraCore.h"
#include "ChakraCore/lib/Jsrt/ChakraCommon.h"

#include <string>
#include <iostream>
#include "threads.h"

JsErrorCode iFetchImportedModuleCallBack(
    _In_ JsModuleRecord referencingModule,
    _In_ JsValueRef specifier,
    _Outptr_result_maybenull_ JsModuleRecord* dependentModuleRecord);

JsErrorCode iFetchImportedModuleFromScriptCallBack(
    _In_ JsSourceContext dwReferencingSourceContext,
    _In_ JsValueRef specifier,
    _Outptr_result_maybenull_ JsModuleRecord* dependentModuleRecord);

JsErrorCode iNotifyModuleReadyCallback(
    _In_opt_ JsModuleRecord referencingModule,
    _In_opt_ JsValueRef exceptionVar);

JsErrorCode newModule(JsModuleRecord parent,
    JsSourceContext sourceContext,
    std::string &fileName,
    std::string &script, 
    JsModuleRecord* moduleRet);

//
// 在 js 虚拟机中抛出异常
//
void pushException(std::string, int code = 0);

//
// 把 js 数字对象转换为 整数, 如果 r 不是数字或出错, 返回默认值
//
int intValue(JsValueRef r, int defaultVal = 0);
double floatValue(JsValueRef v, double defaultVal = 0);
double doubleValue(JsValueRef v, double defaultVal = 0);


//
// 把 c++ 数据包装成 js 对象
//
JsValueRef wrapJs(int i);
JsValueRef wrapJs(double i);
JsValueRef wrapJs(bool b);
JsValueRef wrapJs(const char* str);
JsValueRef wrapJs(size_t i);
JsValueRef wrapJs(unsigned int i);


//
// 参数是数字类型返回 true
//
bool isJsNumber(JsValueRef v);

//
// 返回 js 对象句柄指向数据类型的枚举
//
JsValueType getJsType(JsValueRef v);

//
// 尝试把 js 对象输出为字符串(即使不是字符串对象)
//
std::string toString(JsValueRef str);

//
// 检查 js 虚拟机异常状态, 如果有异常返回异常句柄, 否则返回 0;
// 虚拟机中的异常必须处理后方可继续运行.
//
JsValueRef checkError();

//
// 在脚本中有抛出的异常(非虚拟机错误, 如脚本解析错误)
//
bool hasThrowException();

//
// 解析 js 错误代码为字符串
//
const char* const parseJsErrCode(JsErrorCode c);

//
// 在 obj(LocalVal) 对象上绑定名字为 name 的方法 func_ptr(本地cpp函数指针)
// 必要时附加扩展数据 ext_data, 或为 NULL
//
#define DEF_JS_FUNC(vm, ext_data, obj, jsname, func_ptr) \
    obj.put(#jsname, vm->createFunction(&func_ptr, #jsname, ext_data))

//
// 用 val_name 绑定 js 全局变量, 创建 cpp 的变量句柄 val_name
//
#define DEF_GLOBAL(vm, val_name) \
    LocalVal val_name = vm->createObject(); \
    vm->getGlobal().put(#val_name, val_name)

//
// 生成 js 本机方法函数头.
// args[0] 是 this, args[1] 是第一个参数.
//
#define JS_FUNC_TPL(name, callee, args, argc, info, vm) \
    static JsValueRef name( \
        JsValueRef callee, JsValueRef *args, unsigned short argc, \
        JsNativeFunctionInfo *info, void *vm)

//
// 在局部变量上引用 js 对象, 自动对 js 对象增加外部引用计数
//
class LocalVal {
protected:
    JsValueRef jsv;

private:
    void add() {
        if (jsv) JsAddRef(jsv, 0);
    }

public:
    
    LocalVal(JsValueRef ref) : jsv(ref) {
        add();
    }


    LocalVal(const LocalVal &other) : jsv(other.jsv) {
        add();
    }

    
    virtual ~LocalVal() {
        if (jsv) JsRelease(jsv, 0);
    }


    virtual std::string toString() {
        if (!jsv) return "null";
        JsValueRef str;
        JsConvertValueToString(jsv, &str);
        return ::toString(str);
    }


    void put(std::string name, LocalVal v, bool strict = false) {
        JsPropertyIdRef id;
        JsCreatePropertyId(name.c_str(), name.length(), &id);
        JsSetProperty(jsv, id, v.jsv, strict);
    }


    LocalVal get(std::string name) {
        JsPropertyIdRef id;
        JsCreatePropertyId(name.c_str(), name.length(), &id);
        JsValueRef v;
        JsGetProperty(jsv, id, &v);
        return v;
    }


    //
    // jsv 是个函数, 使用参数调用之,
    // 该方法只有一个参数; 如果函数调用失败, 会生成 js 异常.
    //
    LocalVal call(LocalVal arg) const {
        JsValueRef undef  = undefined();
        JsValueRef args[] = { undef, arg.jsv };
        JsValueRef result = 0;
        if (JsErrorCode c = JsCallFunction(jsv, args, 2, &result)) {
            if (! hasThrowException()) {
                pushException(parseJsErrCode(c));
            }
        }
        return result;
    }


    JsValueRef undefined() const {
        JsValueRef undef = 0;
        JsGetUndefinedValue(&undef);
        return undef;
    }


    bool isNull() {
        return jsv == 0;
    }

    bool notNull() {
        return jsv != 0;
    }

    bool isFunction() {
        return getJsType(jsv) == JsFunction;
    }

    //
    // 返回 js 对象的句柄, 返回的句柄如果超出 LocalVal 生命周期,
    // 该句柄有可能被 js 虚拟机垃圾回收.
    // (本对象可以自动转换为 JsValueRef, 可以直接赋值给 JsValueRef 变量)
    //
    JsValueRef js() {
        return jsv;
    }


    operator JsValueRef() {
        return jsv;
    }


    bool operator==(const LocalVal& right) const {
        return jsv == right.jsv;
    }


    bool operator<(const LocalVal& right) const {
        return jsv < right.jsv;
    }
};


//
// 方便对 TypedArray 的操作
//
class LocalTypedArray : public LocalVal {
private:
    JsTypedArrayType _type;
    unsigned int _len;
    int _byteLen;
    BYTE* _buf;

    void init() {
        if (JsGetTypedArrayStorage(jsv, &_buf, &_len, &_type, &_byteLen)) {
            _len = 0;
            _buf = 0;
            _byteLen = -1;
        }
    }

public:

    LocalTypedArray(JsValueRef r) : LocalVal(r) {
        init();
    }

    LocalTypedArray(LocalTypedArray& o) : LocalVal(o) {
        init();
    }

    inline char* buffer() {
        return (char*)_buf;
    }

    //
    // 数组的长度, 总字节数
    //
    inline unsigned int length() {
        return _len;
    }

    //
    // 每个元素的长度, 单位字节
    //
    inline int unitLen() {
        return _byteLen;
    }

    //
    // 底层数组类型
    //
    inline JsTypedArrayType type() {
        return _type;
    }
};


//
// 普通 js 数组
//
class LocalArray : public LocalVal {
private:
    LocalVal klen = 0;
    LocalVal fpop = 0;
    LocalVal fpush = 0;

    void init() {
        klen = wrapJs("length");
        JsValueRef pop, push;
        JsObjectGetProperty(jsv, wrapJs("pop"), &pop);
        JsObjectGetProperty(jsv, wrapJs("push"), &push);
        fpop = pop;
        fpush = push;
    }

public:
    LocalArray(JsValueRef r) : LocalVal(r) {
        init();
    }

    LocalArray(LocalArray& o) : LocalVal(o) {
        init();
    }

    int length() {
        JsValueRef vlen = 0;
        JsObjectGetProperty(jsv, klen, &vlen);
        return intValue(vlen);
    }

    JsValueRef pop() {
        JsValueRef arg[] = { jsv };
        JsValueRef result = 0;
        JsCallFunction(fpop, arg, 1, &result);
        return result;
    }

    JsValueRef push(JsValueRef v) {
        JsValueRef arg[] = { jsv, v };
        JsValueRef result = 0;
        JsCallFunction(fpop, arg, 2, &result);
        return result;
    }

    void set(int index, JsValueRef v) {
        JsSetIndexedProperty(jsv, wrapJs(index), v);
    }

    JsValueRef get(int index) {
        JsValueRef res = 0;
        JsGetIndexedProperty(jsv, wrapJs(index), &res);
        return res;
    }
};


class VM {
private:
	JsRuntimeHandle runtime;
	JsContextRef context;
	unsigned currentSourceContext;
    threadId _tid;

    void initModule();

public:

	VM(threadId& tid) : currentSourceContext(0), _tid(tid) {
		JsCreateRuntime(JsRuntimeAttributeNone, nullptr, &runtime);
		JsCreateContext(runtime, &context);
		JsSetCurrentContext(context);
        initModule();
	}


    ~VM() {
        JsSetCurrentContext(JS_INVALID_REFERENCE);
        JsDisposeRuntime(runtime);
    }


    JsErrorCode loadModule(JsModuleRecord parent, 
                           std::string &fileName, std::string &script) {
        JsErrorCode code = newModule(
            parent, currentSourceContext, fileName, script, 0);
        if (code) return code;
        return JsNoError;
    }


    LocalVal eval(std::string code, std::string surl) {
		JsValueRef result;
		JsValueRef script;
		JsValueRef url;
		JsCreateString(code.c_str(), code.length(), &script);
		JsCreateString(surl.c_str(), surl.length(), &url);
		JsRun(script, currentSourceContext++, url, 
			JsParseScriptAttributeNone, &result);

		JsValueRef err = checkError();
		if (err) return err;
		return result;
	}


	JsValueRef checkError() {
        return ::checkError();
	}


    LocalVal getGlobal() {
        JsValueRef g = 0;
        JsGetGlobalObject(&g);
        return g;
    }


    LocalVal createObject() {
        JsValueRef o = 0;
        JsCreateObject(&o);
        return o;
    }


    //
    // 普通数组
    //
    LocalArray createArr(int length = 0) {
        JsValueRef o = 0;
        JsCreateArray(length, &o);
        return o;
    }


    LocalVal createFunction(JsEnhancedNativeFunction f, char* name=0, const void* d=0) {
        JsValueRef meta = JS_INVALID_REFERENCE;
        if (name) {
            JsCreateString(name, strlen(name), &meta);
        }
        JsValueRef jf = 0;
        JsCreateEnhancedFunction(f, meta, (void*)d, &jf);
        return jf;
    }


    //
    // 返回当前 vm 所在线程的 ID
    //
    threadId thread() {
        return _tid;
    }
};


std::ostream& operator<<(std::ostream& a, LocalVal& b);
