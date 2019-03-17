#include "gl.h"
#include "../src-auto/glauto.h"

#include <atomic>
#include <system_error>

//
// 下载并编译依赖 glew 在 `/deps/glew` 目录中
//
#pragma comment(lib, "glew32s.lib")
#ifdef WIN32
#pragma comment(lib, "Opengl32.lib")
#endif


static std::atomic<int> gl_count = 0;


LocalVal wrapJs(VM* vm, const GLFWvidmode* mode) {
    auto jmode = vm->createObject();
    jmode.put("width",          wrapJs(mode->width));
    jmode.put("height",         wrapJs(mode->height));
    jmode.put("redBits",        wrapJs(mode->redBits));
    jmode.put("greenBits",      wrapJs(mode->greenBits));
    jmode.put("blueBits",       wrapJs(mode->blueBits));
    jmode.put("refreshRate",    wrapJs(mode->refreshRate));
    return jmode;
}


LocalVal wrapJs(VM* vm, int width, int height) {
    auto size = vm->createObject();
    size.put("width", wrapJs(width));
    size.put("height", wrapJs(height));
    return size;
}


LocalVal wrapJs(GLFWgammaramp* p) {
    return make_shared_js_handle(p);
}


LocalVal wrapJs(GLFWimage* p) {
    return make_shared_js_handle(p);
}


LocalVal wrapJs(GLFWcursor* p) {
    return make_shared_js_handle(p);
}


LocalVal wrapJs(GLFWgamepadstate* p) {
    return make_shared_js_handle(p);
}


static void gl_error_callback(int error, const char* desc) {
    println(desc, 0, LERROR);
}


static bool initOpenGlSystem(VM* vm) {
    if (GLFW_FALSE == glfwInit()) {
        println("Cannot init GLFW", vm->thread(), LERROR);
        return false;
    }

    glfwSetErrorCallback(&gl_error_callback);
    return true;
}


void installGL(VM* vm) {
    if (gl_count == 0) {
        if (! initOpenGlSystem(vm)) return;
    }
    ++gl_count;

    DEF_GLOBAL(vm, gl);

    INCLUDE_AUTO_GL_CODE(vm, gl, gl);
    installGLFWConst(vm, gl);
    installGLCore(vm, gl);
    installGLFW(vm, gl);
}


void unstallGL(VM* vm) {
    if (--gl_count <= 0) {
        gl_count = 0;
        glfwTerminate();
    }
}
