// 
// 2019-02-07 16:38:08
// create from D:\game\sanguo7\src-auto\generate-code.js
// 
// D:\game\sanguo7\deps\glfw\include\GLFW\glfw3.h
//
#include "../src/gl.h"
#include "../src/gldeleter.h"


// GL_FUNC(glfwInit, args, ac) {
    // auto __return_glfwInit = glfwInit();
    // return wrapJs(__return_glfwInit);
// }


// GL_FUNC(glfwTerminate, args, ac) {
    // glfwTerminate();
    // return 0;
// }


GL_FUNC(glfwInitHint, args, ac) {
    GL_CHK_ARG(2, glfwInitHint(hint, value));
    int __gen_hint = intValue(args[1]);
    int __gen_value = intValue(args[2]);
    glfwInitHint(__gen_hint, __gen_value);
    return 0;
}


// GL_FUNC(glfwGetVersion, args, ac) {
    // GL_CHK_ARG(3, glfwGetVersion(major, minor, rev));
    // int __gen_major = 0;
    // int __gen_minor = 0;
    // int __gen_rev = 0;
    // glfwGetVersion(&__gen_major, &__gen_minor, &__gen_rev);
    // auto __retjs = JVM->createObject();
    // __retjs.put("major", wrapJs(__gen_major));
    // __retjs.put("minor", wrapJs(__gen_minor));
    // __retjs.put("rev", wrapJs(__gen_rev));
    // return __retjs;
// }


// GL_FUNC(glfwGetVersionString, args, ac) {
    // auto __return_glfwGetVersionString = glfwGetVersionString();
    // return wrapJs(__return_glfwGetVersionString);
// }


GL_FUNC(glfwGetError, args, ac) {
    GL_CHK_ARG(1, glfwGetError(description));
    const char *__gen_description = 0;
    auto __return_glfwGetError = glfwGetError(&__gen_description);
    return wrapJs(__gen_description);
}


// GL_FUNC(glfwSetErrorCallback, args, ac) {
    // GL_CHK_ARG(1, glfwSetErrorCallback(cbfun));
    // pushException("Not implemented function glfwSetErrorCallback(...)");
    // return 0;
// }


GL_FUNC(glfwGetMonitors, args, ac) {
    GL_CHK_ARG(1, glfwGetMonitors(count));
    int __gen_count = 0;
    auto __return_glfwGetMonitors = glfwGetMonitors(&__gen_count);
    return wrapJs(__gen_count);
}


// GL_FUNC(glfwGetPrimaryMonitor, args, ac) {
    // auto __return_glfwGetPrimaryMonitor = glfwGetPrimaryMonitor();
    // return wrapJs(__return_glfwGetPrimaryMonitor);
// }


GL_FUNC(glfwGetMonitorPos, args, ac) {
    GL_CHK_ARG(3, glfwGetMonitorPos(monitor, xpos, ypos));
    JS_HANDLE(__gen_monitor, args[1], GLFWmonitor);
    int __gen_xpos = 0;
    int __gen_ypos = 0;
    glfwGetMonitorPos(__gen_monitor.get(), &__gen_xpos, &__gen_ypos);
    auto __retjs = JVM->createObject();
    __retjs.put("xpos", wrapJs(__gen_xpos));
    __retjs.put("ypos", wrapJs(__gen_ypos));
    return __retjs;
}


GL_FUNC(glfwGetMonitorPhysicalSize, args, ac) {
    GL_CHK_ARG(3, glfwGetMonitorPhysicalSize(monitor, widthMM, heightMM));
    JS_HANDLE(__gen_monitor, args[1], GLFWmonitor);
    int __gen_widthMM = 0;
    int __gen_heightMM = 0;
    glfwGetMonitorPhysicalSize(__gen_monitor.get(), &__gen_widthMM, &__gen_heightMM);
    auto __retjs = JVM->createObject();
    __retjs.put("widthMM", wrapJs(__gen_widthMM));
    __retjs.put("heightMM", wrapJs(__gen_heightMM));
    return __retjs;
}


GL_FUNC(glfwGetMonitorContentScale, args, ac) {
    GL_CHK_ARG(3, glfwGetMonitorContentScale(monitor, xscale, yscale));
    JS_HANDLE(__gen_monitor, args[1], GLFWmonitor);
    float __gen_xscale = 0;
    float __gen_yscale = 0;
    glfwGetMonitorContentScale(__gen_monitor.get(), &__gen_xscale, &__gen_yscale);
    auto __retjs = JVM->createObject();
    __retjs.put("xscale", wrapJs(__gen_xscale));
    __retjs.put("yscale", wrapJs(__gen_yscale));
    return __retjs;
}


GL_FUNC(glfwGetMonitorName, args, ac) {
    GL_CHK_ARG(1, glfwGetMonitorName(monitor));
    JS_HANDLE(__gen_monitor, args[1], GLFWmonitor);
    auto __return_glfwGetMonitorName = glfwGetMonitorName(__gen_monitor.get());
    return wrapJs(__return_glfwGetMonitorName);
}


// GL_FUNC(glfwSetMonitorUserPointer, args, ac) {
    // GL_CHK_ARG(2, glfwSetMonitorUserPointer(monitor, pointer));
    // pushException("Not implemented function glfwSetMonitorUserPointer(...)");
    // return 0;
// }


// GL_FUNC(glfwGetMonitorUserPointer, args, ac) {
    // GL_CHK_ARG(1, glfwGetMonitorUserPointer(monitor));
    // JS_HANDLE(__gen_monitor, args[1], GLFWmonitor);
    // auto __return_glfwGetMonitorUserPointer = glfwGetMonitorUserPointer(__gen_monitor.get());
    // return wrapJs(__return_glfwGetMonitorUserPointer);
