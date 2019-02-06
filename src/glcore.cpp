#include "gl.h"


GL_FUNC(glViewport, args, ac) {
    GL_CHK_ARG(4, glViewport(x, y, width, height));
    int x = intValue(args[1]);
    int y = intValue(args[2]);
    int width = intValue(args[3]);
    int height = intValue(args[4]);
    glViewport(x, y, width, height);
    return 0;
}


void installGLCore(VM* vm, LocalVal& gl) {
    GL_BIND(glViewport);
}