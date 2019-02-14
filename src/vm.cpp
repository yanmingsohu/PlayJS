#include "vm.h"
#include "fs.h"
#include "util.h"

#include <map>
#include <filesystem>

using namespace std;
using namespace experimental::filesystem::v1; 

//
// {模块:完整路径} (不包括文件名)
//
static map<JsModuleRecord, string> modMap;
//
// {完整绝对路径:模块} 模块缓存
// 模块可以在多个 js runtime 里面运行, 支持多线程
//
static map<string, JsModuleRecord> loaded;


ostream& operator<<(ostream& a, LocalVal& b) {
    a << b.toString();
    return a;
}


//
// 关联 module 和文件的完整路径(包括文件名)
//
void saveMod(JsModuleRecord m, string& fullpath) {
    //cout << m << " " << fullpath << endl;
    modMap[m] = path(fullpath).parent_path().string();
    loaded[canonical(fullpath).string()] = m;
}


JsErrorCode iFetchImportedModuleCallBack(
    _In_ JsModuleRecord referencingModule,
    _In_ JsValueRef specifier,
    _Outptr_result_maybenull_ JsModuleRecord* dependentModuleRecord) 
{
    path full("./");
    auto rmod = modMap.find(referencingModule);
    if (rmod != modMap.end()) {
        full.append(rmod->second);
    }
    LocalVal spec(specifier);
    full.append(spec.toString());
    if (!exists(full)) {
        return JsErrorInvalidArgument;
    }

    auto lmod = loaded.find(canonical(full).string());
    if (lmod != loaded.end()) {
        *dependentModuleRecord = lmod->second;
        return JsNoError;
    }

    string content;
    if (readTxtFile(full.string(), content) == FAILED) {
        return JsErrorInvalidArgument;
    }

    return newModule(referencingModule, JS_SOURCE_CONTEXT_NONE, 
              full.string(), content, dependentModuleRecord);
}


JsErrorCode iFetchImportedModuleFromScriptCallBack(
    _In_ JsSourceContext dwReferencingSourceContext,
    _In_ JsValueRef specifier,
    _Outptr_result_maybenull_ JsModuleRecord* dependentModuleRecord) 
{
    //std::cout << "iFetchImportedModuleFromScriptCallBack\n";
    return JsErrorInvalidArgument;
}


JsErrorCode iNotifyModuleReadyCallback(
    _In_opt_ JsModuleRecord referencingModule,
    _In_opt_ JsValueRef exceptionVar)
{
    //std::cout << "iNotifyModuleReadyCallback\n";
    return JsModuleEvaluation(referencingModule, 0);
}


JsErrorCode newModule(JsModuleRecord parent,
                      JsSourceContext sourceContext,
                      std::string &fileName, 
                      std::string &script,
                      JsModuleRecord* moduleRet) {
    JsErrorCode err = JsNoError;
    JsValueRef spec;
    err = JsCreateString(fileName.c_str(), fileName.length(), &spec);
    if (err) return err;

    JsModuleRecord newMod;
    err = JsInitializeModuleRecord(parent, spec, &newMod);
    if (err) return err;
    saveMod(newMod, fileName);

    JsSetModuleHostInfo(newMod, JsModuleHostInfo_Url, spec);
    JsValueRef exception = 0;
    err = JsParseModuleSource(newMod, sourceContext,
            (BYTE*)script.c_str(), script.length(),
            JsParseModuleSourceFlags_DataIsUTF8, &exception);
    
    if (exception) {
        return JsErrorModuleParsed;
    }
    if (err) return err;

    if (moduleRet) {
        *moduleRet = newMod;
    }
    return JsNoError;
}


void pushException(std::string msg, int code) {
    JsValueRef ex=0, err=0;
    JsCreateString(msg.c_str(), msg.length(), &ex);
    JsCreateError(ex, &err);
    if (code) {
        JsPropertyIdRef id;
        JsCreatePropertyId("code", 4, &id);
        JsSetProperty(err, id, wrapJs(code), true);
    }
    JsSetException(err);
}


int intValue(JsValueRef v, int defaultVal) {
    int i = defaultVal;
    if (v) {
        JsNumberToInt(v, &i);
    }
    return i;
}


double floatValue(JsValueRef v, double defaultVal) {
    double f = defaultVal;
    if (v) {
        JsNumberToDouble(v, &f);
    }
    return f;
}


