#include "vm.h"
#include <iostream>
#include <ctime>
#include <sstream>

const void *LINFO  = (void*)1;
const void *LERROR = (void*)2;
const void *LWARN  = (void*)3;
const void *LDEBUG = (void*)4;
const void *LFATAL = (void*)5;

const char* prefix[] = {
    " ",
    "[INFO ]", 
    "[ERROR]", 
    "[WARN ]", 
    "[DEBUG]", 
    "[FATAL]",
};


static JsValueRef logfunc(JsValueRef callee, JsValueRef *args, unsigned short ac,
                          JsNativeFunctionInfo *info, void *level) 
{
    std::stringbuf buf;
    std::ostream os(&buf);

    time_t now = time(0);
    tm t;
    localtime_s(&t, &now);
    os << t.tm_hour <<':'<< t.tm_min <<':'<< t.tm_sec  <<' ';

    os << prefix[int(level)];
    for (unsigned short i = 1; i < ac; ++i) {
        LocalVal v(args[i]);
        os << prefix[0] << v;
    }
    
    os << std::endl;
    std::cout << buf.str();
    return 0;
}


void installConsole(VM* vm) {
    LocalVal console = vm->createObject();
    vm->getGlobal().put("console", console);
    console.put("log",   vm->createFunction(&logfunc, "info",  LINFO));
    console.put("info",  vm->createFunction(&logfunc, "info",  LINFO));
    console.put("warn",  vm->createFunction(&logfunc, "warn",  LWARN));
    console.put("error", vm->createFunction(&logfunc, "error", LERROR));
    console.put("debug", vm->createFunction(&logfunc, "debug", LINFO));
    console.put("fatal", vm->createFunction(&logfunc, "fatal", LFATAL));
}