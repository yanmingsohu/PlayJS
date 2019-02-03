#pragma once

#include "threads.h"
#include "vm.h"

#include <memory>

class CppVal;

//
// 把 vm 对象转换为本机对象.
// 如果出错返回 0 并把错误消息发送到 vm.
//
CppVal* wrapCppVal(LocalVal& js);


class CppVal {
public:
    CppVal() {}
    CppVal(CppVal&) = delete;
    virtual ~CppVal() {};
    virtual LocalVal wrap() = 0;
};


//
// 该对象包装了 js 底层对象, 并允许在多个线程间传递
// 可以安全复制.
//
class SharedValue {
private:
    threadId src_tid;
    LocalVal v;
    std::shared_ptr<CppVal> cpp;

public:
    SharedValue(threadId tid, LocalVal& js) : src_tid(tid), v(js) {
        cpp.reset(wrapCppVal(js));
    }


    SharedValue() : src_tid(0), v(0), cpp(0) {}


    LocalVal& js();


    bool empty() {
        return cpp.get() == 0;
    }
};