double doubleValue(JsValueRef v, double defaultVal) {
    double f = defaultVal;
    if (v) {
        JsNumberToDouble(v, &f);
    }
    return f;
}


bool boolValue(JsValueRef v, bool defaultVal) {
    bool r = defaultVal;
    if (v) {
        JsBooleanToBool(v, &r);
    }
    return r;
}


bool isJsNumber(JsValueRef v) {
    return getJsType(v) == JsNumber;
}


JsValueType getJsType(JsValueRef v) {
    if (!v) return JsUndefined;
    JsValueType t = JsUndefined;
    JsGetValueType(v, &t);
    return t;
}


JsValueRef wrapJs(size_t i) {
    return wrapJs(static_cast<int>(i));
}


JsValueRef wrapJs(int i) {
    JsValueRef v = 0;
    JsIntToNumber(i, &v);
    return v;
}


JsValueRef wrapJs(double i) {
    JsValueRef v = 0;
    JsDoubleToNumber(i, &v);
    return v;
}


JsValueRef wrapJs(bool b) {
    JsValueRef v = 0;
    JsBoolToBoolean(b, &v);
    return v;
}


JsValueRef wrapJs(const char* str) {
    if (!str) return 0;
    JsValueRef s = 0;
    JsCreateString(str, strlen(str), &s);
    return s;
}


JsValueRef wrapJs(unsigned int i) {
    return wrapJs(static_cast<int>(i));
}


JsValueRef checkError() {
    if (hasThrowException()) {
        JsValueRef result = 0;
        JsGetAndClearException(&result);
        return result;
    }
    return 0;
}


bool hasThrowException() {
    bool hasErr = false;
    JsHasException(&hasErr);
    return hasErr;
}


std::string toString(JsValueRef str) {
    return stringValue(str);
}


std::string stringValue(JsValueRef str, std::string def) {
    size_t len = 0;
    JsCopyString(str, 0, 0, &len);

    if (len > 0) {
        std::unique_ptr<char[]> buf(new char[len + 1]);
        buf[len] = 0;
        JsCopyString(str, buf.get(), len, 0);
        return std::string(buf.get());
    }
    return def;
}


