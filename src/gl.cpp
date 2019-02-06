#include "gl.h"

#include <atomic>
#include <system_error>


static const char* INIT_FAIL = "Cannot init GLFW";
static std::atomic<int> gl_count = 0;


template<>
class SharedResourceDeleter<GLFWwindow> {
public:
    virtual void operator()(GLFWwindow* w) {
        println("GLFWwindow closed", 0, LDEBUG);
        glfwDestroyWindow(w);
    }
};


template<>
class SharedResourceDeleter<GLFWmonitor> {
public:
    virtual void operator()(GLFWmonitor* w) {/* Do nothing */}
};


static inline LocalVal wrapJs(VM* vm, const GLFWvidmode* mode) {
    auto jmode = vm->createObject();
    jmode.put("width",          wrapJs(mode->width));
    jmode.put("height",         wrapJs(mode->height));
    jmode.put("redBits",        wrapJs(mode->redBits));
    jmode.put("greenBits",      wrapJs(mode->greenBits));
    jmode.put("blueBits",       wrapJs(mode->blueBits));
    jmode.put("refreshRate",    wrapJs(mode->refreshRate));
    return jmode;
}


static inline LocalVal wrapJs(VM* vm, int width, int height) {
    auto size = vm->createObject();
    size.put("width", wrapJs(width));
    size.put("height", wrapJs(height));
    return size;
}


GL_FUNC(glfwGetVersion, args, ac) {
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);

    LocalVal version = JVM->createObject();
    version.put("major", wrapJs(major), true);
    version.put("minor", wrapJs(minor), true);
    version.put("rev",   wrapJs(rev),   true);
    return version.js();
}


GL_FUNC(glfwGetVersionString, args, ac) {
    const char* version = glfwGetVersionString();
    return wrapJs(version);
}


GL_FUNC(glfwCreateWindow, args, ac) {
    GL_CHK_ARG(3, glfwCreateWindow(width, height, title, monitor, share));

    int width  = intValue(args[1], 640);
    int height = intValue(args[2], 480);
    std::string title = toString(args[3]);

    // 允许 moni/share 为空值
    auto moni  = get_shared_resource<GLFWmonitor>(ac > 4 ? args[4] : 0);
    auto share = get_shared_resource<GLFWwindow>(ac > 5 ? args[5] : 0);

    GLFWwindow* window = glfwCreateWindow(
        width, height, title.c_str(), moni.get(), share.get());

    if (!window) {
        pushException("create window fail");
        return 0;
    }
    return make_shared_js_handle(window);
}


GL_FUNC(glfwDestroyWindow, args, ac) {
    GL_CHK_ARG(1, glfwDestroyWindow(window));
    return release_shared_resource<GLFWwindow>(args[1]);
}


GL_FUNC(glfwMakeContextCurrent, args, ac) {
    GL_CHK_ARG(1, glfwMakeContextCurrent(window));
    JS_HANDLE(win, args[1], GLFWwindow);
    glfwMakeContextCurrent(win.get());
    //gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    return 0;
}


GL_FUNC(glfwGetPrimaryMonitor, args, ac) {
    GLFWmonitor* m = glfwGetPrimaryMonitor();
    return make_shared_js_handle(m);
}


GL_FUNC(glfwSetWindowMonitor, args, ac) {
    GL_CHK_ARG(7, glfwSetWindowMonitor(window, monitor, xpos, ypos, width, height, refreshRate));
    JS_HANDLE(win, args[1], GLFWwindow);
    auto moni = get_shared_resource<GLFWmonitor>(args[2]);
    int xpos  = intValue(args[3]);
    int ypos  = intValue(args[4]);
    int width = intValue(args[5]);
    int height= intValue(args[6]);
    int ref   = intValue(args[7]);
    glfwSetWindowMonitor(win.get(), moni.get(), xpos, ypos, width, height, ref);
    return 0;
}


GL_FUNC(glfwGetWindowMonitor, args, ac) {
    GL_CHK_ARG(1, glfwGetWindowMonitor(window));
    JS_HANDLE(win, args[1], GLFWwindow);
    GLFWmonitor* moni = glfwGetWindowMonitor(win.get());
    if (!moni) {
        return 0;
    }
    return make_shared_js_handle(moni);
}


GL_FUNC(glfwGetVideoMode, args, ac) {
    // 可以为空
    auto moni = get_shared_resource<GLFWmonitor>(ac > 1 ? args[1] : 0);
    const GLFWvidmode* mode = glfwGetVideoMode(moni.get());
    return wrapJs((VM*)_vm, mode);
}


GL_FUNC(glfwSetWindowSize, args, ac) {
    GL_CHK_ARG(3, glfwSetWindowSize(window, width, height));
    JS_HANDLE(win, args[1], GLFWwindow);
    int width  = intValue(args[2]);
    int height = intValue(args[3]);
    glfwSetWindowSize(win.get(), width, height);
    return 0;
}