// }


// GL_FUNC(glfwSetMonitorCallback, args, ac) {
    // GL_CHK_ARG(1, glfwSetMonitorCallback(cbfun));
    // pushException("Not implemented function glfwSetMonitorCallback(...)");
    // return 0;
// }


GL_FUNC(glfwGetVideoModes, args, ac) {
    GL_CHK_ARG(2, glfwGetVideoModes(monitor, count));
    JS_HANDLE(__gen_monitor, args[1], GLFWmonitor);
    int __gen_count = 0;
    auto __return_glfwGetVideoModes = glfwGetVideoModes(__gen_monitor.get(), &__gen_count);
    return wrapJs(__gen_count);
}


// GL_FUNC(glfwGetVideoMode, args, ac) {
    // GL_CHK_ARG(1, glfwGetVideoMode(monitor));
    // JS_HANDLE(__gen_monitor, args[1], GLFWmonitor);
    // auto __return_glfwGetVideoMode = glfwGetVideoMode(__gen_monitor.get());
    // return wrapJs(__return_glfwGetVideoMode);
// }


GL_FUNC(glfwSetGamma, args, ac) {
    GL_CHK_ARG(2, glfwSetGamma(monitor, gamma));
    JS_HANDLE(__gen_monitor, args[1], GLFWmonitor);
    float __gen_gamma = floatValue(args[2]);
    glfwSetGamma(__gen_monitor.get(), __gen_gamma);
    return 0;
}


GL_FUNC(glfwGetGammaRamp, args, ac) {
    GL_CHK_ARG(1, glfwGetGammaRamp(monitor));
    JS_HANDLE(__gen_monitor, args[1], GLFWmonitor);
    auto __return_glfwGetGammaRamp = glfwGetGammaRamp(__gen_monitor.get());
    return wrapJs(__return_glfwGetGammaRamp);
}


GL_FUNC(glfwSetGammaRamp, args, ac) {
    GL_CHK_ARG(2, glfwSetGammaRamp(monitor, ramp));
    JS_HANDLE(__gen_monitor, args[1], GLFWmonitor);
    JS_HANDLE(__gen_ramp, args[2], GLFWgammaramp);
    glfwSetGammaRamp(__gen_monitor.get(), __gen_ramp.get());
    return 0;
}


GL_FUNC(glfwDefaultWindowHints, args, ac) {
    glfwDefaultWindowHints();
    return 0;
}


GL_FUNC(glfwWindowHint, args, ac) {
    GL_CHK_ARG(2, glfwWindowHint(hint, value));
    int __gen_hint = intValue(args[1]);
    int __gen_value = intValue(args[2]);
    glfwWindowHint(__gen_hint, __gen_value);
    return 0;
}


GL_FUNC(glfwWindowHintString, args, ac) {
    GL_CHK_ARG(2, glfwWindowHintString(hint, value));
    int __gen_hint = intValue(args[1]);
    std::string ____gen_value = toString(args[2]);
               const char* __gen_value = ____gen_value.c_str();
    glfwWindowHintString(__gen_hint, __gen_value);
    return 0;
}


// GL_FUNC(glfwCreateWindow, args, ac) {
    // GL_CHK_ARG(5, glfwCreateWindow(width, height, title, monitor, share));
    // int __gen_width = intValue(args[1]);
    // int __gen_height = intValue(args[2]);
    // std::string ____gen_title = toString(args[3]);
    //            const char* __gen_title = ____gen_title.c_str();
    // JS_HANDLE(__gen_monitor, args[4], GLFWmonitor);
    // JS_HANDLE(__gen_share, args[5], GLFWwindow);
    // auto __return_glfwCreateWindow = glfwCreateWindow(__gen_width, __gen_height, __gen_title, __gen_monitor.get(), __gen_share.get());
    // return wrapJs(__return_glfwCreateWindow);
// }


// GL_FUNC(glfwDestroyWindow, args, ac) {
    // GL_CHK_ARG(1, glfwDestroyWindow(window));
    // JS_HANDLE(__gen_window, args[1], GLFWwindow);
    // glfwDestroyWindow(__gen_window.get());
    // return 0;
// }


// GL_FUNC(glfwWindowShouldClose, args, ac) {
    // GL_CHK_ARG(1, glfwWindowShouldClose(window));
    // JS_HANDLE(__gen_window, args[1], GLFWwindow);
    // auto __return_glfwWindowShouldClose = glfwWindowShouldClose(__gen_window.get());
    // return wrapJs(__return_glfwWindowShouldClose);
// }


GL_FUNC(glfwSetWindowShouldClose, args, ac) {
    GL_CHK_ARG(2, glfwSetWindowShouldClose(window, value));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    int __gen_value = intValue(args[2]);
    glfwSetWindowShouldClose(__gen_window.get(), __gen_value);
    return 0;
}


// GL_FUNC(glfwSetWindowTitle, args, ac) {
    // GL_CHK_ARG(2, glfwSetWindowTitle(window, title));
    // JS_HANDLE(__gen_window, args[1], GLFWwindow);
    // std::string ____gen_title = toString(args[2]);
    //            const char* __gen_title = ____gen_title.c_str();
    // glfwSetWindowTitle(__gen_window.get(), __gen_title);
    // return 0;
// }


GL_FUNC(glfwSetWindowIcon, args, ac) {
    GL_CHK_ARG(3, glfwSetWindowIcon(window, count, images));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    int __gen_count = intValue(args[2]);
    JS_HANDLE(__gen_images, args[3], GLFWimage);
    glfwSetWindowIcon(__gen_window.get(), __gen_count, __gen_images.get());
    return 0;
}


