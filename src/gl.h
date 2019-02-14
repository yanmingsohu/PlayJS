//
// 这个文件不要被非 gl 库所包含
// 宏定义是一整套的约定, 可以简化编码; 宏定义的约定互相依赖.
//
#pragma once
#define GLEW_STATIC

#include "vm.h"
#include "util.h"
#include "shared.h"
#include "glew/include/GL/glew.h"
#include "glfw/include/GLFW/glfw3.h"


#define GL_FUNC         JSS_FUNC
#define GL_CHK_ARG      JSS_CHK_ARG

//
// 更短的绑定, 绑定 js_name 的 js 函数为 name 属性到 gl 对象上.
// DEF_JS_FUNC(vm, vm, gl, _name, js_##_name); 引起函数名二次替换
//
#define GL_BIND(_name) \
    gl.put(#_name, vm->createFunction(&js_##_name, #_name, vm))



//
// GL 常量绑定到 js 对象上
//
#define GL_INT_ENUM(name) _const.put(#name, wrapJs((int)name));


LocalVal wrapJs(VM* vm, const GLFWvidmode* mode);
LocalVal wrapJs(VM* vm, int width, int height);
LocalVal wrapJs(GLFWgammaramp*);
LocalVal wrapJs(GLFWimage*);
LocalVal wrapJs(GLFWcursor*);
LocalVal wrapJs(GLFWgamepadstate*);


void installGLFWConst(VM* vm, LocalVal& _const);
void installGLCore(VM* vm, LocalVal& gl);
void installGLFW(VM*vm, LocalVal& gl);
