#include "vm.h"
#include "util.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <codecvt>
#include <locale>
#include <string>
#include <mutex>

static char head_buf[25];
static std::mutex log_lock;

const int LINFO  = 1;
const int LERROR = 2;
const int LWARN  = 3;
const int LDEBUG = 4;
const int LFATAL = 5;

const char* prefix[] = {
    0,
    "INF", 
    "ERR", 
    "WAN", 
    "DBG", 
    "FTL",
};

static unsigned int codePage;

#ifdef WIN32
static void checkCodePage() {
    codePage = ::GetACP();
}

//
// 必须多线程同步, 否则线程写入的内容将互相覆盖
//
static void sys_out(const char *src_str) {
    if (codePage != CP_UTF8) {
        static wchar_t buf1[2000];
        static char buf2[2000];

        int rlen = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, buf1, sizeof(buf1));
        WideCharToMultiByte(codePage, 0, buf1, rlen, buf2, sizeof(buf2), NULL, NULL);

        printf("%s %s\n", head_buf, buf2);
    } else {
        printf("%s %s\n", head_buf, src_str);
    }
}
#else
static void checkCodePage() {
}

static void sys_out(const char *out) {
    printf("%s %s\n", head_buf, out);
}
#endif


static void update_time(const int level, threadId id=0) {
    time_t now = time(0);
    tm t;
    localtime_s(&t, &now);
    sprintf_s(head_buf, sizeof(head_buf), "%02d:%02d:%02d #%02X %s|", 
        t.tm_hour, t.tm_min, t.tm_sec, id, prefix[level]);
}


void println(const char *out, threadId id) {
    std::lock_guard<std::mutex> lock(log_lock);
    update_time(LINFO, id);
    sys_out(out);
}


void println(const std::string str, threadId id) {
    std::lock_guard<std::mutex> lock(log_lock);
    update_time(LINFO, id);
    sys_out(str.c_str());
}


static JsValueRef logfunc(JsValueRef *args, unsigned short ac, int level, threadId id) 
{
    std::lock_guard<std::mutex> lock(log_lock);
    update_time(level, id);
    static char content_buf[2000];
    int buf_off = 0;

    for (unsigned short i = 1; i < ac; ++i) {
        LocalVal v(args[i]);
        std::string str = v.toString();

        int wlen = min(sizeof(content_buf)-buf_off, str.length());
        memcpy(content_buf + buf_off, str.c_str(), wlen);
        buf_off += wlen;
        content_buf[buf_off++] = ' ';

        if (buf_off > sizeof(content_buf)/2) {
            content_buf[buf_off] = 0;
            sys_out(content_buf);
            buf_off = 0;
        }
    }
    
    if (buf_off > 0) {
        content_buf[buf_off] = 0;
        sys_out(content_buf);
    }
    return 0;
}


static JsValueRef js_info(JsValueRef callee, JsValueRef *args, unsigned short ac,
                          JsNativeFunctionInfo *info, void *_vm)
{
    return logfunc(args, ac, LINFO, ((VM*)_vm)->thread());
}


static JsValueRef js_warn(JsValueRef callee, JsValueRef *args, unsigned short ac,
                          JsNativeFunctionInfo *info, void *_vm)
{
    return logfunc(args, ac, LWARN, ((VM*)_vm)->thread());
}


static JsValueRef js_error(JsValueRef callee, JsValueRef *args, unsigned short ac,
                           JsNativeFunctionInfo *info, void *_vm)
{
    return logfunc(args, ac, LERROR, ((VM*)_vm)->thread());
}


static JsValueRef js_debug(JsValueRef callee, JsValueRef *args, unsigned short ac,
                           JsNativeFunctionInfo *info, void *_vm)
{
    return logfunc(args, ac, LDEBUG, ((VM*)_vm)->thread());
}


static JsValueRef js_fatal(JsValueRef callee, JsValueRef *args, unsigned short ac,
                           JsNativeFunctionInfo *info, void *_vm)
{
    return logfunc(args, ac, LFATAL, ((VM*)_vm)->thread());
}


void installConsole(VM* vm) {
    checkCodePage();
    LocalVal console = vm->createObject();
    vm->getGlobal().put("console", console);
    console.put("log",   vm->createFunction(&js_info,  "info",  vm));
    console.put("info",  vm->createFunction(&js_info,  "info",  vm));
    console.put("warn",  vm->createFunction(&js_warn,  "warn",  vm));
    console.put("error", vm->createFunction(&js_error, "error", vm));
    console.put("debug", vm->createFunction(&js_debug, "debug", vm));
    console.put("fatal", vm->createFunction(&js_fatal, "fatal", vm));
}