GL_FUNC(glfwGetWindowPos, args, ac) {
    GL_CHK_ARG(3, glfwGetWindowPos(window, xpos, ypos));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    int __gen_xpos = 0;
    int __gen_ypos = 0;
    glfwGetWindowPos(__gen_window.get(), &__gen_xpos, &__gen_ypos);
    auto __retjs = JVM->createObject();
    __retjs.put("xpos", wrapJs(__gen_xpos));
    __retjs.put("ypos", wrapJs(__gen_ypos));
    return __retjs;
}


// GL_FUNC(glfwSetWindowPos, args, ac) {
    // GL_CHK_ARG(3, glfwSetWindowPos(window, xpos, ypos));
    // JS_HANDLE(__gen_window, args[1], GLFWwindow);
    // int __gen_xpos = intValue(args[2]);
    // int __gen_ypos = intValue(args[3]);
    // glfwSetWindowPos(__gen_window.get(), __gen_xpos, __gen_ypos);
    // return 0;
// }


// GL_FUNC(glfwGetWindowSize, args, ac) {
    // GL_CHK_ARG(3, glfwGetWindowSize(window, width, height));
    // JS_HANDLE(__gen_window, args[1], GLFWwindow);
    // int __gen_width = 0;
    // int __gen_height = 0;
    // glfwGetWindowSize(__gen_window.get(), &__gen_width, &__gen_height);
    // auto __retjs = JVM->createObject();
    // __retjs.put("width", wrapJs(__gen_width));
    // __retjs.put("height", wrapJs(__gen_height));
    // return __retjs;
// }


GL_FUNC(glfwSetWindowSizeLimits, args, ac) {
    GL_CHK_ARG(5, glfwSetWindowSizeLimits(window, minwidth, minheight, maxwidth, maxheight));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    int __gen_minwidth = intValue(args[2]);
    int __gen_minheight = intValue(args[3]);
    int __gen_maxwidth = intValue(args[4]);
    int __gen_maxheight = intValue(args[5]);
    glfwSetWindowSizeLimits(__gen_window.get(), __gen_minwidth, __gen_minheight, __gen_maxwidth, __gen_maxheight);
    return 0;
}


// GL_FUNC(glfwSetWindowAspectRatio, args, ac) {
    // GL_CHK_ARG(3, glfwSetWindowAspectRatio(window, numer, denom));
    // JS_HANDLE(__gen_window, args[1], GLFWwindow);
    // int __gen_numer = intValue(args[2]);
    // int __gen_denom = intValue(args[3]);
    // glfwSetWindowAspectRatio(__gen_window.get(), __gen_numer, __gen_denom);
    // return 0;
// }


// GL_FUNC(glfwSetWindowSize, args, ac) {
    // GL_CHK_ARG(3, glfwSetWindowSize(window, width, height));
    // JS_HANDLE(__gen_window, args[1], GLFWwindow);
    // int __gen_width = intValue(args[2]);
    // int __gen_height = intValue(args[3]);
    // glfwSetWindowSize(__gen_window.get(), __gen_width, __gen_height);
    // return 0;
// }


// GL_FUNC(glfwGetFramebufferSize, args, ac) {
    // GL_CHK_ARG(3, glfwGetFramebufferSize(window, width, height));
    // JS_HANDLE(__gen_window, args[1], GLFWwindow);
    // int __gen_width = 0;
    // int __gen_height = 0;
    // glfwGetFramebufferSize(__gen_window.get(), &__gen_width, &__gen_height);
    // auto __retjs = JVM->createObject();
    // __retjs.put("width", wrapJs(__gen_width));
    // __retjs.put("height", wrapJs(__gen_height));
    // return __retjs;
// }


GL_FUNC(glfwGetWindowFrameSize, args, ac) {
    GL_CHK_ARG(5, glfwGetWindowFrameSize(window, left, top, right, bottom));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    int __gen_left = 0;
    int __gen_top = 0;
    int __gen_right = 0;
    int __gen_bottom = 0;
    glfwGetWindowFrameSize(__gen_window.get(), &__gen_left, &__gen_top, &__gen_right, &__gen_bottom);
    auto __retjs = JVM->createObject();
    __retjs.put("left", wrapJs(__gen_left));
    __retjs.put("top", wrapJs(__gen_top));
    __retjs.put("right", wrapJs(__gen_right));
    __retjs.put("bottom", wrapJs(__gen_bottom));
    return __retjs;
}


GL_FUNC(glfwGetWindowContentScale, args, ac) {
    GL_CHK_ARG(3, glfwGetWindowContentScale(window, xscale, yscale));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    float __gen_xscale = 0;
    float __gen_yscale = 0;
    glfwGetWindowContentScale(__gen_window.get(), &__gen_xscale, &__gen_yscale);
    auto __retjs = JVM->createObject();
    __retjs.put("xscale", wrapJs(__gen_xscale));
    __retjs.put("yscale", wrapJs(__gen_yscale));
    return __retjs;
}


GL_FUNC(glfwGetWindowOpacity, args, ac) {
    GL_CHK_ARG(1, glfwGetWindowOpacity(window));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    auto __return_glfwGetWindowOpacity = glfwGetWindowOpacity(__gen_window.get());
    return wrapJs(__return_glfwGetWindowOpacity);
}


GL_FUNC(glfwSetWindowOpacity, args, ac) {
    GL_CHK_ARG(2, glfwSetWindowOpacity(window, opacity));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    float __gen_opacity = floatValue(args[2]);
    glfwSetWindowOpacity(__gen_window.get(), __gen_opacity);
    return 0;
}


GL_FUNC(glfwIconifyWindow, args, ac) {
    GL_CHK_ARG(1, glfwIconifyWindow(window));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    glfwIconifyWindow(__gen_window.get());
    return 0;
}


