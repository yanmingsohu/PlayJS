#pragma once

#include "vm.h"

//
// 声明已经定义的函数, 并调用
//
#define JSS_DECLARE_MODULE(name) \
    JSS_INIT_MODULE(name); \
    name(data)


template<class T>
void installJsLibrary(T *data) {
    JSS_DECLARE_MODULE(installVM);
    JSS_DECLARE_MODULE(installConsole);
    JSS_DECLARE_MODULE(installFileSystem);
    JSS_DECLARE_MODULE(installUtf);
    JSS_DECLARE_MODULE(installThread);
    JSS_DECLARE_MODULE(installEvents);
    JSS_DECLARE_MODULE(installShared);
    JSS_DECLARE_MODULE(installGL);
    JSS_DECLARE_MODULE(installImage);
    JSS_DECLARE_MODULE(installModelParser);
    JSS_DECLARE_MODULE(installGlobal);
    JSS_DECLARE_MODULE(installSpecial);
}


template<class T>
void unstallJsLIbrary(T *data) {
    JSS_DECLARE_MODULE(unstallGL);
    JSS_DECLARE_MODULE(destoryEvents);
    JSS_DECLARE_MODULE(unstallGlobal);
}

