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


void println(const char *out, threadId id, int level) {
    std::lock_guard<std::mutex> lock(log_lock);
    update_time(level, id);
    sys_out(out);
}


void println(const std::string str, threadId id, int level) {
    println(str.c_str(), id, level);
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

        int wlen = min(sizeof(content_buf)-buf_off-1, str.length());
        memcpy(content_buf + buf_off, str.c_str(), wlen);
        buf_off += wlen;

        if (buf_off > sizeof(content_buf)/2) {
            content_buf[buf_off] = 0;
            sys_out(content_buf);
            buf_off = 0;
        } else {
            content_buf[buf_off++] = ' ';
        }
    }
    
    if (buf_off > 0) {
        content_buf[buf_off] = 0;
        sys_out(content_buf);
    }
    return 0;
}


JS_FUNC_TPL(js_info, c, args, ac, info, _vm) {
    return logfunc(args, ac, LINFO, ((VM*)_vm)->thread());
}


JS_FUNC_TPL(js_warn, c, args, ac, info, _vm) {
    return logfunc(args, ac, LWARN, ((VM*)_vm)->thread());
}


JS_FUNC_TPL(js_error, c, args, ac, info, _vm) {
    return logfunc(args, ac, LERROR, ((VM*)_vm)->thread());
}


JS_FUNC_TPL(js_debug, c, args, ac, info, _vm) {
    return logfunc(args, ac, LDEBUG, ((VM*)_vm)->thread());
}


JS_FUNC_TPL(js_fatal, c, args, ac, info, _vm) {
    return logfunc(args, ac, LFATAL, ((VM*)_vm)->thread());
}


void installConsole(VM* vm) {
    checkCodePage();
    DEF_GLOBAL(vm, console);

    DEF_JS_FUNC(vm, vm, console, log,   js_info);
    DEF_JS_FUNC(vm, vm, console, info,  js_info);
    DEF_JS_FUNC(vm, vm, console, warn,  js_warn);
    DEF_JS_FUNC(vm, vm, console, error, js_error);
    DEF_JS_FUNC(vm, vm, console, debug, js_debug);
    DEF_JS_FUNC(vm, vm, console, fatal, js_fatal);
}