GL_FUNC(glfwRestoreWindow, args, ac) {
    GL_CHK_ARG(1, glfwRestoreWindow(window));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    glfwRestoreWindow(__gen_window.get());
    return 0;
}


GL_FUNC(glfwMaximizeWindow, args, ac) {
    GL_CHK_ARG(1, glfwMaximizeWindow(window));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    glfwMaximizeWindow(__gen_window.get());
    return 0;
}


GL_FUNC(glfwShowWindow, args, ac) {
    GL_CHK_ARG(1, glfwShowWindow(window));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    glfwShowWindow(__gen_window.get());
    return 0;
}


GL_FUNC(glfwHideWindow, args, ac) {
    GL_CHK_ARG(1, glfwHideWindow(window));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    glfwHideWindow(__gen_window.get());
    return 0;
}


GL_FUNC(glfwFocusWindow, args, ac) {
    GL_CHK_ARG(1, glfwFocusWindow(window));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    glfwFocusWindow(__gen_window.get());
    return 0;
}


GL_FUNC(glfwRequestWindowAttention, args, ac) {
    GL_CHK_ARG(1, glfwRequestWindowAttention(window));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    glfwRequestWindowAttention(__gen_window.get());
    return 0;
}


// GL_FUNC(glfwGetWindowMonitor, args, ac) {
    // GL_CHK_ARG(1, glfwGetWindowMonitor(window));
    // JS_HANDLE(__gen_window, args[1], GLFWwindow);
    // auto __return_glfwGetWindowMonitor = glfwGetWindowMonitor(__gen_window.get());
    // return wrapJs(__return_glfwGetWindowMonitor);
// }


// GL_FUNC(glfwSetWindowMonitor, args, ac) {
    // GL_CHK_ARG(7, glfwSetWindowMonitor(window, monitor, xpos, ypos, width, height, refreshRate));
    // JS_HANDLE(__gen_window, args[1], GLFWwindow);
    // JS_HANDLE(__gen_monitor, args[2], GLFWmonitor);
    // int __gen_xpos = intValue(args[3]);
    // int __gen_ypos = intValue(args[4]);
    // int __gen_width = intValue(args[5]);
    // int __gen_height = intValue(args[6]);
    // int __gen_refreshRate = intValue(args[7]);
    // glfwSetWindowMonitor(__gen_window.get(), __gen_monitor.get(), __gen_xpos, __gen_ypos, __gen_width, __gen_height, __gen_refreshRate);
    // return 0;
// }


GL_FUNC(glfwGetWindowAttrib, args, ac) {
    GL_CHK_ARG(2, glfwGetWindowAttrib(window, attrib));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    int __gen_attrib = intValue(args[2]);
    auto __return_glfwGetWindowAttrib = glfwGetWindowAttrib(__gen_window.get(), __gen_attrib);
    return wrapJs(__return_glfwGetWindowAttrib);
}


GL_FUNC(glfwSetWindowAttrib, args, ac) {
    GL_CHK_ARG(3, glfwSetWindowAttrib(window, attrib, value));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    int __gen_attrib = intValue(args[2]);
    int __gen_value = intValue(args[3]);
    glfwSetWindowAttrib(__gen_window.get(), __gen_attrib, __gen_value);
    return 0;
}


// GL_FUNC(glfwSetWindowUserPointer, args, ac) {
    // GL_CHK_ARG(2, glfwSetWindowUserPointer(window, pointer));
    // pushException("Not implemented function glfwSetWindowUserPointer(...)");
    // return 0;
// }


GL_FUNC(glfwGetWindowUserPointer, args, ac) {
    GL_CHK_ARG(1, glfwGetWindowUserPointer(window));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    auto __return_glfwGetWindowUserPointer = glfwGetWindowUserPointer(__gen_window.get());
    return wrapJs(__return_glfwGetWindowUserPointer);
}


// GL_FUNC(glfwSetWindowPosCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetWindowPosCallback(window, cbfun));
    // pushException("Not implemented function glfwSetWindowPosCallback(...)");
    // return 0;
// }


// GL_FUNC(glfwSetWindowSizeCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetWindowSizeCallback(window, cbfun));
    // pushException("Not implemented function glfwSetWindowSizeCallback(...)");
    // return 0;
// }


// GL_FUNC(glfwSetWindowCloseCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetWindowCloseCallback(window, cbfun));
    // pushException("Not implemented function glfwSetWindowCloseCallback(...)");
    // return 0;
// }


// GL_FUNC(glfwSetWindowRefreshCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetWindowRefreshCallback(window, cbfun));
    // pushException("Not implemented function glfwSetWindowRefreshCallback(...)");
    // return 0;
// }


// GL_FUNC(glfwSetWindowFocusCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetWindowFocusCallback(window, cbfun));
    // pushException("Not implemented function glfwSetWindowFocusCallback(...)");
    // return 0;
// }


// GL_FUNC(glfwSetWindowIconifyCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetWindowIconifyCallback(window, cbfun));
    // pushException("Not implemented function glfwSetWindowIconifyCallback(...)");
    // return 0;
// }


// GL_FUNC(glfwSetWindowMaximizeCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetWindowMaximizeCallback(window, cbfun));
    // pushException("Not implemented function glfwSetWindowMaximizeCallback(...)");
    // return 0;
// }


// GL_FUNC(glfwSetFramebufferSizeCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetFramebufferSizeCallback(window, cbfun));
    // pushException("Not implemented function glfwSetFramebufferSizeCallback(...)");
    // return 0;
// }


// GL_FUNC(glfwSetWindowContentScaleCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetWindowContentScaleCallback(window, cbfun));
    // pushException("Not implemented function glfwSetWindowContentScaleCallback(...)");
    // return 0;
