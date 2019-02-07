#pragma once

#include "gl.h"


template<> struct SharedResourceDeleter<GLFWwindow> {
    virtual void operator()(GLFWwindow* w) {
        println("GLFWwindow closed", 0, LDEBUG);
        glfwDestroyWindow(w);
    }
};


template<> struct SharedResourceDeleter<GLFWmonitor> {
    virtual void operator()(GLFWmonitor* w) {/* Do nothing */ }
};


template<> struct SharedResourceDeleter<GLFWgammaramp> {
    virtual void operator()(GLFWgammaramp* w) {/* Do nothing */ }
};


template<> struct SharedResourceDeleter<GLFWimage> {
    virtual void operator()(GLFWimage* w) {/* Do nothing */ }
};


template<> struct SharedResourceDeleter<GLFWcursor> {
    virtual void operator()(GLFWcursor* w) {/* Do nothing */ }
};


template<> struct SharedResourceDeleter<GLFWgamepadstate> {
    virtual void operator()(GLFWgamepadstate* w) {/* Do nothing */ }
};