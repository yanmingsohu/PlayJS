#include "gl.h"

#include <memory>


template<class T>
static JsValueRef wrapArr(T *arr, const GLsizei size) {
    LocalArray jsarr(size);
    for (int i = 0; i < size; ++i) {
        jsarr.set(i, wrapJs(arr[i]));
    }
    return jsarr;
}


template<class LenType, class ArrType, class NativeFromJsType>
static int callJsWithNumOrArr(JsValueRef arg, 
        void(*callNative)(LenType, const ArrType*), 
        NativeFromJsType(*jsToNative)(JsValueRef, NativeFromJsType),
        NativeFromJsType defaultVal)
{
    JsValueType type;
    JsGetValueType(arg, &type);
    if (type == JsNumber) {
        ArrType id = jsToNative(arg, defaultVal);
        callNative(1, &id);
        return 1;
    }
    else if (type == JsArray) {
        LocalArray jarr(arg);
        LenType len = jarr.length();
        ArrType *arr = new ArrType[len];
        std::unique_ptr<ArrType[]> deleter(arr);
        for (int i = 0; i < len; ++i) {
            arr[i] = jsToNative(jarr.get(i), defaultVal);
        }
        callNative(len, arr);
        return len;
    }
    return 0;
}


template<class IdType>
JsValueRef genTpl(GLsizei size, void(*genFunc)(GLsizei, IdType*)) {
    if (size == 1) {
        GLuint id = 0;
        genFunc(1, &id);
        return wrapJs(id);
    }
    else if (size > 1) {
        std::unique_ptr<IdType[]> arr(new IdType[size]);
        genFunc(size, arr.get());
        return wrapArr(arr.get(), size);
    }
    pushException("size must > 0");
    return 0;
}


typedef void(*UniformMatrixFunc)(GLint location,
        GLsizei count, GLboolean transpose, const GLfloat *value);

void UniformMatrixTpl(JsValueRef *args, UniformMatrixFunc umat) {
    GLint location = intValue(args[1]);
    GLsizei count = intValue(args[2]);
    GLboolean transpose = boolValue(args[3]);
    LocalTypedArray value(args[4]);
    umat(location, count, transpose, (GLfloat*)value.buffer());
}


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
    return genTpl(size, glGenBuffers);
}


GL_FUNC(glDeleteBuffers, args, ac) {
    GL_CHK_ARG(1, glDeleteBuffers(buffer));
    callJsWithNumOrArr<GLsizei, GLuint, int>(
        args[1], glDeleteBuffers, intValue, 0);
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


GL_FUNC(glewInit, args, ac) {
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        auto msg = glewGetErrorString(err);
        pushException((char*) msg, err);
    }
    return 0;
}


GL_FUNC(glCreateShader, args, ac) {
    GL_CHK_ARG(1, glCreateShader(type));
    GLenum type = (GLenum) intValue(args[1]);
    GLuint shader = glCreateShader(type);
    return wrapJs(shader);
}


GL_FUNC(glShaderSource, args, ac) {
    GL_CHK_ARG(2, glCompileShader(shader, string));
    GLuint shader = intValue(args[1]);
    std::string str = toString(args[2]);
    const GLchar * strings[] = { str.c_str() };
    const GLint length = str.size();
    glShaderSource(shader, 1, strings, &length);
    return 0;
}


GL_FUNC(glCompileShader, args, ac) {
    GL_CHK_ARG(1, glCompileShader(shader));
    GLuint shader = intValue(args[1]);
    glCompileShader(shader);
    return 0;
}


GL_FUNC(glGetShaderiv, args, ac) {
    GL_CHK_ARG(2, glGetShaderiv(shader, pname));
    GLuint shader = intValue(args[1]);
    GLenum pname = intValue(args[2]);
    GLint param;
    glGetShaderiv(shader, pname, &param);
    return wrapJs(param);
}


GL_FUNC(glGetShaderInfoLog, args, ac) {
    GL_CHK_ARG(1, glGetShaderInfoLog(shader));
    GLuint shader = intValue(args[1]);
    GLint log_length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length > 1) {
        std::unique_ptr<char[]> msg(new char[log_length]);
        glGetShaderInfoLog(shader, log_length, NULL, msg.get());
        return wrapJs(msg.get());
    }
    return 0;
}