// }


// GL_FUNC(glfwPollEvents, args, ac) {
    // glfwPollEvents();
    // return 0;
// }


// GL_FUNC(glfwWaitEvents, args, ac) {
    // glfwWaitEvents();
    // return 0;
// }


// GL_FUNC(glfwWaitEventsTimeout, args, ac) {
    // GL_CHK_ARG(1, glfwWaitEventsTimeout(timeout));
    // double __gen_timeout = doubleValue(args[1]);
    // glfwWaitEventsTimeout(__gen_timeout);
    // return 0;
// }


GL_FUNC(glfwPostEmptyEvent, args, ac) {
    glfwPostEmptyEvent();
    return 0;
}


GL_FUNC(glfwGetInputMode, args, ac) {
    GL_CHK_ARG(2, glfwGetInputMode(window, mode));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    int __gen_mode = intValue(args[2]);
    auto __return_glfwGetInputMode = glfwGetInputMode(__gen_window.get(), __gen_mode);
    return wrapJs(__return_glfwGetInputMode);
}


GL_FUNC(glfwSetInputMode, args, ac) {
    GL_CHK_ARG(3, glfwSetInputMode(window, mode, value));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    int __gen_mode = intValue(args[2]);
    int __gen_value = intValue(args[3]);
    glfwSetInputMode(__gen_window.get(), __gen_mode, __gen_value);
    return 0;
}


GL_FUNC(glfwGetKeyName, args, ac) {
    GL_CHK_ARG(2, glfwGetKeyName(key, scancode));
    int __gen_key = intValue(args[1]);
    int __gen_scancode = intValue(args[2]);
    auto __return_glfwGetKeyName = glfwGetKeyName(__gen_key, __gen_scancode);
    return wrapJs(__return_glfwGetKeyName);
}


GL_FUNC(glfwGetKeyScancode, args, ac) {
    GL_CHK_ARG(1, glfwGetKeyScancode(key));
    int __gen_key = intValue(args[1]);
    auto __return_glfwGetKeyScancode = glfwGetKeyScancode(__gen_key);
    return wrapJs(__return_glfwGetKeyScancode);
}


GL_FUNC(glfwGetKey, args, ac) {
    GL_CHK_ARG(2, glfwGetKey(window, key));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    int __gen_key = intValue(args[2]);
    auto __return_glfwGetKey = glfwGetKey(__gen_window.get(), __gen_key);
    return wrapJs(__return_glfwGetKey);
}


GL_FUNC(glfwGetMouseButton, args, ac) {
    GL_CHK_ARG(2, glfwGetMouseButton(window, button));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    int __gen_button = intValue(args[2]);
    auto __return_glfwGetMouseButton = glfwGetMouseButton(__gen_window.get(), __gen_button);
    return wrapJs(__return_glfwGetMouseButton);
}


GL_FUNC(glfwGetCursorPos, args, ac) {
    GL_CHK_ARG(3, glfwGetCursorPos(window, xpos, ypos));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    double __gen_xpos = 0;
    double __gen_ypos = 0;
    glfwGetCursorPos(__gen_window.get(), &__gen_xpos, &__gen_ypos);
    auto __retjs = JVM->createObject();
    __retjs.put("xpos", wrapJs(__gen_xpos));
    __retjs.put("ypos", wrapJs(__gen_ypos));
    return __retjs;
}


GL_FUNC(glfwSetCursorPos, args, ac) {
    GL_CHK_ARG(3, glfwSetCursorPos(window, xpos, ypos));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    double __gen_xpos = doubleValue(args[2]);
    double __gen_ypos = doubleValue(args[3]);
    glfwSetCursorPos(__gen_window.get(), __gen_xpos, __gen_ypos);
    return 0;
}


GL_FUNC(glfwCreateCursor, args, ac) {
    GL_CHK_ARG(3, glfwCreateCursor(image, xhot, yhot));
    JS_HANDLE(__gen_image, args[1], GLFWimage);
    int __gen_xhot = intValue(args[2]);
    int __gen_yhot = intValue(args[3]);
    auto __return_glfwCreateCursor = glfwCreateCursor(__gen_image.get(), __gen_xhot, __gen_yhot);
    return wrapJs(__return_glfwCreateCursor);
}


GL_FUNC(glfwCreateStandardCursor, args, ac) {
    GL_CHK_ARG(1, glfwCreateStandardCursor(shape));
    int __gen_shape = intValue(args[1]);
    auto __return_glfwCreateStandardCursor = glfwCreateStandardCursor(__gen_shape);
    return wrapJs(__return_glfwCreateStandardCursor);
}


GL_FUNC(glfwDestroyCursor, args, ac) {
    GL_CHK_ARG(1, glfwDestroyCursor(cursor));
    JS_HANDLE(__gen_cursor, args[1], GLFWcursor);
    glfwDestroyCursor(__gen_cursor.get());
    return 0;
}


GL_FUNC(glfwSetCursor, args, ac) {
    GL_CHK_ARG(2, glfwSetCursor(window, cursor));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    JS_HANDLE(__gen_cursor, args[2], GLFWcursor);
    glfwSetCursor(__gen_window.get(), __gen_cursor.get());
    return 0;
}


// GL_FUNC(glfwSetKeyCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetKeyCallback(window, cbfun));
    // pushException("Not implemented function glfwSetKeyCallback(...)");
    // return 0;
// }


// GL_FUNC(glfwSetCharCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetCharCallback(window, cbfun));
    // pushException("Not implemented function glfwSetCharCallback(...)");
    // return 0;
// }


