#pragma once

#include "threads.h"
#include "vm.h"

#include <memory>
#include <map>
#include <shared_mutex>

class CppVal;
template<class T> class SharedPool;

//
// 把 vm 对象转换为本机对象.
// 如果出错返回 0 并把错误消息发送到 vm.
//
CppVal* wrapCppVal(LocalVal& js);
template<class T> int make_shared_handle(T* resource);
template<class T> size_t release_shared_resource(int handle);
template<class T> std::shared_ptr<T> get_shared_resource(int handle);
template<class T> SharedPool<T>& getSharedPool();


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

    //
    // 返回本机对象对应的 js 对象
    //
    LocalVal& js();

    bool empty() {
        return cpp.get() == 0;
    }
};


//
// T 类型的删除器, 必须针对每个类型特化这个类模板, 否则编译出错.
//
template<class T> struct SharedResourceDeleter {
    virtual void operator()(T* res) = 0;
};


//
// 每个类型都有自己的资源句柄池, 生成的资源句柄值可以相同, 
// 在语义上给予类型安全; 线程安全; 可以在多线程间共享数据.
//
template<class T>
class SharedPool {
public:
    typedef std::shared_ptr<T> SharedResource;
    typedef std::map<int, SharedResource> SharedMap;
    typedef std::pair<int, SharedResource> SharedPair;

private:
    std::shared_mutex m;
    SharedMap map;
    int id;

    SharedPool() : id(0) {}

    //
    // 保存指针并返回对应的句柄
    //
    int insert(T* p) { 
        // 如果编译报错, 检查 T 类型是否特化了 SharedResourceDeleter
        SharedResource sr(p, SharedResourceDeleter<T>());
        std::unique_lock lock(m);
        int handle = ++id;
        map.insert(SharedPair(handle, sr));
        return handle;
    }

    //
    // 用句柄换指针, 如果指针不存在返回 0
    //
    SharedResource get(int handle) {
        std::shared_lock lock(m);
        auto it = map.find(handle);
        if (it == map.end()) 
            return 0;
        return it->second;
    }

    //
    // 释放对句柄的引用, 内存由智能指针负责释放.
    //
    size_t release(int handle) {
        std::unique_lock lock(m);
        return map.erase(handle);
    }


friend int make_shared_handle<T>(T* resource);
friend size_t release_shared_resource<T>(int);
friend SharedPool<T>& getSharedPool<T>();
friend SharedResource get_shared_resource<T>(int handle);
};


//
// 每种类型都会生成对应的对象池
//
template<class T> 
SharedPool<T>& getSharedPool() {
    static SharedPool<T> pool;
    return pool;
}


//
// 创建资源的句柄, 句柄永远 > 0; 线程安全.
// 指针指向的资源不要在外部释放, 而是由模块内部管理.
//
template<class T>
int make_shared_handle(T* resource) {
    auto& pool = getSharedPool<T>();
    return pool.insert(resource);
}


//
// 直接把句柄包装为 js 对象
//
template<class T>
JsValueRef make_shared_js_handle(T* resource) {
    int handle = make_shared_handle(resource);
    return wrapJs(handle);
}


//
// 返回句柄指向的资源, 资源可能已经删除, 需要对返回做 bool 操作以判断空值.
// 如果句柄为 0 一定返回 0. 线程安全.
//
template<class T>
std::shared_ptr<T> get_shared_resource(int handle) {
    if (!handle) return 0;
    auto& pool = getSharedPool<T>();
    return pool.get(handle);
}


//
// jshandle 应该是个整数句柄. 如果句柄为 0 一定返回 0.
//
template<class T>
std::shared_ptr<T> get_shared_resource(JsValueRef jshandle) {
    if (!jshandle) return 0;
    return get_shared_resource<T>(intValue(jshandle));
}


//
// 释放句柄指向的资源, 资源可能不会立即被删除, 
// 而是等待所有对资源的引用都释放后资源才被删除,
// 资源被删除时将调用 SharedResourceDeleter 的特化版本.
// 失败返回 0, 否则返回 1.
//
template<class T>
size_t release_shared_resource(int handle) {
    if (!handle) return 0;
    auto& pool = getSharedPool<T>();
    return pool.release(handle);
}


//
// jshandle 应该是个整数句柄. 如果句柄为 0 一定返回 0.
//
template<class T>
JsValueRef release_shared_resource(JsValueRef jshandle) {
    if (!jshandle) return 0;
    return wrapJs(release_shared_resource<T>(intValue(jshandle)));
}