GL_FUNC(glCreateProgram, args, ac) {
    return wrapJs(glCreateProgram());
}


GL_FUNC(glAttachShader, args, ac) {
    GL_CHK_ARG(2, glAttachShader(program, shader));
    GLuint prog = intValue(args[1]);
    GLuint shader = intValue(args[2]);
    glAttachShader(prog, shader);
    return 0;
}


GL_FUNC(glLinkProgram, args, ac) {
    GL_CHK_ARG(1, glLinkProgram(program));
    GLuint prog = intValue(args[1]);
    glLinkProgram(prog);
    return 0;
}


GL_FUNC(glGetProgramiv, args, ac) {
    GL_CHK_ARG(1, glGetProgramiv(program, pname));
    GLuint prog = intValue(args[1]);
    GLenum pname = intValue(args[2]);
    GLint param;
    glGetProgramiv(prog, pname, &param);
    return wrapJs(param);
}


GL_FUNC(glGetProgramInfoLog, args, ac) {
    GL_CHK_ARG(1, glGetProgramInfoLog(program));
    GLuint prog = intValue(args[1]);
    GLint log_length;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length > 1) {
        std::unique_ptr<char[]> msg(new char[log_length]);
        glGetProgramInfoLog(prog, log_length, NULL, msg.get());
        return wrapJs(msg.get());
    }
    return 0;
}


GL_FUNC(glUseProgram, args, ac) {
    GL_CHK_ARG(1, glUseProgram(program));
    GLuint prog = intValue(args[1]);
    glUseProgram(prog);
    return 0;
}


GL_FUNC(glGetUniformLocation, args, ac) {
    GL_CHK_ARG(2, glGetUniformLocation(program, name));
    GLuint prog = intValue(args[1]);
    std::string name = stringValue(args[2]);
    GLint r = glGetUniformLocation(prog, name.c_str());
    return wrapJs(r);
}


GL_FUNC(glUniform4f, args, ac) {
    GL_CHK_ARG(5, glUniform4f(location, v0, v1, v2, v3));
    GLint location = intValue(args[1]);
    GLfloat v0 = floatValue(args[2]);
    GLfloat v1 = floatValue(args[3]);
    GLfloat v2 = floatValue(args[4]);
    GLfloat v3 = floatValue(args[5]);
    glUniform4f(location, v0, v1, v2, v3);
    return 0;
}


GL_FUNC(glUniform3f, args, ac) {
    GL_CHK_ARG(4, glUniform3f(location, v0, v1, v2));
    GLint location = intValue(args[1]);
    GLfloat v0 = floatValue(args[2]);
    GLfloat v1 = floatValue(args[3]);
    GLfloat v2 = floatValue(args[4]);
    glUniform3f(location, v0, v1, v2);
    return 0;
}


GL_FUNC(glUniform2f, args, ac) {
    GL_CHK_ARG(3, glUniform2f(location, v0, v1));
    GLint location = intValue(args[1]);
    GLfloat v0 = floatValue(args[2]);
    GLfloat v1 = floatValue(args[3]);
    glUniform2f(location, v0, v1);
    return 0;
}


GL_FUNC(glUniform1f, args, ac) {
    GL_CHK_ARG(2, glUniform1f(location, v0));
    GLint location = intValue(args[1]);
    GLfloat v0 = floatValue(args[2]);
    glUniform1f(location, v0);
    return 0;
}


GL_FUNC(glUniform4i, args, ac) {
    GL_CHK_ARG(5, glUniform4i(location, v0, v1, v2, v3));
    GLint location = intValue(args[1]);
    GLint v0 = intValue(args[2]);
    GLint v1 = intValue(args[3]);
    GLint v2 = intValue(args[4]);
    GLint v3 = intValue(args[5]);
    glUniform4i(location, v0, v1, v2, v3);
    return 0;
}


GL_FUNC(glUniform3i, args, ac) {
    GL_CHK_ARG(4, glUniform3i(location, v0, v1, v2));
    GLint location = intValue(args[1]);
    GLint v0 = intValue(args[2]);
    GLint v1 = intValue(args[3]);
    GLint v2 = intValue(args[4]);
    glUniform3i(location, v0, v1, v2);
    return 0;
}