// GL_FUNC(glfwSetCharModsCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetCharModsCallback(window, cbfun));
    // pushException("Not implemented function glfwSetCharModsCallback(...)");
    // return 0;
// }


// GL_FUNC(glfwSetMouseButtonCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetMouseButtonCallback(window, cbfun));
    // pushException("Not implemented function glfwSetMouseButtonCallback(...)");
    // return 0;
// }


// GL_FUNC(glfwSetCursorPosCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetCursorPosCallback(window, cbfun));
    // pushException("Not implemented function glfwSetCursorPosCallback(...)");
    // return 0;
// }


// GL_FUNC(glfwSetCursorEnterCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetCursorEnterCallback(window, cbfun));
    // pushException("Not implemented function glfwSetCursorEnterCallback(...)");
    // return 0;
// }


// GL_FUNC(glfwSetScrollCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetScrollCallback(window, cbfun));
    // pushException("Not implemented function glfwSetScrollCallback(...)");
    // return 0;
// }


// GL_FUNC(glfwSetDropCallback, args, ac) {
    // GL_CHK_ARG(2, glfwSetDropCallback(window, cbfun));
    // pushException("Not implemented function glfwSetDropCallback(...)");
    // return 0;
// }


GL_FUNC(glfwJoystickPresent, args, ac) {
    GL_CHK_ARG(1, glfwJoystickPresent(jid));
    int __gen_jid = intValue(args[1]);
    auto __return_glfwJoystickPresent = glfwJoystickPresent(__gen_jid);
    return wrapJs(__return_glfwJoystickPresent);
}


GL_FUNC(glfwGetJoystickAxes, args, ac) {
    GL_CHK_ARG(2, glfwGetJoystickAxes(jid, count));
    int __gen_jid = intValue(args[1]);
    int __gen_count = 0;
    auto __return_glfwGetJoystickAxes = glfwGetJoystickAxes(__gen_jid, &__gen_count);
    return wrapJs(__gen_count);
}


GL_FUNC(glfwGetJoystickButtons, args, ac) {
    GL_CHK_ARG(2, glfwGetJoystickButtons(jid, count));
    int __gen_jid = intValue(args[1]);
    int __gen_count = 0;
    auto __return_glfwGetJoystickButtons = glfwGetJoystickButtons(__gen_jid, &__gen_count);
    return wrapJs(__gen_count);
}


GL_FUNC(glfwGetJoystickHats, args, ac) {
    GL_CHK_ARG(2, glfwGetJoystickHats(jid, count));
    int __gen_jid = intValue(args[1]);
    int __gen_count = 0;
    auto __return_glfwGetJoystickHats = glfwGetJoystickHats(__gen_jid, &__gen_count);
    return wrapJs(__gen_count);
}


GL_FUNC(glfwGetJoystickName, args, ac) {
    GL_CHK_ARG(1, glfwGetJoystickName(jid));
    int __gen_jid = intValue(args[1]);
    auto __return_glfwGetJoystickName = glfwGetJoystickName(__gen_jid);
    return wrapJs(__return_glfwGetJoystickName);
}


GL_FUNC(glfwGetJoystickGUID, args, ac) {
    GL_CHK_ARG(1, glfwGetJoystickGUID(jid));
    int __gen_jid = intValue(args[1]);
    auto __return_glfwGetJoystickGUID = glfwGetJoystickGUID(__gen_jid);
    return wrapJs(__return_glfwGetJoystickGUID);
}


// GL_FUNC(glfwSetJoystickUserPointer, args, ac) {
    // GL_CHK_ARG(2, glfwSetJoystickUserPointer(jid, pointer));
    // pushException("Not implemented function glfwSetJoystickUserPointer(...)");
    // return 0;
// }


GL_FUNC(glfwGetJoystickUserPointer, args, ac) {
    GL_CHK_ARG(1, glfwGetJoystickUserPointer(jid));
    int __gen_jid = intValue(args[1]);
    auto __return_glfwGetJoystickUserPointer = glfwGetJoystickUserPointer(__gen_jid);
    return wrapJs(__return_glfwGetJoystickUserPointer);
}


GL_FUNC(glfwJoystickIsGamepad, args, ac) {
    GL_CHK_ARG(1, glfwJoystickIsGamepad(jid));
    int __gen_jid = intValue(args[1]);
    auto __return_glfwJoystickIsGamepad = glfwJoystickIsGamepad(__gen_jid);
    return wrapJs(__return_glfwJoystickIsGamepad);
}


// GL_FUNC(glfwSetJoystickCallback, args, ac) {
    // GL_CHK_ARG(1, glfwSetJoystickCallback(cbfun));
    // pushException("Not implemented function glfwSetJoystickCallback(...)");
    // return 0;
// }


GL_FUNC(glfwUpdateGamepadMappings, args, ac) {
    GL_CHK_ARG(1, glfwUpdateGamepadMappings(string));
    std::string ____gen_string = toString(args[1]);
               const char* __gen_string = ____gen_string.c_str();
    auto __return_glfwUpdateGamepadMappings = glfwUpdateGamepadMappings(__gen_string);
    return wrapJs(__return_glfwUpdateGamepadMappings);
}


GL_FUNC(glfwGetGamepadName, args, ac) {
    GL_CHK_ARG(1, glfwGetGamepadName(jid));
    int __gen_jid = intValue(args[1]);
    auto __return_glfwGetGamepadName = glfwGetGamepadName(__gen_jid);
    return wrapJs(__return_glfwGetGamepadName);
}


GL_FUNC(glfwGetGamepadState, args, ac) {
    GL_CHK_ARG(2, glfwGetGamepadState(jid, state));
    int __gen_jid = intValue(args[1]);
    JS_HANDLE(__gen_state, args[2], GLFWgamepadstate);
    auto __return_glfwGetGamepadState = glfwGetGamepadState(__gen_jid, __gen_state.get());
    return wrapJs(__return_glfwGetGamepadState);
}


