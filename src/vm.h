#pragma once

#include "ChakraCore/lib/Jsrt/ChakraCore.h"
#include "ChakraCore/lib/Jsrt/ChakraCommon.h"

#include <string>
#include <iostream>

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
// 在局部变量上引用 js 对象, 自动对 js 对象增加外部引用计数
//
class LocalVal {
protected:
    const JsValueRef jsv;

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
        return toString(str);
    }


    std::string toString(JsValueRef str) {
        size_t len = 0;
        JsCopyString(str, 0, 0, &len);

        if (len > 0) {
            char *buf = new char[len + 1];
            buf[len] = 0;
            JsCopyString(str, buf, len, 0);
            std::string s = std::string(buf);
            delete[] buf;
            return s;
        }
        return std::string();
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


    bool isNull() {
        return jsv == 0;
    }

    bool notNull() {
        return jsv != 0;
    }
};


//
// 方便对 TypedArray 的操作
//
class LocalArray : public LocalVal {
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

    LocalArray(JsValueRef r) : LocalVal(r) {
        init();
    }

    LocalArray(LocalArray& o) : LocalVal(o) {
        init();
    }

    BYTE* buffer() {
        return _buf;
    }

    //
    // 数组的长度, 总字节数
    //
    unsigned int length() {
        return _len;
    }

    //
    // 每个元素的长度, 单位字节
    //
    int unitLen() {
        return _byteLen;
    }

    //
    // 底层数组类型
    //
    JsTypedArrayType type() {
        return _type;
    }
};


class VM {
private:
	JsRuntimeHandle runtime;
	JsContextRef context;
	unsigned currentSourceContext;


    void initModule() {
        char desc[] = "bootstrap";
        JsContextRef spec;
        JsCreateString(desc, sizeof(desc), &spec);
        JsModuleRecord root;
        JsInitializeModuleRecord(NULL, spec, &root);

        JsSetModuleHostInfo(root, 
            JsModuleHostInfo_FetchImportedModuleCallback,
            &iFetchImportedModuleCallBack);
        JsSetModuleHostInfo(root, 
            JsModuleHostInfo_FetchImportedModuleFromScriptCallback,
            &iFetchImportedModuleFromScriptCallBack);
        JsSetModuleHostInfo(root, 
            JsModuleHostInfo_NotifyModuleReadyCallback,
            &iNotifyModuleReadyCallback);
    }

public:

	VM() : currentSourceContext(0) {
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
		bool hasErr = false;
		JsHasException(&hasErr);
		if (hasErr) {
			JsValueRef result = 0;
			JsGetAndClearException(&result);
			return result;
		}
		return 0;
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


    LocalVal createFunction(JsEnhancedNativeFunction f, char* name=0, const void* d=0) {
        JsValueRef meta = JS_INVALID_REFERENCE;
        if (name) {
            JsCreateString(name, strlen(name), &meta);
        }
        JsValueRef jf = 0;
        JsCreateEnhancedFunction(f, meta, (void*)d, &jf);
        return jf;
    }
};


std::ostream& operator<<(std::ostream& a, LocalVal& b);
void pushException(std::string);
int intValue(JsValueRef r, int defaultVal = 0);
JsValueRef wrapJs(int i);