//
// 这个文件不要被非 gl 库所包含
// 宏定义是一整套的约定, 可以简化编码; 宏定义的约定互相依赖.
//
#pragma once

#include "glfw/include/GLFW/glfw3.h"
#include "vm.h"
#include "util.h"
#include "shared.h"


//
// 句柄换资源, 句柄无效则抛出 js 错误, 并立即从当前函数退出.
//
#define JS_HANDLE(_val, _arg, _type) \
    auto _val  = get_shared_resource<_type>(_arg); \
    if (!_val) { \
        pushException("bad arguments, "#_type" handle invalid"); \
        return 0; \
    }


//
// 方便访问变量
//
#define JVM ((VM*)_vm)


//
// 更短的函数头, 参数不变, 但固定:
// function js_name(callee, args, ac, info, _vm)
// args[0] 是 this 指针, 参数从 [1] 开始计算
//
#define GL_FUNC(_name, args, ac) \
    JS_FUNC_TPL(js_##_name, callee, args, ac, info, _vm)


//
// 更短的绑定, 绑定 js_name 的 js 函数为 name 属性到 gl 对象上.
//
#define GL_BIND(_name) \
    DEF_JS_FUNC(vm, vm, gl, _name, js_##_name);


//
// 更短的参数检查, 大于等于 count 参数数量, 否则 js 异常 (不需要计算 this).
// msg 包含 js 函数签名, 当异常时给予提示.
//
#define GL_CHK_ARG(count, msg) \
    if (ac < count+1) { \
        pushException("bad arguments, " #msg); \
        return 0; \
    }


//
// GL 常量绑定到 js 对象上
//
#define GL_INT_ENUM(name) _const.put(#name, wrapJs((int)name));


LocalVal wrapJs(VM* vm, const GLFWvidmode* mode);
LocalVal wrapJs(VM* vm, int width, int height);


void installGLFWConst(VM* vm, LocalVal& _const);
void installGLCore(VM* vm, LocalVal& gl);
void installGLFW(VM*vm, LocalVal& gl);