GL_FUNC(glfwSetClipboardString, args, ac) {
    GL_CHK_ARG(2, glfwSetClipboardString(window, string));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    std::string ____gen_string = toString(args[2]);
               const char* __gen_string = ____gen_string.c_str();
    glfwSetClipboardString(__gen_window.get(), __gen_string);
    return 0;
}


GL_FUNC(glfwGetClipboardString, args, ac) {
    GL_CHK_ARG(1, glfwGetClipboardString(window));
    JS_HANDLE(__gen_window, args[1], GLFWwindow);
    auto __return_glfwGetClipboardString = glfwGetClipboardString(__gen_window.get());
    return wrapJs(__return_glfwGetClipboardString);
}


// GL_FUNC(glfwGetTime, args, ac) {
    // auto __return_glfwGetTime = glfwGetTime();
    // return wrapJs(__return_glfwGetTime);
// }


GL_FUNC(glfwSetTime, args, ac) {
    GL_CHK_ARG(1, glfwSetTime(time));
    double __gen_time = doubleValue(args[1]);
    glfwSetTime(__gen_time);
    return 0;
}


GL_FUNC(glfwGetTimerValue, args, ac) {
    auto __return_glfwGetTimerValue = glfwGetTimerValue();
    return wrapJs(__return_glfwGetTimerValue);
}


GL_FUNC(glfwGetTimerFrequency, args, ac) {
    auto __return_glfwGetTimerFrequency = glfwGetTimerFrequency();
    return wrapJs(__return_glfwGetTimerFrequency);
}


// GL_FUNC(glfwMakeContextCurrent, args, ac) {
    // GL_CHK_ARG(1, glfwMakeContextCurrent(window));
    // JS_HANDLE(__gen_window, args[1], GLFWwindow);
    // glfwMakeContextCurrent(__gen_window.get());
    // return 0;
// }


GL_FUNC(glfwGetCurrentContext, args, ac) {
    auto __return_glfwGetCurrentContext = glfwGetCurrentContext();
    return wrapJs(__return_glfwGetCurrentContext);
}


// GL_FUNC(glfwSwapBuffers, args, ac) {
    // GL_CHK_ARG(1, glfwSwapBuffers(window));
    // JS_HANDLE(__gen_window, args[1], GLFWwindow);
    // glfwSwapBuffers(__gen_window.get());
    // return 0;
// }


// GL_FUNC(glfwSwapInterval, args, ac) {
    // GL_CHK_ARG(1, glfwSwapInterval(interval));
    // int __gen_interval = intValue(args[1]);
    // glfwSwapInterval(__gen_interval);
    // return 0;
// }


GL_FUNC(glfwExtensionSupported, args, ac) {
    GL_CHK_ARG(1, glfwExtensionSupported(extension));
    std::string ____gen_extension = toString(args[1]);
               const char* __gen_extension = ____gen_extension.c_str();
    auto __return_glfwExtensionSupported = glfwExtensionSupported(__gen_extension);
    return wrapJs(__return_glfwExtensionSupported);
}


GL_FUNC(glfwGetProcAddress, args, ac) {
    GL_CHK_ARG(1, glfwGetProcAddress(procname));
    std::string ____gen_procname = toString(args[1]);
               const char* __gen_procname = ____gen_procname.c_str();
    auto __return_glfwGetProcAddress = glfwGetProcAddress(__gen_procname);
    return wrapJs(__return_glfwGetProcAddress);
}


GL_FUNC(glfwVulkanSupported, args, ac) {
    auto __return_glfwVulkanSupported = glfwVulkanSupported();
    return wrapJs(__return_glfwVulkanSupported);
}


// GL_FUNC(glfwGetRequiredInstanceExtensions, args, ac) {
    // GL_CHK_ARG(1, glfwGetRequiredInstanceExtensions(count));
    // pushException("Not implemented function glfwGetRequiredInstanceExtensions(...)");
    // return 0;
// }


// GL_FUNC(glfwGetInstanceProcAddress, args, ac) {
    // GL_CHK_ARG(2, glfwGetInstanceProcAddress(instance, procname));
    // pushException("Not implemented function glfwGetInstanceProcAddress(...)");
    // return 0;
// }


// GL_FUNC(glfwGetPhysicalDevicePresentationSupport, args, ac) {
    // GL_CHK_ARG(3, glfwGetPhysicalDevicePresentationSupport(instance, device, queuefamily));
    // pushException("Not implemented function glfwGetPhysicalDevicePresentationSupport(...)");
    // return 0;
// }


// GL_FUNC(glfwCreateWindowSurface, args, ac) {
    // GL_CHK_ARG(4, glfwCreateWindowSurface(instance, window, allocator, surface));
    // pushException("Not implemented function glfwCreateWindowSurface(...)");
    // return 0;
// }


