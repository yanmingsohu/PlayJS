#include "vm.h"
#include "fs.h"

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


void pushException(std::string msg) {
    JsValueRef ex=0, err=0;
    JsCreateString(msg.c_str(), msg.length(), &ex);
    JsCreateError(ex, &err);
    JsSetException(ex);
}


int intValue(JsValueRef v, int defaultVal) {
    int i = defaultVal;
    if (v) {
        JsNumberToInt(v, &i);
    }
    return i;
}


JsValueRef wrapJs(int i) {
    JsValueRef v = 0;
    JsIntToNumber(i, &v);
    return v;
}