void VM:: initModule() {
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


void LocalTypedArray::init() {
    JsValueType type;
    JsGetValueType(jsv, &type);
    JsErrorCode code;

    if (type == JsTypedArray) {
        code = JsGetTypedArrayStorage(jsv, &_buf, &_len, &_type, &_byteLen);
    }
    else if (type == JsArrayBuffer) {
        code = JsGetArrayBufferStorage(jsv, &_buf, &_len);
        _byteLen = _len;
        _type = JsArrayTypeInt8;
    }
    else {
        pushException("<LocalTypedArray> Value Is not TypedArray or ArrayBuffer");
    }

    if (JsNoError != code) {
        _len = 0;
        _buf = 0;
        _byteLen = -1;
        pushException(parseJsErrCode(code));
    }
}


const char* const getJsTypeName(const JsValueType type) {
    switch (type) {
        case JsUndefined:   return "undefined";
        case JsNull:        return "null";
        case JsNumber:      return "Number";
        case JsString:      return "String";
        case JsBoolean:     return "Boolean";
        case JsObject:      return "Object";
        case JsFunction:    return "Function";
        case JsError:       return "Error";
        case JsArray:       return "Array";
        case JsSymbol:      return "Symbol";
        case JsArrayBuffer: return "ArrayBuffer";
        case JsTypedArray:  return "TypedArray";
        case JsDataView:    return "JsDataView";
    }
}


const char* const parseJsErrCode(JsErrorCode c) {
    switch (c) {
    case JsNoError: return 0;
    default: return "Unknow error";

    case JsErrorCategoryUsage:  return 
    "Category of errors that relates to incorrect usage of the API itself.";

    case JsErrorInvalidArgument: return
    "An argument to a hosting API was invalid.";

    case JsErrorNullArgument: return
    "An argument to a hosting API was null in a context where null is not allowed.";

    case JsErrorNoCurrentContext: return
    "The hosting API requires that a context be current, but there is no current context.";

    case JsErrorInExceptionState: return
    "The engine is in an exception state and no APIs can \
    be called until the exception is cleared.";

    case JsErrorNotImplemented: return
    "A hosting API is not yet implemented.";

    case JsErrorWrongThread: return 
    "A hosting API was called on the wrong thread.";

    case JsErrorRuntimeInUse: return
    "A runtime that is still in use cannot be disposed.";

    case JsErrorBadSerializedScript: return
    "A bad serialized script was used, or the serialized script was serialized by a \
    different version of the Chakra engine.";

    case JsErrorInDisabledState: return
    "The runtime is in a disabled state.";

    case JsErrorCannotDisableExecution: return
    "Runtime does not support reliable script interruption.";

    case JsErrorHeapEnumInProgress: return
    "A heap enumeration is currently underway in the script context.";

    case JsErrorArgumentNotObject: return
    "A hosting API that operates on object values was called with a non-object value.";

    case JsErrorInProfileCallback: return 
    "A script context is in the middle of a profile callback.";

    case JsErrorInThreadServiceCallback: return
    "A thread service callback is currently underway.";

    case JsErrorCannotSerializeDebugScript: return
    "Scripts cannot be serialized in debug contexts.";

    case JsErrorAlreadyDebuggingContext: return
    "The context cannot be put into a debug state because it is already in a debug state.";

    case JsErrorAlreadyProfilingContext: return
    "The context cannot start profiling because it is already profiling.";

    case JsErrorIdleNotEnabled: return
    "Idle notification given when the host did not enable idle processing.";

    case JsCannotSetProjectionEnqueueCallback: return
    "The context did not accept the enqueue callback.";

    case JsErrorCannotStartProjection: return 
    "Failed to start projection.";

    case JsErrorInObjectBeforeCollectCallback: return
    "The operation is not supported in an object before collect callback.";

    case JsErrorObjectNotInspectable: return
    "Object cannot be unwrapped to IInspectable pointer.";

    case JsErrorPropertyNotSymbol: return
    "A hosting API that operates on symbol property ids but was called with \
    a non-symbol property id. The error code is returned by \
    JsGetSymbolFromPropertyId if the function is called with non-symbol property id.";

    case JsErrorPropertyNotString: return
    "A hosting API that operates on string property ids but was called with \
    a non-string property id. The error code is returned by existing \
    JsGetPropertyNamefromId if the function is called with non-string property id.";

    case JsErrorInvalidContext: return
    "Module evaluation is called in wrong context.";

    case JsInvalidModuleHostInfoKind: return
    "The Module HostInfoKind provided was invalid.";

    case JsErrorModuleParsed: return
    "Module was parsed already when JsParseModuleSource is called.";

    case JsNoWeakRefRequired: return
    "Argument passed to JsCreateWeakReference is a primitive that is not managed by the GC.\
    No weak reference is required, the value will never be collected.";

    case JsErrorPromisePending: return
    "The [Promise] object is still in the pending state.";

    case JsErrorModuleNotEvaluated: return
    "Module was not yet evaluated when JsGetModuleNamespace was called.";

    case JsErrorCategoryEngine: return
    "Category of errors that relates to errors occurring within the engine itself.";

    case JsErrorOutOfMemory: return
    "The Chakra engine has run out of memory.";

    case JsErrorBadFPUState: return
    "The Chakra engine failed to set the Floating Point Unit state.";

    case JsErrorCategoryScript: return
    "Category of errors that relates to errors in a script.";

    case JsErrorScriptException: return
    "A JavaScript exception occurred while running a script.";

    case JsErrorScriptCompile: return
    "JavaScript failed to compile.";

    case JsErrorScriptTerminated: return
    "A script was terminated due to a request to suspend a runtime.";

    case JsErrorScriptEvalDisabled: return
    "A script was terminated because it tried to use [eval] or [function] \
    and eval was disabled.";

    case JsErrorCategoryFatal: return
    "Category of errors that are fatal and signify failure of the engine.";

    case JsErrorFatal: return
    "A fatal error in the engine has occurred.";

    case JsErrorWrongRuntime: return
    "A hosting API was called with object created on different javascript runtime.";

    case JsErrorCategoryDiagError: return
    "Category of errors that are related to failures during diagnostic operations.";

    case JsErrorDiagAlreadyInDebugMode: return
    "The object for which the debugging API was called was not found";

    case JsErrorDiagNotInDebugMode: return
    "The debugging API can only be called when VM is in debug mode";

    case JsErrorDiagNotAtBreak: return
    "The debugging API can only be called when VM is at a break";

    case JsErrorDiagInvalidHandle: return
    "Debugging API was called with an invalid handle.";

    case JsErrorDiagObjectNotFound: return
    "The object for which the debugging API was called was not found";

    case JsErrorDiagUnableToPerformAction: return
    "VM was unable to perform the request action";
    }
}