GL_FUNC(glfwGetWindowSize, args, ac) {
    GL_CHK_ARG(1, glfwGetWindowSize(window));
    JS_HANDLE(win, args[1], GLFWwindow);
    int width, height;
    glfwGetWindowSize(win.get(), &width, &height);
    return wrapJs(JVM, width, height);
}


GL_FUNC(glfwGetFramebufferSize, args, ac) {
    GL_CHK_ARG(1, glfwGetFramebufferSize(window));
    JS_HANDLE(win, args[1], GLFWwindow);
    int width, height;
    glfwGetFramebufferSize(win.get(), &width, &height);
    return wrapJs(JVM, width, height);
}


GL_FUNC(glfwSetWindowAspectRatio, args, ac)  {
    GL_CHK_ARG(3, glfwSetWindowAspectRatio(window, numer, denom));
    JS_HANDLE(win, args[1], GLFWwindow);
    int n = intValue(args[2], GLFW_DONT_CARE);
    int d = intValue(args[3], GLFW_DONT_CARE);
    glfwSetWindowAspectRatio(win.get(), n, d);
    return 0;
}


GL_FUNC(glfwSetWindowPos, args, ac) {
    GL_CHK_ARG(3, lfwSetWindowPos(window, x, y));
    JS_HANDLE(win, args[1], GLFWwindow);
    int x = intValue(args[2], GLFW_DONT_CARE);
    int y = intValue(args[3], GLFW_DONT_CARE);
    glfwSetWindowPos(win.get(), x, y);
    return 0;
}


GL_FUNC(glfwWindowHint, args, ac) {
    GL_CHK_ARG(2, glfwWindowHint(hint, value));
    int hint = intValue(args[1]);
    int val  = intValue(args[2]);
    glfwWindowHint(hint, val);
    return 0;
}


GL_FUNC(glfwSwapBuffers, args, ac) {
    GL_CHK_ARG(1, glfwSwapBuffers(window));
    JS_HANDLE(win, args[1], GLFWwindow);
    glfwSwapBuffers(win.get());
    return 0;
}


GL_FUNC(glfwSwapInterval, args, ac) {
    GL_CHK_ARG(1, glfwSwapInterval(interval));
    int interval = intValue(args[1]);
    glfwSwapInterval(interval);
    return 0;
}


GL_FUNC(glfwPollEvents, args, ac) {
    glfwPollEvents();
    return 0;
}


GL_FUNC(glfwWaitEvents, args, ac) {
    glfwWaitEvents();
    return 0;
}


GL_FUNC(glfwWaitEventsTimeout, args, ac) {
    GL_CHK_ARG(1, glfwWaitEventsTimeout(timeout_seconds));
    int seconds = intValue(args[1], 1);
    glfwWaitEventsTimeout(seconds);
    return 0;
}


GL_FUNC(glfwGetTime, args, ac) {
    return wrapJs(glfwGetTime());
}


GL_FUNC(glfwWindowShouldClose, args, ac) {
    GL_CHK_ARG(1, glfwWindowShouldClose(window));
    JS_HANDLE(win, args[1], GLFWwindow);
    int f = glfwWindowShouldClose(win.get());
    return wrapJs(f);
}


GL_FUNC(glfwSetWindowTitle, args, ac) {
    GL_CHK_ARG(2, glfwSetWindowTitle(window, title));
    JS_HANDLE(win, args[1], GLFWwindow);
    std::string title = toString(args[2]);
    glfwSetWindowTitle(win.get(), title.c_str());
    return 0;
}


static void bind(VM*vm, LocalVal& gl) {
    GL_BIND(glfwGetVersion);
    GL_BIND(glfwGetVersionString);

    GL_BIND(glfwCreateWindow);
    GL_BIND(glfwDestroyWindow);
    GL_BIND(glfwSetWindowTitle);
    GL_BIND(glfwGetWindowMonitor);
    GL_BIND(glfwMakeContextCurrent);

    GL_BIND(glfwGetPrimaryMonitor);
    GL_BIND(glfwSetWindowMonitor);
    GL_BIND(glfwGetVideoMode);
    GL_BIND(glfwSetWindowSize);
    GL_BIND(glfwGetWindowSize);
    GL_BIND(glfwGetFramebufferSize);
    GL_BIND(glfwSetWindowAspectRatio);
    GL_BIND(glfwSetWindowPos);

    GL_BIND(glfwSwapBuffers);
    GL_BIND(glfwSwapInterval);
    GL_BIND(glfwPollEvents);
    GL_BIND(glfwWaitEvents);
    GL_BIND(glfwWaitEventsTimeout);
    GL_BIND(glfwGetTime);
    GL_BIND(glfwWindowShouldClose);
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
    bind(vm, gl);
}


void unstallGL(VM* vm) {
    if (--gl_count <= 0) {
        gl_count = 0;
        glfwTerminate();
    }
}
