#include "vm.h"
#include "util.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <codecvt>
#include <locale>
#include <string>
#include <mutex>

static char head_buf[20];
static std::mutex log_lock;

const void *LINFO  = (void*)1;
const void *LERROR = (void*)2;
const void *LWARN  = (void*)3;
const void *LDEBUG = (void*)4;
const void *LFATAL = (void*)5;

const char* prefix[] = {
    " ",
    " INFO.", 
    "ERROR.", 
    " WARN.", 
    "DEBUG.", 
    "FATAL.",
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


static void update_time(const void *level) {
    time_t now = time(0);
    tm t;
    localtime_s(&t, &now);
    sprintf_s(head_buf, sizeof(head_buf), "%02d:%02d:%02d %s", 
        t.tm_hour, t.tm_min, t.tm_sec, prefix[int(level)]);
}


void println(const char *out) {
    std::lock_guard<std::mutex> lock(log_lock);
    update_time(LINFO);
    sys_out(out);
}


void println(const std::string str) {
    std::lock_guard<std::mutex> lock(log_lock);
    update_time(LINFO);
    sys_out(str.c_str());
}


static JsValueRef logfunc(JsValueRef callee, JsValueRef *args, unsigned short ac,
                          JsNativeFunctionInfo *info, void *level) 
{
    std::lock_guard<std::mutex> lock(log_lock);
    update_time(level);
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


void installConsole(VM* vm) {
    checkCodePage();
    LocalVal console = vm->createObject();
    vm->getGlobal().put("console", console);
    console.put("log",   vm->createFunction(&logfunc, "info",  LINFO));
    console.put("info",  vm->createFunction(&logfunc, "info",  LINFO));
    console.put("warn",  vm->createFunction(&logfunc, "warn",  LWARN));
    console.put("error", vm->createFunction(&logfunc, "error", LERROR));
    console.put("debug", vm->createFunction(&logfunc, "debug", LINFO));
    console.put("fatal", vm->createFunction(&logfunc, "fatal", LFATAL));
}