void auto_bind_glfw3_h(VM*vm, LocalVal& gl) {
    // GL_BIND(glfwInit);
    // GL_BIND(glfwTerminate);
    GL_BIND(glfwInitHint);
    // GL_BIND(glfwGetVersion);
    // GL_BIND(glfwGetVersionString);
    GL_BIND(glfwGetError);
    // GL_BIND(glfwSetErrorCallback);
    GL_BIND(glfwGetMonitors);
    // GL_BIND(glfwGetPrimaryMonitor);
    GL_BIND(glfwGetMonitorPos);
    GL_BIND(glfwGetMonitorPhysicalSize);
    GL_BIND(glfwGetMonitorContentScale);
    GL_BIND(glfwGetMonitorName);
    // GL_BIND(glfwSetMonitorUserPointer);
    // GL_BIND(glfwGetMonitorUserPointer);
    // GL_BIND(glfwSetMonitorCallback);
    GL_BIND(glfwGetVideoModes);
    // GL_BIND(glfwGetVideoMode);
    GL_BIND(glfwSetGamma);
    GL_BIND(glfwGetGammaRamp);
    GL_BIND(glfwSetGammaRamp);
    GL_BIND(glfwDefaultWindowHints);
    GL_BIND(glfwWindowHint);
    GL_BIND(glfwWindowHintString);
    // GL_BIND(glfwCreateWindow);
    // GL_BIND(glfwDestroyWindow);
    // GL_BIND(glfwWindowShouldClose);
    GL_BIND(glfwSetWindowShouldClose);
    // GL_BIND(glfwSetWindowTitle);
    GL_BIND(glfwSetWindowIcon);
    GL_BIND(glfwGetWindowPos);
    // GL_BIND(glfwSetWindowPos);
    // GL_BIND(glfwGetWindowSize);
    GL_BIND(glfwSetWindowSizeLimits);
    // GL_BIND(glfwSetWindowAspectRatio);
    // GL_BIND(glfwSetWindowSize);
    // GL_BIND(glfwGetFramebufferSize);
    GL_BIND(glfwGetWindowFrameSize);
    GL_BIND(glfwGetWindowContentScale);
    GL_BIND(glfwGetWindowOpacity);
    GL_BIND(glfwSetWindowOpacity);
    GL_BIND(glfwIconifyWindow);
    GL_BIND(glfwRestoreWindow);
    GL_BIND(glfwMaximizeWindow);
    GL_BIND(glfwShowWindow);
    GL_BIND(glfwHideWindow);
    GL_BIND(glfwFocusWindow);
    GL_BIND(glfwRequestWindowAttention);
    // GL_BIND(glfwGetWindowMonitor);
    // GL_BIND(glfwSetWindowMonitor);
    GL_BIND(glfwGetWindowAttrib);
    GL_BIND(glfwSetWindowAttrib);
    // GL_BIND(glfwSetWindowUserPointer);
    GL_BIND(glfwGetWindowUserPointer);
    // GL_BIND(glfwSetWindowPosCallback);
    // GL_BIND(glfwSetWindowSizeCallback);
    // GL_BIND(glfwSetWindowCloseCallback);
    // GL_BIND(glfwSetWindowRefreshCallback);
    // GL_BIND(glfwSetWindowFocusCallback);
    // GL_BIND(glfwSetWindowIconifyCallback);
    // GL_BIND(glfwSetWindowMaximizeCallback);
    // GL_BIND(glfwSetFramebufferSizeCallback);
    // GL_BIND(glfwSetWindowContentScaleCallback);
    // GL_BIND(glfwPollEvents);
    // GL_BIND(glfwWaitEvents);
    // GL_BIND(glfwWaitEventsTimeout);
    GL_BIND(glfwPostEmptyEvent);
    GL_BIND(glfwGetInputMode);
    GL_BIND(glfwSetInputMode);
    GL_BIND(glfwGetKeyName);
    GL_BIND(glfwGetKeyScancode);
    GL_BIND(glfwGetKey);
    GL_BIND(glfwGetMouseButton);
    GL_BIND(glfwGetCursorPos);
    GL_BIND(glfwSetCursorPos);
    GL_BIND(glfwCreateCursor);
    GL_BIND(glfwCreateStandardCursor);
    GL_BIND(glfwDestroyCursor);
    GL_BIND(glfwSetCursor);
    // GL_BIND(glfwSetKeyCallback);
    // GL_BIND(glfwSetCharCallback);
    // GL_BIND(glfwSetCharModsCallback);
    // GL_BIND(glfwSetMouseButtonCallback);
    // GL_BIND(glfwSetCursorPosCallback);
    // GL_BIND(glfwSetCursorEnterCallback);
    // GL_BIND(glfwSetScrollCallback);
    // GL_BIND(glfwSetDropCallback);
    GL_BIND(glfwJoystickPresent);
    GL_BIND(glfwGetJoystickAxes);
    GL_BIND(glfwGetJoystickButtons);
    GL_BIND(glfwGetJoystickHats);
    GL_BIND(glfwGetJoystickName);
    GL_BIND(glfwGetJoystickGUID);
    // GL_BIND(glfwSetJoystickUserPointer);
    GL_BIND(glfwGetJoystickUserPointer);
    GL_BIND(glfwJoystickIsGamepad);
    // GL_BIND(glfwSetJoystickCallback);
    GL_BIND(glfwUpdateGamepadMappings);
    GL_BIND(glfwGetGamepadName);
    GL_BIND(glfwGetGamepadState);
    GL_BIND(glfwSetClipboardString);
    GL_BIND(glfwGetClipboardString);
    // GL_BIND(glfwGetTime);
    GL_BIND(glfwSetTime);
    GL_BIND(glfwGetTimerValue);
    GL_BIND(glfwGetTimerFrequency);
    // GL_BIND(glfwMakeContextCurrent);
    GL_BIND(glfwGetCurrentContext);
    // GL_BIND(glfwSwapBuffers);
    // GL_BIND(glfwSwapInterval);
    GL_BIND(glfwExtensionSupported);
    GL_BIND(glfwGetProcAddress);
    GL_BIND(glfwVulkanSupported);
    // GL_BIND(glfwGetRequiredInstanceExtensions);
    // GL_BIND(glfwGetInstanceProcAddress);
    // GL_BIND(glfwGetPhysicalDevicePresentationSupport);
    // GL_BIND(glfwCreateWindowSurface);
}
