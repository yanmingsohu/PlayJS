#include "gl.h"


void installGLFWConst(VM* vm, LocalVal& _const) {
    GL_INT_ENUM(GLFW_HAT_RIGHT_UP);
    GL_INT_ENUM(GLFW_HAT_RIGHT_DOWN);
    GL_INT_ENUM(GLFW_HAT_LEFT_UP);
    GL_INT_ENUM(GLFW_HAT_LEFT_DOWN);
}