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


GL_FUNC(glGenBuffers, args, ac) {
    GL_CHK_ARG(1, glGenBuffers(size));
    GLsizei size = intValue(args[1]);
    if (size == 1) {
        GLuint id = 0;
        glGenBuffers(1, &id);
        return wrapJs(id);
    }
    else if (size > 1) {
        GLuint *id = new GLuint[size];
        LocalResource<GLuint> _id(id, DeleteArray);
        glGenBuffers(size, id);

        LocalArray jsarr = JVM->createArr(size);
        for (int i = 0; i < size; ++i) {
            jsarr.set(i, wrapJs(id[i]));
        }
        return jsarr;
    }
    return 0;
}


GL_FUNC(glBindBuffer, args, ac) {
    GL_CHK_ARG(2, glBindBuffer(target, bufferID));
    GLenum t = (GLenum) intValue(args[1]);
    GLuint b = (GLuint) intValue(args[2]);
    glBindBuffer(t, b);
    return 0;
}


GL_FUNC(glBufferData, args, ac) {
    GL_CHK_ARG(3, glBufferData(target, TypedBuffer, usage));
    GLenum target = (GLenum) intValue(args[1]);
    LocalTypedArray arr(args[2]);
    GLenum usage = (GLenum)intValue(args[3]);
    glBufferData(target, arr.length(), arr.buffer(), usage);
    return 0;
}


void installGLCore(VM* vm, LocalVal& gl) {
    GL_BIND(glViewport);
    GL_BIND(glGenBuffers);
    GL_BIND(glBindBuffer);
    GL_BIND(glBufferData);
}