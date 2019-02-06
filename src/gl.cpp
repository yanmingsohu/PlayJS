#include "gl.h"
#include "../src-auto/glauto.h"

#include <atomic>
#include <system_error>


static const char* INIT_FAIL = "Cannot init GLFW";
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


static void gl_error_callback(int error, const char* desc) {
    println(desc, 0, LERROR);
}


void installGL(VM* vm) {
    if (gl_count == 0) {
        glfwSetErrorCallback(&gl_error_callback);
        
        if (GLFW_FALSE == glfwInit())
            throw std::runtime_error(INIT_FAIL);
    }
    ++gl_count;

    DEF_GLOBAL(vm, gl);
    auto _const = vm->createObject();

    installGLFWConst(vm, _const);
    installGLCore(vm, gl);
    installGLFW(vm, gl);
    INCLUDE_AUTO_GL_CODE(vm, gl, _const);
}


void unstallGL(VM* vm) {
    if (--gl_count <= 0) {
        gl_count = 0;
        glfwTerminate();
    }
}
