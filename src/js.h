#pragma once


//
// 在 obj(LocalVal) 对象上绑定名字为 name 的方法 func_ptr(本地cpp函数指针)
// 必要时附加扩展数据 ext_data, 或为 NULL
//
#define DEF_JS_FUNC(vm, ext_data, obj, jsname, func_ptr) \
    obj.put(#jsname, vm->createFunction(&func_ptr, #jsname, ext_data))


//
// 用 val_name 绑定 js 全局变量, 创建 cpp 的变量句柄 val_name
//
#define DEF_GLOBAL(vm, val_name) \
    LocalVal val_name = vm->createObject(); \
    vm->getGlobal().put(#val_name, val_name)


//
// 生成 js 本机方法函数头.
// args[0] 是 this, args[1] 是第一个参数.
//
#define JS_FUNC_TPL(name, callee, args, argc, info, vm) \
    static JsValueRef name( \
        JsValueRef callee, JsValueRef *args, unsigned short argc, \
        JsNativeFunctionInfo *info, void *vm)


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
#define JSS_FUNC(_name, args, ac) \
    JS_FUNC_TPL(js_##_name, callee, args, ac, info, _vm)


//
// 更短的绑定, 绑定 js_name 的 js 函数为 name 属性到 gl 对象上.
// DEF_JS_FUNC(vm, vm, gl, _name, js_##_name); 引起函数名二次替换
//
#define JSS_BIND(_name) \
    mod.put(#_name, vm->createFunction(&js_##_name, #_name, vm))


//
// 将属性绑定到模块, _val 必须是简单类型或字符串
//
#define JSS_ATTR(_name, _val) \
    mod.put(#_name, wrapJs(_val))


//
// 创建模块, 并绑定到全局
//
#define JSS_MOD(_name) \
    LocalVal mod = vm->createObject(); \
    vm->getGlobal().put(#_name, mod)


//
// 更短的参数检查, 大于等于 count 参数数量, 否则 js 异常 (不需要计算 this).
// msg 包含 js 函数签名, 当异常时给予提示.
//
#define JSS_CHK_ARG(count, msg) \
    if (ac < count+1) { \
        pushException("bad arguments, " #msg); \
        return 0; \
    }


//
// 定义一个函数, 用于js模块初始化
//
#define JSS_INIT_MODULE(name)  void name(VM* vm)


//
// 定义一个函数, 用于卸载 js 模块.
//
#define JSS_UNINIT_MODULE(name) void name(VM* vm)