GL_FUNC(glUniform2i, args, ac) {
    GL_CHK_ARG(3, glUniform2i(location, v0, v1));
    GLint location = intValue(args[1]);
    GLint v0 = intValue(args[2]);
    GLint v1 = intValue(args[3]);
    glUniform2i(location, v0, v1);
    return 0;
}


GL_FUNC(glUniform1i, args, ac) {
    GL_CHK_ARG(2, glUniform1i(location, v0));
    GLint location = intValue(args[1]);
    GLint v0 = intValue(args[2]);
    glUniform1i(location, v0);
    return 0;
}


GL_FUNC(glUniform2uiv, args, ac) {
    GL_CHK_ARG(2, glUniform2uiv(location, Uint32Array));
    GLint location = intValue(args[1]);
    LocalTypedArray arr(args[2]);
    glUniform2uiv(location, arr.length()/arr.unitLen()/2, (GLuint*) arr.buffer());
    return 0;
}


GL_FUNC(glUniform3fv, args, ac) {
    GL_CHK_ARG(2, glUniform3fv(location, Float32Array));
    GLint location = intValue(args[1]);
    LocalTypedArray arr(args[2]);
    glUniform3fv(location, arr.length()/arr.unitLen()/3, (GLfloat*)arr.buffer());
    return 0;
}


GL_FUNC(glUniform4fv, args, ac) {
    GL_CHK_ARG(2, glUniform4fv(location, Float32Array));
    GLint location = intValue(args[1]);
    LocalTypedArray arr(args[2]);
    glUniform4fv(location, arr.length()/arr.unitLen()/4, (GLfloat*)arr.buffer());
    return 0;
}


GL_FUNC(glUniformMatrix4fv, args, ac) {
    GL_CHK_ARG(4, glUniformMatrix4fv(location, count, transpose, value));
    UniformMatrixTpl(args, glUniformMatrix4fv);
    return 0;
}


GL_FUNC(glUniformMatrix3fv, args, ac) {
    GL_CHK_ARG(4, glUniformMatrix3fv(location, count, transpose, value));
    UniformMatrixTpl(args, glUniformMatrix3fv);
    return 0;
}


GL_FUNC(glUniformMatrix2fv, args, ac) {
    GL_CHK_ARG(4, glUniformMatrix2fv(location, count, transpose, value));
    UniformMatrixTpl(args, glUniformMatrix2fv);
    return 0;
}


GL_FUNC(glUniformMatrix2x3fv, args, ac) {
    GL_CHK_ARG(4, glUniformMatrix2x3fv(location, count, transpose, value));
    UniformMatrixTpl(args, glUniformMatrix2x3fv);
    return 0;
}


GL_FUNC(glUniformMatrix3x2fv, args, ac) {
    GL_CHK_ARG(4, glUniformMatrix3x2fv(location, count, transpose, value));
    UniformMatrixTpl(args, glUniformMatrix3x2fv);
    return 0;
}


GL_FUNC(glUniformMatrix2x4fv, args, ac) {
    GL_CHK_ARG(4, glUniformMatrix2x4fv(location, count, transpose, value));
    UniformMatrixTpl(args, glUniformMatrix2x4fv);
    return 0;
}


GL_FUNC(glUniformMatrix4x2fv, args, ac) {
    GL_CHK_ARG(4, glUniformMatrix4x2fv(location, count, transpose, value));
    UniformMatrixTpl(args, glUniformMatrix4x2fv);
    return 0;
}


GL_FUNC(glUniformMatrix3x4fv, args, ac) {
    GL_CHK_ARG(4, glUniformMatrix3x4fv(location, count, transpose, value));
    UniformMatrixTpl(args, glUniformMatrix3x4fv);
    return 0;
}


GL_FUNC(glUniformMatrix4x3fv, args, ac) {
    GL_CHK_ARG(4, glUniformMatrix4x3fv(location, count, transpose, value));
    UniformMatrixTpl(args, glUniformMatrix4x3fv);
    return 0;
}


GL_FUNC(glDeleteShader, args, ac) {
    GL_CHK_ARG(1, glDeleteShader(shader));
    GLuint shader = intValue(args[1]);
    glDeleteShader(shader);
    return 0;
}


