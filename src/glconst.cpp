#include "gl.h"


#define sizeof$float    sizeof(float)
#define sizeof$double   sizeof(double)
#define sizeof$int      sizeof(int)
#define sizeof$short    sizeof(short)
#define sizeof$char     sizeof(char)
#define sizeof$long     sizeof(long)


void installGLFWConst(VM* vm, LocalVal& _const) {
    GL_INT_ENUM(GLFW_HAT_RIGHT_UP);
    GL_INT_ENUM(GLFW_HAT_RIGHT_DOWN);
    GL_INT_ENUM(GLFW_HAT_LEFT_UP);
    GL_INT_ENUM(GLFW_HAT_LEFT_DOWN);

    GL_INT_ENUM(sizeof$float);
    GL_INT_ENUM(sizeof$double);
    GL_INT_ENUM(sizeof$int);
    GL_INT_ENUM(sizeof$short);
    GL_INT_ENUM(sizeof$char);
    GL_INT_ENUM(sizeof$long);
}