GL_FUNC(glVertexAttribPointer, args, ac) {
    GL_CHK_ARG(6, glVertexAttribPointer(index, size, type, normalized, stride, pointer));
    GLuint index = intValue(args[1]);
    GLint size = intValue(args[2]);
    GLenum type = intValue(args[3]);
    GLboolean normalized = intValue(args[4]);
    GLsizei stride = intValue(args[5]);
    GLvoid * pointer = (GLvoid *) intValue(args[6]);
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    return 0;
}


GL_FUNC(glVertexAttribIPointer, args, ac) {
    GL_CHK_ARG(5, glVertexAttribIPointer(index, size, type, stride, pointer));
    GLuint index = intValue(args[1]);
    GLint size = intValue(args[2]);
    GLenum type = intValue(args[3]);
    GLsizei stride = intValue(args[4]);
    GLvoid * pointer = (GLvoid *)intValue(args[5]);
    glVertexAttribIPointer(index, size, type, stride, pointer);
    return 0;
}


GL_FUNC(glEnableVertexAttribArray, args, ac) {
    GL_CHK_ARG(1, glEnableVertexAttribArray(index));
    GLuint index = intValue(args[1]);
    glEnableVertexAttribArray(index);
    return 0;
}


GL_FUNC(glDisableVertexAttribArray, args, ac) {
    GL_CHK_ARG(1, glDisableVertexAttribArray(index));
    GLuint index = intValue(args[1]);
    glDisableVertexAttribArray(index);
    return 0;
}


GL_FUNC(glBindVertexArray, args, ac) {
    GL_CHK_ARG(1, glBindVertexArray(index));
    GLuint index = intValue(args[1]);
    glBindVertexArray(index);
    return 0;
}


GL_FUNC(glGenVertexArrays, args, ac) {
    GL_CHK_ARG(1, glGenVertexArrays(size));
    GLsizei size = intValue(args[1]);
    return genTpl(size, glGenVertexArrays);
}


GL_FUNC(glDeleteVertexArrays, args, ac) {
    GL_CHK_ARG(1, glDeleteVertexArrays(buffer));
    callJsWithNumOrArr<GLsizei, GLuint, int>(
            args[1], glDeleteVertexArrays, intValue, 0);
    return 0;
}


GL_FUNC(glDrawElements, args, ac) {
    GL_CHK_ARG(4, glDrawElements(mode, count, type, indices));
    GLenum mode = intValue(args[1]); 
    GLsizei count = intValue(args[2]);
    GLenum type = intValue(args[3]);
    int indices = intValue(args[4]);
    glDrawElements(mode, count, type, (void*) indices);
    return 0;
}


GL_FUNC(glGetIntegerv, args, ac) {
    GL_CHK_ARG(1, glGetIntegerv(pname));
    GLenum pname = intValue(args[1]);
    GLint ret = 0;
    glGetIntegerv(pname, &ret);
    return wrapJs(ret);
}


GL_FUNC(glTexParameterfv, args, ac) {
    GL_CHK_ARG(3, glTexParameterfv(target, pname, params));
    GLenum target = intValue(args[1]);
    GLenum pname = intValue(args[2]);
    LocalTypedArray arr(args[3]);
    glTexParameterfv(target, pname, (GLfloat*) arr.buffer());
    return 0;
}


GL_FUNC(glGenTextures, args, ac) {
    GL_CHK_ARG(1, glGenTextures(size));
    GLsizei size = intValue(args[1]);
    return genTpl(size, glGenTextures);
}


GL_FUNC(glDeleteTextures, args, ac) {
    GL_CHK_ARG(1, glDeleteTextures(size));
    callJsWithNumOrArr<GLsizei, GLuint, int>(
        args[1], glDeleteTextures, intValue, 0);
    return 0;
}


GL_FUNC(glTexImage2D, args, ac) {
    GL_CHK_ARG(9, glTexImage2D(target, mipmap_level, internalformat, width, height, border, format, type, data));
    GLenum target = intValue(args[1]);
    GLint level = intValue(args[2]);
    GLint internalformat = intValue(args[3]);
    GLsizei width = intValue(args[4]);
    GLsizei height = intValue(args[5]);
    GLint border = intValue(args[6]);
    GLenum format = intValue(args[7]);
    GLenum type = intValue(args[8]);
    LocalTypedArray data(args[9]);
    glTexImage2D(target, level, internalformat, width, height, border, format, type, data.buffer());
    return 0;
}


JSS_FUNC(glGenerateMipmap, args, ac) {
    GL_CHK_ARG(1, glGenerateMipmap(target));
    GLenum target = intValue(args[1]);
    glGenerateMipmap(target);
    return 0;
}


JSS_FUNC(glGetUniformBlockIndex, args, ac) {
    GL_CHK_ARG(2, glGetUniformBlockIndex(program, name));
    GLuint prog = intValue(args[1]);
    auto name = stringValue(args[2]);
    GLuint idx = glGetUniformBlockIndex(prog, name.c_str());
    return wrapJs(idx);
}


JSS_FUNC(glUniformBlockBinding, args, ac) {
    GL_CHK_ARG(2, glUniformBlockBinding(program, name));
    GLuint prog = intValue(args[1]);
    GLuint idx = intValue(args[2]);
    GLuint bind = intValue(args[3]);
    glUniformBlockBinding(prog, idx, bind);
    return 0;
}


JSS_FUNC(glGetAttribLocation, args, ac) {
    GL_CHK_ARG(2, glGetAttribLocation(program, name));
    GLuint prog = intValue(args[1]);
    auto name = stringValue(args[2]);
    GLint idx = glGetAttribLocation(prog, name.c_str());
    return wrapJs(idx);
}


void installGLCore(VM* vm, LocalVal& gl) {
    GL_BIND(glewInit);
    GL_BIND(glViewport);
    GL_BIND(glGenBuffers);
    GL_BIND(glDeleteBuffers);
    GL_BIND(glBindBuffer);
    GL_BIND(glBufferData);

    GL_BIND(glTexParameterfv);
    GL_BIND(glGenTextures);
    GL_BIND(glTexImage2D);
    GL_BIND(glGenerateMipmap);
    GL_BIND(glDeleteTextures);

    GL_BIND(glDrawElements);
    GL_BIND(glGetIntegerv);
    GL_BIND(glGetUniformLocation);
    GL_BIND(glUniform4f);
    GL_BIND(glUniform3f);
    GL_BIND(glUniform2f);
    GL_BIND(glUniform1f);
    GL_BIND(glUniform4i);
    GL_BIND(glUniform3i);
    GL_BIND(glUniform2i);
    GL_BIND(glUniform1i);
    GL_BIND(glUniformMatrix2fv);
    GL_BIND(glUniformMatrix3fv);
    GL_BIND(glUniformMatrix4fv);
    GL_BIND(glUniformMatrix2x3fv);
    GL_BIND(glUniformMatrix3x2fv);
    GL_BIND(glUniformMatrix2x4fv);
    GL_BIND(glUniformMatrix4x2fv);
    GL_BIND(glUniformMatrix3x4fv);
    GL_BIND(glUniformMatrix4x3fv);
    GL_BIND(glUniform2uiv);
    GL_BIND(glUniform3fv);
    GL_BIND(glUniform4fv);

    GL_BIND(glCreateShader);
    GL_BIND(glDeleteShader);
    GL_BIND(glShaderSource);
    GL_BIND(glCompileShader);
    GL_BIND(glGetShaderiv);
    GL_BIND(glGetShaderInfoLog);
    GL_BIND(glVertexAttribPointer);
    GL_BIND(glVertexAttribIPointer);

    GL_BIND(glGenVertexArrays);
    GL_BIND(glDeleteVertexArrays);
    GL_BIND(glBindVertexArray);
    GL_BIND(glEnableVertexAttribArray);
    GL_BIND(glDisableVertexAttribArray);

    GL_BIND(glCreateProgram);
    GL_BIND(glAttachShader);
    GL_BIND(glLinkProgram);
    GL_BIND(glUseProgram);
    GL_BIND(glGetProgramInfoLog);
    GL_BIND(glGetProgramiv);
    GL_BIND(glGetUniformBlockIndex);
    GL_BIND(glUniformBlockBinding);
    GL_BIND(glGetAttribLocation);
}