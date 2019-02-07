// 
// 2019-02-07 16:38:10
// create from D:\game\sanguo7\src-auto\generate-code.js
// 
// D:\game\sanguo7\deps\glew\include\GL\glew.h
//
#include "../src/gl.h"
#include "../src/gldeleter.h"


GL_FUNC(glAccum, args, ac) {
    GL_CHK_ARG(2, glAccum(op, value));
    GLenum __gen_op = (GLenum) intValue(args[1]);
    GLfloat __gen_value = (GLfloat) doubleValue(args[2]);
    glAccum(__gen_op, __gen_value);
    return 0;
}


GL_FUNC(glAlphaFunc, args, ac) {
    GL_CHK_ARG(2, glAlphaFunc(func, ref));
    GLenum __gen_func = (GLenum) intValue(args[1]);
    GLclampf __gen_ref = (GLclampf) doubleValue(args[2]);
    glAlphaFunc(__gen_func, __gen_ref);
    return 0;
}


GL_FUNC(glAreTexturesResident, args, ac) {
    GL_CHK_ARG(3, glAreTexturesResident(n, textures, residences));
    pushException("Not implemented function glAreTexturesResident(...)");
    return 0;
}


GL_FUNC(glArrayElement, args, ac) {
    GL_CHK_ARG(1, glArrayElement(i));
    GLint __gen_i = (GLint) intValue(args[1]);
    glArrayElement(__gen_i);
    return 0;
}


GL_FUNC(glBegin, args, ac) {
    GL_CHK_ARG(1, glBegin(mode));
    GLenum __gen_mode = (GLenum) intValue(args[1]);
    glBegin(__gen_mode);
    return 0;
}


GL_FUNC(glBindTexture, args, ac) {
    GL_CHK_ARG(2, glBindTexture(target, texture));
    GLenum __gen_target = (GLenum) intValue(args[1]);
    GLuint __gen_texture = (GLuint) intValue(args[2]);
    glBindTexture(__gen_target, __gen_texture);
    return 0;
}


GL_FUNC(glBitmap, args, ac) {
    GL_CHK_ARG(7, glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap));
    pushException("Not implemented function glBitmap(...)");
    return 0;
}


GL_FUNC(glBlendFunc, args, ac) {
    GL_CHK_ARG(2, glBlendFunc(sfactor, dfactor));
    GLenum __gen_sfactor = (GLenum) intValue(args[1]);
    GLenum __gen_dfactor = (GLenum) intValue(args[2]);
    glBlendFunc(__gen_sfactor, __gen_dfactor);
    return 0;
}


GL_FUNC(glCallList, args, ac) {
    GL_CHK_ARG(1, glCallList(list));
    GLuint __gen_list = (GLuint) intValue(args[1]);
    glCallList(__gen_list);
    return 0;
}


GL_FUNC(glCallLists, args, ac) {
    GL_CHK_ARG(3, glCallLists(n, type, lists));
    pushException("Not implemented function glCallLists(...)");
    return 0;
}


GL_FUNC(glClear, args, ac) {
    GL_CHK_ARG(1, glClear(mask));
    GLbitfield __gen_mask = (GLbitfield) intValue(args[1]);
    glClear(__gen_mask);
    return 0;
}


GL_FUNC(glClearAccum, args, ac) {
    GL_CHK_ARG(4, glClearAccum(red, green, blue, alpha));
    GLfloat __gen_red = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_green = (GLfloat) doubleValue(args[2]);
    GLfloat __gen_blue = (GLfloat) doubleValue(args[3]);
    GLfloat __gen_alpha = (GLfloat) doubleValue(args[4]);
    glClearAccum(__gen_red, __gen_green, __gen_blue, __gen_alpha);
    return 0;
}


GL_FUNC(glClearColor, args, ac) {
    GL_CHK_ARG(4, glClearColor(red, green, blue, alpha));
    GLclampf __gen_red = (GLclampf) doubleValue(args[1]);
    GLclampf __gen_green = (GLclampf) doubleValue(args[2]);
    GLclampf __gen_blue = (GLclampf) doubleValue(args[3]);
    GLclampf __gen_alpha = (GLclampf) doubleValue(args[4]);
    glClearColor(__gen_red, __gen_green, __gen_blue, __gen_alpha);
    return 0;
}


GL_FUNC(glClearDepth, args, ac) {
    GL_CHK_ARG(1, glClearDepth(depth));
    GLclampd __gen_depth = (GLclampd) doubleValue(args[1]);
    glClearDepth(__gen_depth);
    return 0;
}


GL_FUNC(glClearIndex, args, ac) {
    GL_CHK_ARG(1, glClearIndex(c));
    GLfloat __gen_c = (GLfloat) doubleValue(args[1]);
    glClearIndex(__gen_c);
    return 0;
}


GL_FUNC(glClearStencil, args, ac) {
    GL_CHK_ARG(1, glClearStencil(s));
    GLint __gen_s = (GLint) intValue(args[1]);
    glClearStencil(__gen_s);
    return 0;
}


GL_FUNC(glClipPlane, args, ac) {
    GL_CHK_ARG(2, glClipPlane(plane, equation));
    pushException("Not implemented function glClipPlane(...)");
    return 0;
}


GL_FUNC(glColor3b, args, ac) {
    GL_CHK_ARG(3, glColor3b(red, green, blue));
    GLbyte __gen_red = (GLbyte) intValue(args[1]);
    GLbyte __gen_green = (GLbyte) intValue(args[2]);
    GLbyte __gen_blue = (GLbyte) intValue(args[3]);
    glColor3b(__gen_red, __gen_green, __gen_blue);
    return 0;
}


GL_FUNC(glColor3bv, args, ac) {
    GL_CHK_ARG(1, glColor3bv(v));
    pushException("Not implemented function glColor3bv(...)");
    return 0;
}


GL_FUNC(glColor3d, args, ac) {
    GL_CHK_ARG(3, glColor3d(red, green, blue));
    GLdouble __gen_red = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_green = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_blue = (GLdouble) doubleValue(args[3]);
    glColor3d(__gen_red, __gen_green, __gen_blue);
    return 0;
}


GL_FUNC(glColor3dv, args, ac) {
    GL_CHK_ARG(1, glColor3dv(v));
    pushException("Not implemented function glColor3dv(...)");
    return 0;
}


GL_FUNC(glColor3f, args, ac) {
    GL_CHK_ARG(3, glColor3f(red, green, blue));
    GLfloat __gen_red = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_green = (GLfloat) doubleValue(args[2]);
    GLfloat __gen_blue = (GLfloat) doubleValue(args[3]);
    glColor3f(__gen_red, __gen_green, __gen_blue);
    return 0;
}


GL_FUNC(glColor3fv, args, ac) {
    GL_CHK_ARG(1, glColor3fv(v));
    pushException("Not implemented function glColor3fv(...)");
    return 0;
}


GL_FUNC(glColor3i, args, ac) {
    GL_CHK_ARG(3, glColor3i(red, green, blue));
    GLint __gen_red = (GLint) intValue(args[1]);
    GLint __gen_green = (GLint) intValue(args[2]);
    GLint __gen_blue = (GLint) intValue(args[3]);
    glColor3i(__gen_red, __gen_green, __gen_blue);
    return 0;
}


GL_FUNC(glColor3iv, args, ac) {
    GL_CHK_ARG(1, glColor3iv(v));
    pushException("Not implemented function glColor3iv(...)");
    return 0;
}


GL_FUNC(glColor3s, args, ac) {
    GL_CHK_ARG(3, glColor3s(red, green, blue));
    GLshort __gen_red = (GLshort) intValue(args[1]);
    GLshort __gen_green = (GLshort) intValue(args[2]);
    GLshort __gen_blue = (GLshort) intValue(args[3]);
    glColor3s(__gen_red, __gen_green, __gen_blue);
    return 0;
}


GL_FUNC(glColor3sv, args, ac) {
    GL_CHK_ARG(1, glColor3sv(v));
    pushException("Not implemented function glColor3sv(...)");
    return 0;
}


GL_FUNC(glColor3ub, args, ac) {
    GL_CHK_ARG(3, glColor3ub(red, green, blue));
    GLubyte __gen_red = (GLubyte) intValue(args[1]);
    GLubyte __gen_green = (GLubyte) intValue(args[2]);
    GLubyte __gen_blue = (GLubyte) intValue(args[3]);
    glColor3ub(__gen_red, __gen_green, __gen_blue);
    return 0;
}


GL_FUNC(glColor3ubv, args, ac) {
    GL_CHK_ARG(1, glColor3ubv(v));
    pushException("Not implemented function glColor3ubv(...)");
    return 0;
}


GL_FUNC(glColor3ui, args, ac) {
    GL_CHK_ARG(3, glColor3ui(red, green, blue));
    GLuint __gen_red = (GLuint) intValue(args[1]);
    GLuint __gen_green = (GLuint) intValue(args[2]);
    GLuint __gen_blue = (GLuint) intValue(args[3]);
    glColor3ui(__gen_red, __gen_green, __gen_blue);
    return 0;
}


GL_FUNC(glColor3uiv, args, ac) {
    GL_CHK_ARG(1, glColor3uiv(v));
    pushException("Not implemented function glColor3uiv(...)");
    return 0;
}


GL_FUNC(glColor3us, args, ac) {
    GL_CHK_ARG(3, glColor3us(red, green, blue));
    GLushort __gen_red = (GLushort) intValue(args[1]);
    GLushort __gen_green = (GLushort) intValue(args[2]);
    GLushort __gen_blue = (GLushort) intValue(args[3]);
    glColor3us(__gen_red, __gen_green, __gen_blue);
    return 0;
}


GL_FUNC(glColor3usv, args, ac) {
    GL_CHK_ARG(1, glColor3usv(v));
    pushException("Not implemented function glColor3usv(...)");
    return 0;
}


GL_FUNC(glColor4b, args, ac) {
    GL_CHK_ARG(4, glColor4b(red, green, blue, alpha));
    GLbyte __gen_red = (GLbyte) intValue(args[1]);
    GLbyte __gen_green = (GLbyte) intValue(args[2]);
    GLbyte __gen_blue = (GLbyte) intValue(args[3]);
    GLbyte __gen_alpha = (GLbyte) intValue(args[4]);
    glColor4b(__gen_red, __gen_green, __gen_blue, __gen_alpha);
    return 0;
}


GL_FUNC(glColor4bv, args, ac) {
    GL_CHK_ARG(1, glColor4bv(v));
    pushException("Not implemented function glColor4bv(...)");
    return 0;
}


GL_FUNC(glColor4d, args, ac) {
    GL_CHK_ARG(4, glColor4d(red, green, blue, alpha));
    GLdouble __gen_red = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_green = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_blue = (GLdouble) doubleValue(args[3]);
    GLdouble __gen_alpha = (GLdouble) doubleValue(args[4]);
    glColor4d(__gen_red, __gen_green, __gen_blue, __gen_alpha);
    return 0;
}


GL_FUNC(glColor4dv, args, ac) {
    GL_CHK_ARG(1, glColor4dv(v));
    pushException("Not implemented function glColor4dv(...)");
    return 0;
}


GL_FUNC(glColor4f, args, ac) {
    GL_CHK_ARG(4, glColor4f(red, green, blue, alpha));
    GLfloat __gen_red = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_green = (GLfloat) doubleValue(args[2]);
    GLfloat __gen_blue = (GLfloat) doubleValue(args[3]);
    GLfloat __gen_alpha = (GLfloat) doubleValue(args[4]);
    glColor4f(__gen_red, __gen_green, __gen_blue, __gen_alpha);
    return 0;
}


GL_FUNC(glColor4fv, args, ac) {
    GL_CHK_ARG(1, glColor4fv(v));
    pushException("Not implemented function glColor4fv(...)");
    return 0;
}


GL_FUNC(glColor4i, args, ac) {
    GL_CHK_ARG(4, glColor4i(red, green, blue, alpha));
    GLint __gen_red = (GLint) intValue(args[1]);
    GLint __gen_green = (GLint) intValue(args[2]);
    GLint __gen_blue = (GLint) intValue(args[3]);
    GLint __gen_alpha = (GLint) intValue(args[4]);
    glColor4i(__gen_red, __gen_green, __gen_blue, __gen_alpha);
    return 0;
}


GL_FUNC(glColor4iv, args, ac) {
    GL_CHK_ARG(1, glColor4iv(v));
    pushException("Not implemented function glColor4iv(...)");
    return 0;
}


GL_FUNC(glColor4s, args, ac) {
    GL_CHK_ARG(4, glColor4s(red, green, blue, alpha));
    GLshort __gen_red = (GLshort) intValue(args[1]);
    GLshort __gen_green = (GLshort) intValue(args[2]);
    GLshort __gen_blue = (GLshort) intValue(args[3]);
    GLshort __gen_alpha = (GLshort) intValue(args[4]);
    glColor4s(__gen_red, __gen_green, __gen_blue, __gen_alpha);
    return 0;
}


GL_FUNC(glColor4sv, args, ac) {
    GL_CHK_ARG(1, glColor4sv(v));
    pushException("Not implemented function glColor4sv(...)");
    return 0;
}


GL_FUNC(glColor4ub, args, ac) {
    GL_CHK_ARG(4, glColor4ub(red, green, blue, alpha));
    GLubyte __gen_red = (GLubyte) intValue(args[1]);
    GLubyte __gen_green = (GLubyte) intValue(args[2]);
    GLubyte __gen_blue = (GLubyte) intValue(args[3]);
    GLubyte __gen_alpha = (GLubyte) intValue(args[4]);
    glColor4ub(__gen_red, __gen_green, __gen_blue, __gen_alpha);
    return 0;
}


GL_FUNC(glColor4ubv, args, ac) {
    GL_CHK_ARG(1, glColor4ubv(v));
    pushException("Not implemented function glColor4ubv(...)");
    return 0;
}


GL_FUNC(glColor4ui, args, ac) {
    GL_CHK_ARG(4, glColor4ui(red, green, blue, alpha));
    GLuint __gen_red = (GLuint) intValue(args[1]);
    GLuint __gen_green = (GLuint) intValue(args[2]);
    GLuint __gen_blue = (GLuint) intValue(args[3]);
    GLuint __gen_alpha = (GLuint) intValue(args[4]);
    glColor4ui(__gen_red, __gen_green, __gen_blue, __gen_alpha);
    return 0;
}


GL_FUNC(glColor4uiv, args, ac) {
    GL_CHK_ARG(1, glColor4uiv(v));
    pushException("Not implemented function glColor4uiv(...)");
    return 0;
}


GL_FUNC(glColor4us, args, ac) {
    GL_CHK_ARG(4, glColor4us(red, green, blue, alpha));
    GLushort __gen_red = (GLushort) intValue(args[1]);
    GLushort __gen_green = (GLushort) intValue(args[2]);
    GLushort __gen_blue = (GLushort) intValue(args[3]);
    GLushort __gen_alpha = (GLushort) intValue(args[4]);
    glColor4us(__gen_red, __gen_green, __gen_blue, __gen_alpha);
    return 0;
}


GL_FUNC(glColor4usv, args, ac) {
    GL_CHK_ARG(1, glColor4usv(v));
    pushException("Not implemented function glColor4usv(...)");
    return 0;
}


GL_FUNC(glColorMask, args, ac) {
    GL_CHK_ARG(4, glColorMask(red, green, blue, alpha));
    GLboolean __gen_red = (GLboolean) intValue(args[1]);
    GLboolean __gen_green = (GLboolean) intValue(args[2]);
    GLboolean __gen_blue = (GLboolean) intValue(args[3]);
    GLboolean __gen_alpha = (GLboolean) intValue(args[4]);
    glColorMask(__gen_red, __gen_green, __gen_blue, __gen_alpha);
    return 0;
}


GL_FUNC(glColorMaterial, args, ac) {
    GL_CHK_ARG(2, glColorMaterial(face, mode));
    GLenum __gen_face = (GLenum) intValue(args[1]);
    GLenum __gen_mode = (GLenum) intValue(args[2]);
    glColorMaterial(__gen_face, __gen_mode);
    return 0;
}


GL_FUNC(glColorPointer, args, ac) {
    GL_CHK_ARG(4, glColorPointer(size, type, stride, pointer));
    pushException("Not implemented function glColorPointer(...)");
    return 0;
}


GL_FUNC(glCopyPixels, args, ac) {
    GL_CHK_ARG(5, glCopyPixels(x, y, width, height, type));
    GLint __gen_x = (GLint) intValue(args[1]);
    GLint __gen_y = (GLint) intValue(args[2]);
    GLsizei __gen_width = (GLsizei) intValue(args[3]);
    GLsizei __gen_height = (GLsizei) intValue(args[4]);
    GLenum __gen_type = (GLenum) intValue(args[5]);
    glCopyPixels(__gen_x, __gen_y, __gen_width, __gen_height, __gen_type);
    return 0;
}


GL_FUNC(glCopyTexImage1D, args, ac) {
    GL_CHK_ARG(7, glCopyTexImage1D(target, level, internalFormat, x, y, width, border));
    GLenum __gen_target = (GLenum) intValue(args[1]);
    GLint __gen_level = (GLint) intValue(args[2]);
    GLenum __gen_internalFormat = (GLenum) intValue(args[3]);
    GLint __gen_x = (GLint) intValue(args[4]);
    GLint __gen_y = (GLint) intValue(args[5]);
    GLsizei __gen_width = (GLsizei) intValue(args[6]);
    GLint __gen_border = (GLint) intValue(args[7]);
    glCopyTexImage1D(__gen_target, __gen_level, __gen_internalFormat, __gen_x, __gen_y, __gen_width, __gen_border);
    return 0;
}


GL_FUNC(glCopyTexImage2D, args, ac) {
    GL_CHK_ARG(8, glCopyTexImage2D(target, level, internalFormat, x, y, width, height, border));
    GLenum __gen_target = (GLenum) intValue(args[1]);
    GLint __gen_level = (GLint) intValue(args[2]);
    GLenum __gen_internalFormat = (GLenum) intValue(args[3]);
    GLint __gen_x = (GLint) intValue(args[4]);
    GLint __gen_y = (GLint) intValue(args[5]);
    GLsizei __gen_width = (GLsizei) intValue(args[6]);
    GLsizei __gen_height = (GLsizei) intValue(args[7]);
    GLint __gen_border = (GLint) intValue(args[8]);
    glCopyTexImage2D(__gen_target, __gen_level, __gen_internalFormat, __gen_x, __gen_y, __gen_width, __gen_height, __gen_border);
    return 0;
}


GL_FUNC(glCopyTexSubImage1D, args, ac) {
    GL_CHK_ARG(6, glCopyTexSubImage1D(target, level, xoffset, x, y, width));
    GLenum __gen_target = (GLenum) intValue(args[1]);
    GLint __gen_level = (GLint) intValue(args[2]);
    GLint __gen_xoffset = (GLint) intValue(args[3]);
    GLint __gen_x = (GLint) intValue(args[4]);
    GLint __gen_y = (GLint) intValue(args[5]);
    GLsizei __gen_width = (GLsizei) intValue(args[6]);
    glCopyTexSubImage1D(__gen_target, __gen_level, __gen_xoffset, __gen_x, __gen_y, __gen_width);
    return 0;
}


GL_FUNC(glCopyTexSubImage2D, args, ac) {
    GL_CHK_ARG(8, glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height));
    GLenum __gen_target = (GLenum) intValue(args[1]);
    GLint __gen_level = (GLint) intValue(args[2]);
    GLint __gen_xoffset = (GLint) intValue(args[3]);
    GLint __gen_yoffset = (GLint) intValue(args[4]);
    GLint __gen_x = (GLint) intValue(args[5]);
    GLint __gen_y = (GLint) intValue(args[6]);
    GLsizei __gen_width = (GLsizei) intValue(args[7]);
    GLsizei __gen_height = (GLsizei) intValue(args[8]);
    glCopyTexSubImage2D(__gen_target, __gen_level, __gen_xoffset, __gen_yoffset, __gen_x, __gen_y, __gen_width, __gen_height);
    return 0;
}


GL_FUNC(glCullFace, args, ac) {
    GL_CHK_ARG(1, glCullFace(mode));
    GLenum __gen_mode = (GLenum) intValue(args[1]);
    glCullFace(__gen_mode);
    return 0;
}


GL_FUNC(glDeleteLists, args, ac) {
    GL_CHK_ARG(2, glDeleteLists(list, range));
    GLuint __gen_list = (GLuint) intValue(args[1]);
    GLsizei __gen_range = (GLsizei) intValue(args[2]);
    glDeleteLists(__gen_list, __gen_range);
    return 0;
}


GL_FUNC(glDeleteTextures, args, ac) {
    GL_CHK_ARG(2, glDeleteTextures(n, textures));
    pushException("Not implemented function glDeleteTextures(...)");
    return 0;
}


GL_FUNC(glDepthFunc, args, ac) {
    GL_CHK_ARG(1, glDepthFunc(func));
    GLenum __gen_func = (GLenum) intValue(args[1]);
    glDepthFunc(__gen_func);
    return 0;
}


GL_FUNC(glDepthMask, args, ac) {
    GL_CHK_ARG(1, glDepthMask(flag));
    GLboolean __gen_flag = (GLboolean) intValue(args[1]);
    glDepthMask(__gen_flag);
    return 0;
}


GL_FUNC(glDepthRange, args, ac) {
    GL_CHK_ARG(2, glDepthRange(zNear, zFar));
    GLclampd __gen_zNear = (GLclampd) doubleValue(args[1]);
    GLclampd __gen_zFar = (GLclampd) doubleValue(args[2]);
    glDepthRange(__gen_zNear, __gen_zFar);
    return 0;
}


GL_FUNC(glDisable, args, ac) {
    GL_CHK_ARG(1, glDisable(cap));
    GLenum __gen_cap = (GLenum) intValue(args[1]);
    glDisable(__gen_cap);
    return 0;
}


GL_FUNC(glDisableClientState, args, ac) {
    GL_CHK_ARG(1, glDisableClientState(array));
    GLenum __gen_array = (GLenum) intValue(args[1]);
    glDisableClientState(__gen_array);
    return 0;
}


GL_FUNC(glDrawArrays, args, ac) {
    GL_CHK_ARG(3, glDrawArrays(mode, first, count));
    GLenum __gen_mode = (GLenum) intValue(args[1]);
    GLint __gen_first = (GLint) intValue(args[2]);
    GLsizei __gen_count = (GLsizei) intValue(args[3]);
    glDrawArrays(__gen_mode, __gen_first, __gen_count);
    return 0;
}


GL_FUNC(glDrawBuffer, args, ac) {
    GL_CHK_ARG(1, glDrawBuffer(mode));
    GLenum __gen_mode = (GLenum) intValue(args[1]);
    glDrawBuffer(__gen_mode);
    return 0;
}


GL_FUNC(glDrawElements, args, ac) {
    GL_CHK_ARG(4, glDrawElements(mode, count, type, indices));
    pushException("Not implemented function glDrawElements(...)");
    return 0;
}


GL_FUNC(glDrawPixels, args, ac) {
    GL_CHK_ARG(5, glDrawPixels(width, height, format, type, pixels));
    pushException("Not implemented function glDrawPixels(...)");
    return 0;
}


GL_FUNC(glEdgeFlag, args, ac) {
    GL_CHK_ARG(1, glEdgeFlag(flag));
    GLboolean __gen_flag = (GLboolean) intValue(args[1]);
    glEdgeFlag(__gen_flag);
    return 0;
}


GL_FUNC(glEdgeFlagPointer, args, ac) {
    GL_CHK_ARG(2, glEdgeFlagPointer(stride, pointer));
    pushException("Not implemented function glEdgeFlagPointer(...)");
    return 0;
}


GL_FUNC(glEdgeFlagv, args, ac) {
    GL_CHK_ARG(1, glEdgeFlagv(flag));
    pushException("Not implemented function glEdgeFlagv(...)");
    return 0;
}


GL_FUNC(glEnable, args, ac) {
    GL_CHK_ARG(1, glEnable(cap));
    GLenum __gen_cap = (GLenum) intValue(args[1]);
    glEnable(__gen_cap);
    return 0;
}


GL_FUNC(glEnableClientState, args, ac) {
    GL_CHK_ARG(1, glEnableClientState(array));
    GLenum __gen_array = (GLenum) intValue(args[1]);
    glEnableClientState(__gen_array);
    return 0;
}


GL_FUNC(glEnd, args, ac) {
    glEnd();
    return 0;
}


GL_FUNC(glEndList, args, ac) {
    glEndList();
    return 0;
}


GL_FUNC(glEvalCoord1d, args, ac) {
    GL_CHK_ARG(1, glEvalCoord1d(u));
    GLdouble __gen_u = (GLdouble) doubleValue(args[1]);
    glEvalCoord1d(__gen_u);
    return 0;
}


GL_FUNC(glEvalCoord1dv, args, ac) {
    GL_CHK_ARG(1, glEvalCoord1dv(u));
    pushException("Not implemented function glEvalCoord1dv(...)");
    return 0;
}


GL_FUNC(glEvalCoord1f, args, ac) {
    GL_CHK_ARG(1, glEvalCoord1f(u));
    GLfloat __gen_u = (GLfloat) doubleValue(args[1]);
    glEvalCoord1f(__gen_u);
    return 0;
}


GL_FUNC(glEvalCoord1fv, args, ac) {
    GL_CHK_ARG(1, glEvalCoord1fv(u));
    pushException("Not implemented function glEvalCoord1fv(...)");
    return 0;
}


GL_FUNC(glEvalCoord2d, args, ac) {
    GL_CHK_ARG(2, glEvalCoord2d(u, v));
    GLdouble __gen_u = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_v = (GLdouble) doubleValue(args[2]);
    glEvalCoord2d(__gen_u, __gen_v);
    return 0;
}


GL_FUNC(glEvalCoord2dv, args, ac) {
    GL_CHK_ARG(1, glEvalCoord2dv(u));
    pushException("Not implemented function glEvalCoord2dv(...)");
    return 0;
}


GL_FUNC(glEvalCoord2f, args, ac) {
    GL_CHK_ARG(2, glEvalCoord2f(u, v));
    GLfloat __gen_u = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_v = (GLfloat) doubleValue(args[2]);
    glEvalCoord2f(__gen_u, __gen_v);
    return 0;
}


GL_FUNC(glEvalCoord2fv, args, ac) {
    GL_CHK_ARG(1, glEvalCoord2fv(u));
    pushException("Not implemented function glEvalCoord2fv(...)");
    return 0;
}


GL_FUNC(glEvalMesh1, args, ac) {
    GL_CHK_ARG(3, glEvalMesh1(mode, i1, i2));
    GLenum __gen_mode = (GLenum) intValue(args[1]);
    GLint __gen_i1 = (GLint) intValue(args[2]);
    GLint __gen_i2 = (GLint) intValue(args[3]);
    glEvalMesh1(__gen_mode, __gen_i1, __gen_i2);
    return 0;
}


GL_FUNC(glEvalMesh2, args, ac) {
    GL_CHK_ARG(5, glEvalMesh2(mode, i1, i2, j1, j2));
    GLenum __gen_mode = (GLenum) intValue(args[1]);
    GLint __gen_i1 = (GLint) intValue(args[2]);
    GLint __gen_i2 = (GLint) intValue(args[3]);
    GLint __gen_j1 = (GLint) intValue(args[4]);
    GLint __gen_j2 = (GLint) intValue(args[5]);
    glEvalMesh2(__gen_mode, __gen_i1, __gen_i2, __gen_j1, __gen_j2);
    return 0;
}


GL_FUNC(glEvalPoint1, args, ac) {
    GL_CHK_ARG(1, glEvalPoint1(i));
    GLint __gen_i = (GLint) intValue(args[1]);
    glEvalPoint1(__gen_i);
    return 0;
}


GL_FUNC(glEvalPoint2, args, ac) {
    GL_CHK_ARG(2, glEvalPoint2(i, j));
    GLint __gen_i = (GLint) intValue(args[1]);
    GLint __gen_j = (GLint) intValue(args[2]);
    glEvalPoint2(__gen_i, __gen_j);
    return 0;
}


GL_FUNC(glFeedbackBuffer, args, ac) {
    GL_CHK_ARG(3, glFeedbackBuffer(size, type, buffer));
    pushException("Not implemented function glFeedbackBuffer(...)");
    return 0;
}


GL_FUNC(glFinish, args, ac) {
    glFinish();
    return 0;
}


GL_FUNC(glFlush, args, ac) {
    glFlush();
    return 0;
}


GL_FUNC(glFogf, args, ac) {
    GL_CHK_ARG(2, glFogf(pname, param));
    GLenum __gen_pname = (GLenum) intValue(args[1]);
    GLfloat __gen_param = (GLfloat) doubleValue(args[2]);
    glFogf(__gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glFogfv, args, ac) {
    GL_CHK_ARG(2, glFogfv(pname, params));
    pushException("Not implemented function glFogfv(...)");
    return 0;
}


GL_FUNC(glFogi, args, ac) {
    GL_CHK_ARG(2, glFogi(pname, param));
    GLenum __gen_pname = (GLenum) intValue(args[1]);
    GLint __gen_param = (GLint) intValue(args[2]);
    glFogi(__gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glFogiv, args, ac) {
    GL_CHK_ARG(2, glFogiv(pname, params));
    pushException("Not implemented function glFogiv(...)");
    return 0;
}


GL_FUNC(glFrontFace, args, ac) {
    GL_CHK_ARG(1, glFrontFace(mode));
    GLenum __gen_mode = (GLenum) intValue(args[1]);
    glFrontFace(__gen_mode);
    return 0;
}


GL_FUNC(glFrustum, args, ac) {
    GL_CHK_ARG(6, glFrustum(left, right, bottom, top, zNear, zFar));
    GLdouble __gen_left = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_right = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_bottom = (GLdouble) doubleValue(args[3]);
    GLdouble __gen_top = (GLdouble) doubleValue(args[4]);
    GLdouble __gen_zNear = (GLdouble) doubleValue(args[5]);
    GLdouble __gen_zFar = (GLdouble) doubleValue(args[6]);
    glFrustum(__gen_left, __gen_right, __gen_bottom, __gen_top, __gen_zNear, __gen_zFar);
    return 0;
}


GL_FUNC(glGenLists, args, ac) {
    GL_CHK_ARG(1, glGenLists(range));
    GLsizei __gen_range = (GLsizei) intValue(args[1]);
    auto __return_glGenLists = glGenLists(__gen_range);
    return wrapJs(__return_glGenLists);
}


GL_FUNC(glGenTextures, args, ac) {
    GL_CHK_ARG(2, glGenTextures(n, textures));
    pushException("Not implemented function glGenTextures(...)");
    return 0;
}


GL_FUNC(glGetBooleanv, args, ac) {
    GL_CHK_ARG(2, glGetBooleanv(pname, params));
    pushException("Not implemented function glGetBooleanv(...)");
    return 0;
}


GL_FUNC(glGetClipPlane, args, ac) {
    GL_CHK_ARG(2, glGetClipPlane(plane, equation));
    pushException("Not implemented function glGetClipPlane(...)");
    return 0;
}


GL_FUNC(glGetDoublev, args, ac) {
    GL_CHK_ARG(2, glGetDoublev(pname, params));
    pushException("Not implemented function glGetDoublev(...)");
    return 0;
}


GL_FUNC(glGetError, args, ac) {
    auto __return_glGetError = glGetError();
    return wrapJs(__return_glGetError);
}


GL_FUNC(glGetFloatv, args, ac) {
    GL_CHK_ARG(2, glGetFloatv(pname, params));
    pushException("Not implemented function glGetFloatv(...)");
    return 0;
}


GL_FUNC(glGetIntegerv, args, ac) {
    GL_CHK_ARG(2, glGetIntegerv(pname, params));
    pushException("Not implemented function glGetIntegerv(...)");
    return 0;
}


GL_FUNC(glGetLightfv, args, ac) {
    GL_CHK_ARG(3, glGetLightfv(light, pname, params));
    pushException("Not implemented function glGetLightfv(...)");
    return 0;
}


GL_FUNC(glGetLightiv, args, ac) {
    GL_CHK_ARG(3, glGetLightiv(light, pname, params));
    pushException("Not implemented function glGetLightiv(...)");
    return 0;
}


GL_FUNC(glGetMapdv, args, ac) {
    GL_CHK_ARG(3, glGetMapdv(target, query, v));
    pushException("Not implemented function glGetMapdv(...)");
    return 0;
}


GL_FUNC(glGetMapfv, args, ac) {
    GL_CHK_ARG(3, glGetMapfv(target, query, v));
    pushException("Not implemented function glGetMapfv(...)");
    return 0;
}


GL_FUNC(glGetMapiv, args, ac) {
    GL_CHK_ARG(3, glGetMapiv(target, query, v));
    pushException("Not implemented function glGetMapiv(...)");
    return 0;
}


GL_FUNC(glGetMaterialfv, args, ac) {
    GL_CHK_ARG(3, glGetMaterialfv(face, pname, params));
    pushException("Not implemented function glGetMaterialfv(...)");
    return 0;
}


GL_FUNC(glGetMaterialiv, args, ac) {
    GL_CHK_ARG(3, glGetMaterialiv(face, pname, params));
    pushException("Not implemented function glGetMaterialiv(...)");
    return 0;
}


GL_FUNC(glGetPixelMapfv, args, ac) {
    GL_CHK_ARG(2, glGetPixelMapfv(map, values));
    pushException("Not implemented function glGetPixelMapfv(...)");
    return 0;
}


GL_FUNC(glGetPixelMapuiv, args, ac) {
    GL_CHK_ARG(2, glGetPixelMapuiv(map, values));
    pushException("Not implemented function glGetPixelMapuiv(...)");
    return 0;
}


GL_FUNC(glGetPixelMapusv, args, ac) {
    GL_CHK_ARG(2, glGetPixelMapusv(map, values));
    pushException("Not implemented function glGetPixelMapusv(...)");
    return 0;
}


GL_FUNC(glGetPointerv, args, ac) {
    GL_CHK_ARG(2, glGetPointerv(pname, params));
    pushException("Not implemented function glGetPointerv(...)");
    return 0;
}


GL_FUNC(glGetPolygonStipple, args, ac) {
    GL_CHK_ARG(1, glGetPolygonStipple(mask));
    pushException("Not implemented function glGetPolygonStipple(...)");
    return 0;
}


GL_FUNC(glGetString, args, ac) {
    GL_CHK_ARG(1, glGetString(name));
    GLenum __gen_name = (GLenum) intValue(args[1]);
    auto __return_glGetString = glGetString(__gen_name);
    return wrapJs(__return_glGetString);
}


GL_FUNC(glGetTexEnvfv, args, ac) {
    GL_CHK_ARG(3, glGetTexEnvfv(target, pname, params));
    pushException("Not implemented function glGetTexEnvfv(...)");
    return 0;
}


GL_FUNC(glGetTexEnviv, args, ac) {
    GL_CHK_ARG(3, glGetTexEnviv(target, pname, params));
    pushException("Not implemented function glGetTexEnviv(...)");
    return 0;
}


GL_FUNC(glGetTexGendv, args, ac) {
    GL_CHK_ARG(3, glGetTexGendv(coord, pname, params));
    pushException("Not implemented function glGetTexGendv(...)");
    return 0;
}


GL_FUNC(glGetTexGenfv, args, ac) {
    GL_CHK_ARG(3, glGetTexGenfv(coord, pname, params));
    pushException("Not implemented function glGetTexGenfv(...)");
    return 0;
}


GL_FUNC(glGetTexGeniv, args, ac) {
    GL_CHK_ARG(3, glGetTexGeniv(coord, pname, params));
    pushException("Not implemented function glGetTexGeniv(...)");
    return 0;
}


GL_FUNC(glGetTexImage, args, ac) {
    GL_CHK_ARG(5, glGetTexImage(target, level, format, type, pixels));
    pushException("Not implemented function glGetTexImage(...)");
    return 0;
}


GL_FUNC(glGetTexLevelParameterfv, args, ac) {
    GL_CHK_ARG(4, glGetTexLevelParameterfv(target, level, pname, params));
    pushException("Not implemented function glGetTexLevelParameterfv(...)");
    return 0;
}


GL_FUNC(glGetTexLevelParameteriv, args, ac) {
    GL_CHK_ARG(4, glGetTexLevelParameteriv(target, level, pname, params));
    pushException("Not implemented function glGetTexLevelParameteriv(...)");
    return 0;
}


GL_FUNC(glGetTexParameterfv, args, ac) {
    GL_CHK_ARG(3, glGetTexParameterfv(target, pname, params));
    pushException("Not implemented function glGetTexParameterfv(...)");
    return 0;
}


GL_FUNC(glGetTexParameteriv, args, ac) {
    GL_CHK_ARG(3, glGetTexParameteriv(target, pname, params));
    pushException("Not implemented function glGetTexParameteriv(...)");
    return 0;
}


GL_FUNC(glHint, args, ac) {
    GL_CHK_ARG(2, glHint(target, mode));
    GLenum __gen_target = (GLenum) intValue(args[1]);
    GLenum __gen_mode = (GLenum) intValue(args[2]);
    glHint(__gen_target, __gen_mode);
    return 0;
}


GL_FUNC(glIndexMask, args, ac) {
    GL_CHK_ARG(1, glIndexMask(mask));
    GLuint __gen_mask = (GLuint) intValue(args[1]);
    glIndexMask(__gen_mask);
    return 0;
}


GL_FUNC(glIndexPointer, args, ac) {
    GL_CHK_ARG(3, glIndexPointer(type, stride, pointer));
    pushException("Not implemented function glIndexPointer(...)");
    return 0;
}


GL_FUNC(glIndexd, args, ac) {
    GL_CHK_ARG(1, glIndexd(c));
    GLdouble __gen_c = (GLdouble) doubleValue(args[1]);
    glIndexd(__gen_c);
    return 0;
}


GL_FUNC(glIndexdv, args, ac) {
    GL_CHK_ARG(1, glIndexdv(c));
    pushException("Not implemented function glIndexdv(...)");
    return 0;
}


GL_FUNC(glIndexf, args, ac) {
    GL_CHK_ARG(1, glIndexf(c));
    GLfloat __gen_c = (GLfloat) doubleValue(args[1]);
    glIndexf(__gen_c);
    return 0;
}


GL_FUNC(glIndexfv, args, ac) {
    GL_CHK_ARG(1, glIndexfv(c));
    pushException("Not implemented function glIndexfv(...)");
    return 0;
}


GL_FUNC(glIndexi, args, ac) {
    GL_CHK_ARG(1, glIndexi(c));
    GLint __gen_c = (GLint) intValue(args[1]);
    glIndexi(__gen_c);
    return 0;
}


GL_FUNC(glIndexiv, args, ac) {
    GL_CHK_ARG(1, glIndexiv(c));
    pushException("Not implemented function glIndexiv(...)");
    return 0;
}


GL_FUNC(glIndexs, args, ac) {
    GL_CHK_ARG(1, glIndexs(c));
    GLshort __gen_c = (GLshort) intValue(args[1]);
    glIndexs(__gen_c);
    return 0;
}


GL_FUNC(glIndexsv, args, ac) {
    GL_CHK_ARG(1, glIndexsv(c));
    pushException("Not implemented function glIndexsv(...)");
    return 0;
}


GL_FUNC(glIndexub, args, ac) {
    GL_CHK_ARG(1, glIndexub(c));
    GLubyte __gen_c = (GLubyte) intValue(args[1]);
    glIndexub(__gen_c);
    return 0;
}


GL_FUNC(glIndexubv, args, ac) {
    GL_CHK_ARG(1, glIndexubv(c));
    pushException("Not implemented function glIndexubv(...)");
    return 0;
}


GL_FUNC(glInitNames, args, ac) {
    glInitNames();
    return 0;
}


GL_FUNC(glInterleavedArrays, args, ac) {
    GL_CHK_ARG(3, glInterleavedArrays(format, stride, pointer));
    pushException("Not implemented function glInterleavedArrays(...)");
    return 0;
}


GL_FUNC(glIsEnabled, args, ac) {
    GL_CHK_ARG(1, glIsEnabled(cap));
    GLenum __gen_cap = (GLenum) intValue(args[1]);
    auto __return_glIsEnabled = glIsEnabled(__gen_cap);
    return wrapJs(__return_glIsEnabled);
}


GL_FUNC(glIsList, args, ac) {
    GL_CHK_ARG(1, glIsList(list));
    GLuint __gen_list = (GLuint) intValue(args[1]);
    auto __return_glIsList = glIsList(__gen_list);
    return wrapJs(__return_glIsList);
}


GL_FUNC(glIsTexture, args, ac) {
    GL_CHK_ARG(1, glIsTexture(texture));
    GLuint __gen_texture = (GLuint) intValue(args[1]);
    auto __return_glIsTexture = glIsTexture(__gen_texture);
    return wrapJs(__return_glIsTexture);
}


GL_FUNC(glLightModelf, args, ac) {
    GL_CHK_ARG(2, glLightModelf(pname, param));
    GLenum __gen_pname = (GLenum) intValue(args[1]);
    GLfloat __gen_param = (GLfloat) doubleValue(args[2]);
    glLightModelf(__gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glLightModelfv, args, ac) {
    GL_CHK_ARG(2, glLightModelfv(pname, params));
    pushException("Not implemented function glLightModelfv(...)");
    return 0;
}


GL_FUNC(glLightModeli, args, ac) {
    GL_CHK_ARG(2, glLightModeli(pname, param));
    GLenum __gen_pname = (GLenum) intValue(args[1]);
    GLint __gen_param = (GLint) intValue(args[2]);
    glLightModeli(__gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glLightModeliv, args, ac) {
    GL_CHK_ARG(2, glLightModeliv(pname, params));
    pushException("Not implemented function glLightModeliv(...)");
    return 0;
}


GL_FUNC(glLightf, args, ac) {
    GL_CHK_ARG(3, glLightf(light, pname, param));
    GLenum __gen_light = (GLenum) intValue(args[1]);
    GLenum __gen_pname = (GLenum) intValue(args[2]);
    GLfloat __gen_param = (GLfloat) doubleValue(args[3]);
    glLightf(__gen_light, __gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glLightfv, args, ac) {
    GL_CHK_ARG(3, glLightfv(light, pname, params));
    pushException("Not implemented function glLightfv(...)");
    return 0;
}


GL_FUNC(glLighti, args, ac) {
    GL_CHK_ARG(3, glLighti(light, pname, param));
    GLenum __gen_light = (GLenum) intValue(args[1]);
    GLenum __gen_pname = (GLenum) intValue(args[2]);
    GLint __gen_param = (GLint) intValue(args[3]);
    glLighti(__gen_light, __gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glLightiv, args, ac) {
    GL_CHK_ARG(3, glLightiv(light, pname, params));
    pushException("Not implemented function glLightiv(...)");
    return 0;
}


GL_FUNC(glLineStipple, args, ac) {
    GL_CHK_ARG(2, glLineStipple(factor, pattern));
    GLint __gen_factor = (GLint) intValue(args[1]);
    GLushort __gen_pattern = (GLushort) intValue(args[2]);
    glLineStipple(__gen_factor, __gen_pattern);
    return 0;
}


GL_FUNC(glLineWidth, args, ac) {
    GL_CHK_ARG(1, glLineWidth(width));
    GLfloat __gen_width = (GLfloat) doubleValue(args[1]);
    glLineWidth(__gen_width);
    return 0;
}


GL_FUNC(glListBase, args, ac) {
    GL_CHK_ARG(1, glListBase(base));
    GLuint __gen_base = (GLuint) intValue(args[1]);
    glListBase(__gen_base);
    return 0;
}


GL_FUNC(glLoadIdentity, args, ac) {
    glLoadIdentity();
    return 0;
}


GL_FUNC(glLoadMatrixd, args, ac) {
    GL_CHK_ARG(1, glLoadMatrixd(m));
    pushException("Not implemented function glLoadMatrixd(...)");
    return 0;
}


GL_FUNC(glLoadMatrixf, args, ac) {
    GL_CHK_ARG(1, glLoadMatrixf(m));
    pushException("Not implemented function glLoadMatrixf(...)");
    return 0;
}


GL_FUNC(glLoadName, args, ac) {
    GL_CHK_ARG(1, glLoadName(name));
    GLuint __gen_name = (GLuint) intValue(args[1]);
    glLoadName(__gen_name);
    return 0;
}


GL_FUNC(glLogicOp, args, ac) {
    GL_CHK_ARG(1, glLogicOp(opcode));
    GLenum __gen_opcode = (GLenum) intValue(args[1]);
    glLogicOp(__gen_opcode);
    return 0;
}


GL_FUNC(glMap1d, args, ac) {
    GL_CHK_ARG(6, glMap1d(target, u1, u2, stride, order, points));
    pushException("Not implemented function glMap1d(...)");
    return 0;
}


GL_FUNC(glMap1f, args, ac) {
    GL_CHK_ARG(6, glMap1f(target, u1, u2, stride, order, points));
    pushException("Not implemented function glMap1f(...)");
    return 0;
}


GL_FUNC(glMap2d, args, ac) {
    GL_CHK_ARG(10, glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points));
    pushException("Not implemented function glMap2d(...)");
    return 0;
}


GL_FUNC(glMap2f, args, ac) {
    GL_CHK_ARG(10, glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points));
    pushException("Not implemented function glMap2f(...)");
    return 0;
}


GL_FUNC(glMapGrid1d, args, ac) {
    GL_CHK_ARG(3, glMapGrid1d(un, u1, u2));
    GLint __gen_un = (GLint) intValue(args[1]);
    GLdouble __gen_u1 = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_u2 = (GLdouble) doubleValue(args[3]);
    glMapGrid1d(__gen_un, __gen_u1, __gen_u2);
    return 0;
}


GL_FUNC(glMapGrid1f, args, ac) {
    GL_CHK_ARG(3, glMapGrid1f(un, u1, u2));
    GLint __gen_un = (GLint) intValue(args[1]);
    GLfloat __gen_u1 = (GLfloat) doubleValue(args[2]);
    GLfloat __gen_u2 = (GLfloat) doubleValue(args[3]);
    glMapGrid1f(__gen_un, __gen_u1, __gen_u2);
    return 0;
}


GL_FUNC(glMapGrid2d, args, ac) {
    GL_CHK_ARG(6, glMapGrid2d(un, u1, u2, vn, v1, v2));
    GLint __gen_un = (GLint) intValue(args[1]);
    GLdouble __gen_u1 = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_u2 = (GLdouble) doubleValue(args[3]);
    GLint __gen_vn = (GLint) intValue(args[4]);
    GLdouble __gen_v1 = (GLdouble) doubleValue(args[5]);
    GLdouble __gen_v2 = (GLdouble) doubleValue(args[6]);
    glMapGrid2d(__gen_un, __gen_u1, __gen_u2, __gen_vn, __gen_v1, __gen_v2);
    return 0;
}


GL_FUNC(glMapGrid2f, args, ac) {
    GL_CHK_ARG(6, glMapGrid2f(un, u1, u2, vn, v1, v2));
    GLint __gen_un = (GLint) intValue(args[1]);
    GLfloat __gen_u1 = (GLfloat) doubleValue(args[2]);
    GLfloat __gen_u2 = (GLfloat) doubleValue(args[3]);
    GLint __gen_vn = (GLint) intValue(args[4]);
    GLfloat __gen_v1 = (GLfloat) doubleValue(args[5]);
    GLfloat __gen_v2 = (GLfloat) doubleValue(args[6]);
    glMapGrid2f(__gen_un, __gen_u1, __gen_u2, __gen_vn, __gen_v1, __gen_v2);
    return 0;
}


GL_FUNC(glMaterialf, args, ac) {
    GL_CHK_ARG(3, glMaterialf(face, pname, param));
    GLenum __gen_face = (GLenum) intValue(args[1]);
    GLenum __gen_pname = (GLenum) intValue(args[2]);
    GLfloat __gen_param = (GLfloat) doubleValue(args[3]);
    glMaterialf(__gen_face, __gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glMaterialfv, args, ac) {
    GL_CHK_ARG(3, glMaterialfv(face, pname, params));
    pushException("Not implemented function glMaterialfv(...)");
    return 0;
}


GL_FUNC(glMateriali, args, ac) {
    GL_CHK_ARG(3, glMateriali(face, pname, param));
    GLenum __gen_face = (GLenum) intValue(args[1]);
    GLenum __gen_pname = (GLenum) intValue(args[2]);
    GLint __gen_param = (GLint) intValue(args[3]);
    glMateriali(__gen_face, __gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glMaterialiv, args, ac) {
    GL_CHK_ARG(3, glMaterialiv(face, pname, params));
    pushException("Not implemented function glMaterialiv(...)");
    return 0;
}


GL_FUNC(glMatrixMode, args, ac) {
    GL_CHK_ARG(1, glMatrixMode(mode));
    GLenum __gen_mode = (GLenum) intValue(args[1]);
    glMatrixMode(__gen_mode);
    return 0;
}


GL_FUNC(glMultMatrixd, args, ac) {
    GL_CHK_ARG(1, glMultMatrixd(m));
    pushException("Not implemented function glMultMatrixd(...)");
    return 0;
}


GL_FUNC(glMultMatrixf, args, ac) {
    GL_CHK_ARG(1, glMultMatrixf(m));
    pushException("Not implemented function glMultMatrixf(...)");
    return 0;
}


GL_FUNC(glNewList, args, ac) {
    GL_CHK_ARG(2, glNewList(list, mode));
    GLuint __gen_list = (GLuint) intValue(args[1]);
    GLenum __gen_mode = (GLenum) intValue(args[2]);
    glNewList(__gen_list, __gen_mode);
    return 0;
}


GL_FUNC(glNormal3b, args, ac) {
    GL_CHK_ARG(3, glNormal3b(nx, ny, nz));
    GLbyte __gen_nx = (GLbyte) intValue(args[1]);
    GLbyte __gen_ny = (GLbyte) intValue(args[2]);
    GLbyte __gen_nz = (GLbyte) intValue(args[3]);
    glNormal3b(__gen_nx, __gen_ny, __gen_nz);
    return 0;
}


GL_FUNC(glNormal3bv, args, ac) {
    GL_CHK_ARG(1, glNormal3bv(v));
    pushException("Not implemented function glNormal3bv(...)");
    return 0;
}


GL_FUNC(glNormal3d, args, ac) {
    GL_CHK_ARG(3, glNormal3d(nx, ny, nz));
    GLdouble __gen_nx = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_ny = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_nz = (GLdouble) doubleValue(args[3]);
    glNormal3d(__gen_nx, __gen_ny, __gen_nz);
    return 0;
}


GL_FUNC(glNormal3dv, args, ac) {
    GL_CHK_ARG(1, glNormal3dv(v));
    pushException("Not implemented function glNormal3dv(...)");
    return 0;
}


GL_FUNC(glNormal3f, args, ac) {
    GL_CHK_ARG(3, glNormal3f(nx, ny, nz));
    GLfloat __gen_nx = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_ny = (GLfloat) doubleValue(args[2]);
    GLfloat __gen_nz = (GLfloat) doubleValue(args[3]);
    glNormal3f(__gen_nx, __gen_ny, __gen_nz);
    return 0;
}


GL_FUNC(glNormal3fv, args, ac) {
    GL_CHK_ARG(1, glNormal3fv(v));
    pushException("Not implemented function glNormal3fv(...)");
    return 0;
}


GL_FUNC(glNormal3i, args, ac) {
    GL_CHK_ARG(3, glNormal3i(nx, ny, nz));
    GLint __gen_nx = (GLint) intValue(args[1]);
    GLint __gen_ny = (GLint) intValue(args[2]);
    GLint __gen_nz = (GLint) intValue(args[3]);
    glNormal3i(__gen_nx, __gen_ny, __gen_nz);
    return 0;
}


GL_FUNC(glNormal3iv, args, ac) {
    GL_CHK_ARG(1, glNormal3iv(v));
    pushException("Not implemented function glNormal3iv(...)");
    return 0;
}


GL_FUNC(glNormal3s, args, ac) {
    GL_CHK_ARG(3, glNormal3s(nx, ny, nz));
    GLshort __gen_nx = (GLshort) intValue(args[1]);
    GLshort __gen_ny = (GLshort) intValue(args[2]);
    GLshort __gen_nz = (GLshort) intValue(args[3]);
    glNormal3s(__gen_nx, __gen_ny, __gen_nz);
    return 0;
}


GL_FUNC(glNormal3sv, args, ac) {
    GL_CHK_ARG(1, glNormal3sv(v));
    pushException("Not implemented function glNormal3sv(...)");
    return 0;
}


GL_FUNC(glNormalPointer, args, ac) {
    GL_CHK_ARG(3, glNormalPointer(type, stride, pointer));
    pushException("Not implemented function glNormalPointer(...)");
    return 0;
}


GL_FUNC(glOrtho, args, ac) {
    GL_CHK_ARG(6, glOrtho(left, right, bottom, top, zNear, zFar));
    GLdouble __gen_left = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_right = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_bottom = (GLdouble) doubleValue(args[3]);
    GLdouble __gen_top = (GLdouble) doubleValue(args[4]);
    GLdouble __gen_zNear = (GLdouble) doubleValue(args[5]);
    GLdouble __gen_zFar = (GLdouble) doubleValue(args[6]);
    glOrtho(__gen_left, __gen_right, __gen_bottom, __gen_top, __gen_zNear, __gen_zFar);
    return 0;
}


GL_FUNC(glPassThrough, args, ac) {
    GL_CHK_ARG(1, glPassThrough(token));
    GLfloat __gen_token = (GLfloat) doubleValue(args[1]);
    glPassThrough(__gen_token);
    return 0;
}


GL_FUNC(glPixelMapfv, args, ac) {
    GL_CHK_ARG(3, glPixelMapfv(map, mapsize, values));
    pushException("Not implemented function glPixelMapfv(...)");
    return 0;
}


GL_FUNC(glPixelMapuiv, args, ac) {
    GL_CHK_ARG(3, glPixelMapuiv(map, mapsize, values));
    pushException("Not implemented function glPixelMapuiv(...)");
    return 0;
}


GL_FUNC(glPixelMapusv, args, ac) {
    GL_CHK_ARG(3, glPixelMapusv(map, mapsize, values));
    pushException("Not implemented function glPixelMapusv(...)");
    return 0;
}


GL_FUNC(glPixelStoref, args, ac) {
    GL_CHK_ARG(2, glPixelStoref(pname, param));
    GLenum __gen_pname = (GLenum) intValue(args[1]);
    GLfloat __gen_param = (GLfloat) doubleValue(args[2]);
    glPixelStoref(__gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glPixelStorei, args, ac) {
    GL_CHK_ARG(2, glPixelStorei(pname, param));
    GLenum __gen_pname = (GLenum) intValue(args[1]);
    GLint __gen_param = (GLint) intValue(args[2]);
    glPixelStorei(__gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glPixelTransferf, args, ac) {
    GL_CHK_ARG(2, glPixelTransferf(pname, param));
    GLenum __gen_pname = (GLenum) intValue(args[1]);
    GLfloat __gen_param = (GLfloat) doubleValue(args[2]);
    glPixelTransferf(__gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glPixelTransferi, args, ac) {
    GL_CHK_ARG(2, glPixelTransferi(pname, param));
    GLenum __gen_pname = (GLenum) intValue(args[1]);
    GLint __gen_param = (GLint) intValue(args[2]);
    glPixelTransferi(__gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glPixelZoom, args, ac) {
    GL_CHK_ARG(2, glPixelZoom(xfactor, yfactor));
    GLfloat __gen_xfactor = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_yfactor = (GLfloat) doubleValue(args[2]);
    glPixelZoom(__gen_xfactor, __gen_yfactor);
    return 0;
}


GL_FUNC(glPointSize, args, ac) {
    GL_CHK_ARG(1, glPointSize(size));
    GLfloat __gen_size = (GLfloat) doubleValue(args[1]);
    glPointSize(__gen_size);
    return 0;
}


GL_FUNC(glPolygonMode, args, ac) {
    GL_CHK_ARG(2, glPolygonMode(face, mode));
    GLenum __gen_face = (GLenum) intValue(args[1]);
    GLenum __gen_mode = (GLenum) intValue(args[2]);
    glPolygonMode(__gen_face, __gen_mode);
    return 0;
}


GL_FUNC(glPolygonOffset, args, ac) {
    GL_CHK_ARG(2, glPolygonOffset(factor, units));
    GLfloat __gen_factor = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_units = (GLfloat) doubleValue(args[2]);
    glPolygonOffset(__gen_factor, __gen_units);
    return 0;
}


GL_FUNC(glPolygonStipple, args, ac) {
    GL_CHK_ARG(1, glPolygonStipple(mask));
    pushException("Not implemented function glPolygonStipple(...)");
    return 0;
}


GL_FUNC(glPopAttrib, args, ac) {
    glPopAttrib();
    return 0;
}


GL_FUNC(glPopClientAttrib, args, ac) {
    glPopClientAttrib();
    return 0;
}


GL_FUNC(glPopMatrix, args, ac) {
    glPopMatrix();
    return 0;
}


GL_FUNC(glPopName, args, ac) {
    glPopName();
    return 0;
}


GL_FUNC(glPrioritizeTextures, args, ac) {
    GL_CHK_ARG(3, glPrioritizeTextures(n, textures, priorities));
    pushException("Not implemented function glPrioritizeTextures(...)");
    return 0;
}


GL_FUNC(glPushAttrib, args, ac) {
    GL_CHK_ARG(1, glPushAttrib(mask));
    GLbitfield __gen_mask = (GLbitfield) intValue(args[1]);
    glPushAttrib(__gen_mask);
    return 0;
}


GL_FUNC(glPushClientAttrib, args, ac) {
    GL_CHK_ARG(1, glPushClientAttrib(mask));
    GLbitfield __gen_mask = (GLbitfield) intValue(args[1]);
    glPushClientAttrib(__gen_mask);
    return 0;
}


GL_FUNC(glPushMatrix, args, ac) {
    glPushMatrix();
    return 0;
}


GL_FUNC(glPushName, args, ac) {
    GL_CHK_ARG(1, glPushName(name));
    GLuint __gen_name = (GLuint) intValue(args[1]);
    glPushName(__gen_name);
    return 0;
}


GL_FUNC(glRasterPos2d, args, ac) {
    GL_CHK_ARG(2, glRasterPos2d(x, y));
    GLdouble __gen_x = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_y = (GLdouble) doubleValue(args[2]);
    glRasterPos2d(__gen_x, __gen_y);
    return 0;
}


GL_FUNC(glRasterPos2dv, args, ac) {
    GL_CHK_ARG(1, glRasterPos2dv(v));
    pushException("Not implemented function glRasterPos2dv(...)");
    return 0;
}


GL_FUNC(glRasterPos2f, args, ac) {
    GL_CHK_ARG(2, glRasterPos2f(x, y));
    GLfloat __gen_x = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_y = (GLfloat) doubleValue(args[2]);
    glRasterPos2f(__gen_x, __gen_y);
    return 0;
}


GL_FUNC(glRasterPos2fv, args, ac) {
    GL_CHK_ARG(1, glRasterPos2fv(v));
    pushException("Not implemented function glRasterPos2fv(...)");
    return 0;
}


GL_FUNC(glRasterPos2i, args, ac) {
    GL_CHK_ARG(2, glRasterPos2i(x, y));
    GLint __gen_x = (GLint) intValue(args[1]);
    GLint __gen_y = (GLint) intValue(args[2]);
    glRasterPos2i(__gen_x, __gen_y);
    return 0;
}


GL_FUNC(glRasterPos2iv, args, ac) {
    GL_CHK_ARG(1, glRasterPos2iv(v));
    pushException("Not implemented function glRasterPos2iv(...)");
    return 0;
}


GL_FUNC(glRasterPos2s, args, ac) {
    GL_CHK_ARG(2, glRasterPos2s(x, y));
    GLshort __gen_x = (GLshort) intValue(args[1]);
    GLshort __gen_y = (GLshort) intValue(args[2]);
    glRasterPos2s(__gen_x, __gen_y);
    return 0;
}


GL_FUNC(glRasterPos2sv, args, ac) {
    GL_CHK_ARG(1, glRasterPos2sv(v));
    pushException("Not implemented function glRasterPos2sv(...)");
    return 0;
}


GL_FUNC(glRasterPos3d, args, ac) {
    GL_CHK_ARG(3, glRasterPos3d(x, y, z));
    GLdouble __gen_x = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_y = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_z = (GLdouble) doubleValue(args[3]);
    glRasterPos3d(__gen_x, __gen_y, __gen_z);
    return 0;
}


GL_FUNC(glRasterPos3dv, args, ac) {
    GL_CHK_ARG(1, glRasterPos3dv(v));
    pushException("Not implemented function glRasterPos3dv(...)");
    return 0;
}


GL_FUNC(glRasterPos3f, args, ac) {
    GL_CHK_ARG(3, glRasterPos3f(x, y, z));
    GLfloat __gen_x = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_y = (GLfloat) doubleValue(args[2]);
    GLfloat __gen_z = (GLfloat) doubleValue(args[3]);
    glRasterPos3f(__gen_x, __gen_y, __gen_z);
    return 0;
}


GL_FUNC(glRasterPos3fv, args, ac) {
    GL_CHK_ARG(1, glRasterPos3fv(v));
    pushException("Not implemented function glRasterPos3fv(...)");
    return 0;
}


GL_FUNC(glRasterPos3i, args, ac) {
    GL_CHK_ARG(3, glRasterPos3i(x, y, z));
    GLint __gen_x = (GLint) intValue(args[1]);
    GLint __gen_y = (GLint) intValue(args[2]);
    GLint __gen_z = (GLint) intValue(args[3]);
    glRasterPos3i(__gen_x, __gen_y, __gen_z);
    return 0;
}


GL_FUNC(glRasterPos3iv, args, ac) {
    GL_CHK_ARG(1, glRasterPos3iv(v));
    pushException("Not implemented function glRasterPos3iv(...)");
    return 0;
}


GL_FUNC(glRasterPos3s, args, ac) {
    GL_CHK_ARG(3, glRasterPos3s(x, y, z));
    GLshort __gen_x = (GLshort) intValue(args[1]);
    GLshort __gen_y = (GLshort) intValue(args[2]);
    GLshort __gen_z = (GLshort) intValue(args[3]);
    glRasterPos3s(__gen_x, __gen_y, __gen_z);
    return 0;
}


GL_FUNC(glRasterPos3sv, args, ac) {
    GL_CHK_ARG(1, glRasterPos3sv(v));
    pushException("Not implemented function glRasterPos3sv(...)");
    return 0;
}


GL_FUNC(glRasterPos4d, args, ac) {
    GL_CHK_ARG(4, glRasterPos4d(x, y, z, w));
    GLdouble __gen_x = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_y = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_z = (GLdouble) doubleValue(args[3]);
    GLdouble __gen_w = (GLdouble) doubleValue(args[4]);
    glRasterPos4d(__gen_x, __gen_y, __gen_z, __gen_w);
    return 0;
}


GL_FUNC(glRasterPos4dv, args, ac) {
    GL_CHK_ARG(1, glRasterPos4dv(v));
    pushException("Not implemented function glRasterPos4dv(...)");
    return 0;
}


GL_FUNC(glRasterPos4f, args, ac) {
    GL_CHK_ARG(4, glRasterPos4f(x, y, z, w));
    GLfloat __gen_x = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_y = (GLfloat) doubleValue(args[2]);
    GLfloat __gen_z = (GLfloat) doubleValue(args[3]);
    GLfloat __gen_w = (GLfloat) doubleValue(args[4]);
    glRasterPos4f(__gen_x, __gen_y, __gen_z, __gen_w);
    return 0;
}


GL_FUNC(glRasterPos4fv, args, ac) {
    GL_CHK_ARG(1, glRasterPos4fv(v));
    pushException("Not implemented function glRasterPos4fv(...)");
    return 0;
}


GL_FUNC(glRasterPos4i, args, ac) {
    GL_CHK_ARG(4, glRasterPos4i(x, y, z, w));
    GLint __gen_x = (GLint) intValue(args[1]);
    GLint __gen_y = (GLint) intValue(args[2]);
    GLint __gen_z = (GLint) intValue(args[3]);
    GLint __gen_w = (GLint) intValue(args[4]);
    glRasterPos4i(__gen_x, __gen_y, __gen_z, __gen_w);
    return 0;
}


GL_FUNC(glRasterPos4iv, args, ac) {
    GL_CHK_ARG(1, glRasterPos4iv(v));
    pushException("Not implemented function glRasterPos4iv(...)");
    return 0;
}


GL_FUNC(glRasterPos4s, args, ac) {
    GL_CHK_ARG(4, glRasterPos4s(x, y, z, w));
    GLshort __gen_x = (GLshort) intValue(args[1]);
    GLshort __gen_y = (GLshort) intValue(args[2]);
    GLshort __gen_z = (GLshort) intValue(args[3]);
    GLshort __gen_w = (GLshort) intValue(args[4]);
    glRasterPos4s(__gen_x, __gen_y, __gen_z, __gen_w);
    return 0;
}


GL_FUNC(glRasterPos4sv, args, ac) {
    GL_CHK_ARG(1, glRasterPos4sv(v));
    pushException("Not implemented function glRasterPos4sv(...)");
    return 0;
}


GL_FUNC(glReadBuffer, args, ac) {
    GL_CHK_ARG(1, glReadBuffer(mode));
    GLenum __gen_mode = (GLenum) intValue(args[1]);
    glReadBuffer(__gen_mode);
    return 0;
}


GL_FUNC(glReadPixels, args, ac) {
    GL_CHK_ARG(7, glReadPixels(x, y, width, height, format, type, pixels));
    pushException("Not implemented function glReadPixels(...)");
    return 0;
}


GL_FUNC(glRectd, args, ac) {
    GL_CHK_ARG(4, glRectd(x1, y1, x2, y2));
    GLdouble __gen_x1 = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_y1 = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_x2 = (GLdouble) doubleValue(args[3]);
    GLdouble __gen_y2 = (GLdouble) doubleValue(args[4]);
    glRectd(__gen_x1, __gen_y1, __gen_x2, __gen_y2);
    return 0;
}


GL_FUNC(glRectdv, args, ac) {
    GL_CHK_ARG(2, glRectdv(v1, v2));
    pushException("Not implemented function glRectdv(...)");
    return 0;
}


GL_FUNC(glRectf, args, ac) {
    GL_CHK_ARG(4, glRectf(x1, y1, x2, y2));
    GLfloat __gen_x1 = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_y1 = (GLfloat) doubleValue(args[2]);
    GLfloat __gen_x2 = (GLfloat) doubleValue(args[3]);
    GLfloat __gen_y2 = (GLfloat) doubleValue(args[4]);
    glRectf(__gen_x1, __gen_y1, __gen_x2, __gen_y2);
    return 0;
}


GL_FUNC(glRectfv, args, ac) {
    GL_CHK_ARG(2, glRectfv(v1, v2));
    pushException("Not implemented function glRectfv(...)");
    return 0;
}


GL_FUNC(glRecti, args, ac) {
    GL_CHK_ARG(4, glRecti(x1, y1, x2, y2));
    GLint __gen_x1 = (GLint) intValue(args[1]);
    GLint __gen_y1 = (GLint) intValue(args[2]);
    GLint __gen_x2 = (GLint) intValue(args[3]);
    GLint __gen_y2 = (GLint) intValue(args[4]);
    glRecti(__gen_x1, __gen_y1, __gen_x2, __gen_y2);
    return 0;
}


GL_FUNC(glRectiv, args, ac) {
    GL_CHK_ARG(2, glRectiv(v1, v2));
    pushException("Not implemented function glRectiv(...)");
    return 0;
}


GL_FUNC(glRects, args, ac) {
    GL_CHK_ARG(4, glRects(x1, y1, x2, y2));
    GLshort __gen_x1 = (GLshort) intValue(args[1]);
    GLshort __gen_y1 = (GLshort) intValue(args[2]);
    GLshort __gen_x2 = (GLshort) intValue(args[3]);
    GLshort __gen_y2 = (GLshort) intValue(args[4]);
    glRects(__gen_x1, __gen_y1, __gen_x2, __gen_y2);
    return 0;
}


GL_FUNC(glRectsv, args, ac) {
    GL_CHK_ARG(2, glRectsv(v1, v2));
    pushException("Not implemented function glRectsv(...)");
    return 0;
}


GL_FUNC(glRenderMode, args, ac) {
    GL_CHK_ARG(1, glRenderMode(mode));
    GLenum __gen_mode = (GLenum) intValue(args[1]);
    auto __return_glRenderMode = glRenderMode(__gen_mode);
    return wrapJs(__return_glRenderMode);
}


GL_FUNC(glRotated, args, ac) {
    GL_CHK_ARG(4, glRotated(angle, x, y, z));
    GLdouble __gen_angle = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_x = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_y = (GLdouble) doubleValue(args[3]);
    GLdouble __gen_z = (GLdouble) doubleValue(args[4]);
    glRotated(__gen_angle, __gen_x, __gen_y, __gen_z);
    return 0;
}


GL_FUNC(glRotatef, args, ac) {
    GL_CHK_ARG(4, glRotatef(angle, x, y, z));
    GLfloat __gen_angle = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_x = (GLfloat) doubleValue(args[2]);
    GLfloat __gen_y = (GLfloat) doubleValue(args[3]);
    GLfloat __gen_z = (GLfloat) doubleValue(args[4]);
    glRotatef(__gen_angle, __gen_x, __gen_y, __gen_z);
    return 0;
}


GL_FUNC(glScaled, args, ac) {
    GL_CHK_ARG(3, glScaled(x, y, z));
    GLdouble __gen_x = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_y = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_z = (GLdouble) doubleValue(args[3]);
    glScaled(__gen_x, __gen_y, __gen_z);
    return 0;
}


GL_FUNC(glScalef, args, ac) {
    GL_CHK_ARG(3, glScalef(x, y, z));
    GLfloat __gen_x = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_y = (GLfloat) doubleValue(args[2]);
    GLfloat __gen_z = (GLfloat) doubleValue(args[3]);
    glScalef(__gen_x, __gen_y, __gen_z);
    return 0;
}


GL_FUNC(glScissor, args, ac) {
    GL_CHK_ARG(4, glScissor(x, y, width, height));
    GLint __gen_x = (GLint) intValue(args[1]);
    GLint __gen_y = (GLint) intValue(args[2]);
    GLsizei __gen_width = (GLsizei) intValue(args[3]);
    GLsizei __gen_height = (GLsizei) intValue(args[4]);
    glScissor(__gen_x, __gen_y, __gen_width, __gen_height);
    return 0;
}


GL_FUNC(glSelectBuffer, args, ac) {
    GL_CHK_ARG(2, glSelectBuffer(size, buffer));
    pushException("Not implemented function glSelectBuffer(...)");
    return 0;
}


GL_FUNC(glShadeModel, args, ac) {
    GL_CHK_ARG(1, glShadeModel(mode));
    GLenum __gen_mode = (GLenum) intValue(args[1]);
    glShadeModel(__gen_mode);
    return 0;
}


GL_FUNC(glStencilFunc, args, ac) {
    GL_CHK_ARG(3, glStencilFunc(func, ref, mask));
    GLenum __gen_func = (GLenum) intValue(args[1]);
    GLint __gen_ref = (GLint) intValue(args[2]);
    GLuint __gen_mask = (GLuint) intValue(args[3]);
    glStencilFunc(__gen_func, __gen_ref, __gen_mask);
    return 0;
}


GL_FUNC(glStencilMask, args, ac) {
    GL_CHK_ARG(1, glStencilMask(mask));
    GLuint __gen_mask = (GLuint) intValue(args[1]);
    glStencilMask(__gen_mask);
    return 0;
}


GL_FUNC(glStencilOp, args, ac) {
    GL_CHK_ARG(3, glStencilOp(fail, zfail, zpass));
    GLenum __gen_fail = (GLenum) intValue(args[1]);
    GLenum __gen_zfail = (GLenum) intValue(args[2]);
    GLenum __gen_zpass = (GLenum) intValue(args[3]);
    glStencilOp(__gen_fail, __gen_zfail, __gen_zpass);
    return 0;
}


GL_FUNC(glTexCoord1d, args, ac) {
    GL_CHK_ARG(1, glTexCoord1d(s));
    GLdouble __gen_s = (GLdouble) doubleValue(args[1]);
    glTexCoord1d(__gen_s);
    return 0;
}


GL_FUNC(glTexCoord1dv, args, ac) {
    GL_CHK_ARG(1, glTexCoord1dv(v));
    pushException("Not implemented function glTexCoord1dv(...)");
    return 0;
}


GL_FUNC(glTexCoord1f, args, ac) {
    GL_CHK_ARG(1, glTexCoord1f(s));
    GLfloat __gen_s = (GLfloat) doubleValue(args[1]);
    glTexCoord1f(__gen_s);
    return 0;
}


GL_FUNC(glTexCoord1fv, args, ac) {
    GL_CHK_ARG(1, glTexCoord1fv(v));
    pushException("Not implemented function glTexCoord1fv(...)");
    return 0;
}


GL_FUNC(glTexCoord1i, args, ac) {
    GL_CHK_ARG(1, glTexCoord1i(s));
    GLint __gen_s = (GLint) intValue(args[1]);
    glTexCoord1i(__gen_s);
    return 0;
}


GL_FUNC(glTexCoord1iv, args, ac) {
    GL_CHK_ARG(1, glTexCoord1iv(v));
    pushException("Not implemented function glTexCoord1iv(...)");
    return 0;
}


GL_FUNC(glTexCoord1s, args, ac) {
    GL_CHK_ARG(1, glTexCoord1s(s));
    GLshort __gen_s = (GLshort) intValue(args[1]);
    glTexCoord1s(__gen_s);
    return 0;
}


GL_FUNC(glTexCoord1sv, args, ac) {
    GL_CHK_ARG(1, glTexCoord1sv(v));
    pushException("Not implemented function glTexCoord1sv(...)");
    return 0;
}


GL_FUNC(glTexCoord2d, args, ac) {
    GL_CHK_ARG(2, glTexCoord2d(s, t));
    GLdouble __gen_s = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_t = (GLdouble) doubleValue(args[2]);
    glTexCoord2d(__gen_s, __gen_t);
    return 0;
}


GL_FUNC(glTexCoord2dv, args, ac) {
    GL_CHK_ARG(1, glTexCoord2dv(v));
    pushException("Not implemented function glTexCoord2dv(...)");
    return 0;
}


GL_FUNC(glTexCoord2f, args, ac) {
    GL_CHK_ARG(2, glTexCoord2f(s, t));
    GLfloat __gen_s = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_t = (GLfloat) doubleValue(args[2]);
    glTexCoord2f(__gen_s, __gen_t);
    return 0;
}


GL_FUNC(glTexCoord2fv, args, ac) {
    GL_CHK_ARG(1, glTexCoord2fv(v));
    pushException("Not implemented function glTexCoord2fv(...)");
    return 0;
}


GL_FUNC(glTexCoord2i, args, ac) {
    GL_CHK_ARG(2, glTexCoord2i(s, t));
    GLint __gen_s = (GLint) intValue(args[1]);
    GLint __gen_t = (GLint) intValue(args[2]);
    glTexCoord2i(__gen_s, __gen_t);
    return 0;
}


GL_FUNC(glTexCoord2iv, args, ac) {
    GL_CHK_ARG(1, glTexCoord2iv(v));
    pushException("Not implemented function glTexCoord2iv(...)");
    return 0;
}


GL_FUNC(glTexCoord2s, args, ac) {
    GL_CHK_ARG(2, glTexCoord2s(s, t));
    GLshort __gen_s = (GLshort) intValue(args[1]);
    GLshort __gen_t = (GLshort) intValue(args[2]);
    glTexCoord2s(__gen_s, __gen_t);
    return 0;
}


GL_FUNC(glTexCoord2sv, args, ac) {
    GL_CHK_ARG(1, glTexCoord2sv(v));
    pushException("Not implemented function glTexCoord2sv(...)");
    return 0;
}


GL_FUNC(glTexCoord3d, args, ac) {
    GL_CHK_ARG(3, glTexCoord3d(s, t, r));
    GLdouble __gen_s = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_t = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_r = (GLdouble) doubleValue(args[3]);
    glTexCoord3d(__gen_s, __gen_t, __gen_r);
    return 0;
}


GL_FUNC(glTexCoord3dv, args, ac) {
    GL_CHK_ARG(1, glTexCoord3dv(v));
    pushException("Not implemented function glTexCoord3dv(...)");
    return 0;
}


GL_FUNC(glTexCoord3f, args, ac) {
    GL_CHK_ARG(3, glTexCoord3f(s, t, r));
    GLfloat __gen_s = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_t = (GLfloat) doubleValue(args[2]);
    GLfloat __gen_r = (GLfloat) doubleValue(args[3]);
    glTexCoord3f(__gen_s, __gen_t, __gen_r);
    return 0;
}


GL_FUNC(glTexCoord3fv, args, ac) {
    GL_CHK_ARG(1, glTexCoord3fv(v));
    pushException("Not implemented function glTexCoord3fv(...)");
    return 0;
}


GL_FUNC(glTexCoord3i, args, ac) {
    GL_CHK_ARG(3, glTexCoord3i(s, t, r));
    GLint __gen_s = (GLint) intValue(args[1]);
    GLint __gen_t = (GLint) intValue(args[2]);
    GLint __gen_r = (GLint) intValue(args[3]);
    glTexCoord3i(__gen_s, __gen_t, __gen_r);
    return 0;
}


GL_FUNC(glTexCoord3iv, args, ac) {
    GL_CHK_ARG(1, glTexCoord3iv(v));
    pushException("Not implemented function glTexCoord3iv(...)");
    return 0;
}


GL_FUNC(glTexCoord3s, args, ac) {
    GL_CHK_ARG(3, glTexCoord3s(s, t, r));
    GLshort __gen_s = (GLshort) intValue(args[1]);
    GLshort __gen_t = (GLshort) intValue(args[2]);
    GLshort __gen_r = (GLshort) intValue(args[3]);
    glTexCoord3s(__gen_s, __gen_t, __gen_r);
    return 0;
}


GL_FUNC(glTexCoord3sv, args, ac) {
    GL_CHK_ARG(1, glTexCoord3sv(v));
    pushException("Not implemented function glTexCoord3sv(...)");
    return 0;
}


GL_FUNC(glTexCoord4d, args, ac) {
    GL_CHK_ARG(4, glTexCoord4d(s, t, r, q));
    GLdouble __gen_s = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_t = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_r = (GLdouble) doubleValue(args[3]);
    GLdouble __gen_q = (GLdouble) doubleValue(args[4]);
    glTexCoord4d(__gen_s, __gen_t, __gen_r, __gen_q);
    return 0;
}


GL_FUNC(glTexCoord4dv, args, ac) {
    GL_CHK_ARG(1, glTexCoord4dv(v));
    pushException("Not implemented function glTexCoord4dv(...)");
    return 0;
}


GL_FUNC(glTexCoord4f, args, ac) {
    GL_CHK_ARG(4, glTexCoord4f(s, t, r, q));
    GLfloat __gen_s = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_t = (GLfloat) doubleValue(args[2]);
    GLfloat __gen_r = (GLfloat) doubleValue(args[3]);
    GLfloat __gen_q = (GLfloat) doubleValue(args[4]);
    glTexCoord4f(__gen_s, __gen_t, __gen_r, __gen_q);
    return 0;
}


GL_FUNC(glTexCoord4fv, args, ac) {
    GL_CHK_ARG(1, glTexCoord4fv(v));
    pushException("Not implemented function glTexCoord4fv(...)");
    return 0;
}


GL_FUNC(glTexCoord4i, args, ac) {
    GL_CHK_ARG(4, glTexCoord4i(s, t, r, q));
    GLint __gen_s = (GLint) intValue(args[1]);
    GLint __gen_t = (GLint) intValue(args[2]);
    GLint __gen_r = (GLint) intValue(args[3]);
    GLint __gen_q = (GLint) intValue(args[4]);
    glTexCoord4i(__gen_s, __gen_t, __gen_r, __gen_q);
    return 0;
}


GL_FUNC(glTexCoord4iv, args, ac) {
    GL_CHK_ARG(1, glTexCoord4iv(v));
    pushException("Not implemented function glTexCoord4iv(...)");
    return 0;
}


GL_FUNC(glTexCoord4s, args, ac) {
    GL_CHK_ARG(4, glTexCoord4s(s, t, r, q));
    GLshort __gen_s = (GLshort) intValue(args[1]);
    GLshort __gen_t = (GLshort) intValue(args[2]);
    GLshort __gen_r = (GLshort) intValue(args[3]);
    GLshort __gen_q = (GLshort) intValue(args[4]);
    glTexCoord4s(__gen_s, __gen_t, __gen_r, __gen_q);
    return 0;
}


GL_FUNC(glTexCoord4sv, args, ac) {
    GL_CHK_ARG(1, glTexCoord4sv(v));
    pushException("Not implemented function glTexCoord4sv(...)");
    return 0;
}


GL_FUNC(glTexCoordPointer, args, ac) {
    GL_CHK_ARG(4, glTexCoordPointer(size, type, stride, pointer));
    pushException("Not implemented function glTexCoordPointer(...)");
    return 0;
}


GL_FUNC(glTexEnvf, args, ac) {
    GL_CHK_ARG(3, glTexEnvf(target, pname, param));
    GLenum __gen_target = (GLenum) intValue(args[1]);
    GLenum __gen_pname = (GLenum) intValue(args[2]);
    GLfloat __gen_param = (GLfloat) doubleValue(args[3]);
    glTexEnvf(__gen_target, __gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glTexEnvfv, args, ac) {
    GL_CHK_ARG(3, glTexEnvfv(target, pname, params));
    pushException("Not implemented function glTexEnvfv(...)");
    return 0;
}


GL_FUNC(glTexEnvi, args, ac) {
    GL_CHK_ARG(3, glTexEnvi(target, pname, param));
    GLenum __gen_target = (GLenum) intValue(args[1]);
    GLenum __gen_pname = (GLenum) intValue(args[2]);
    GLint __gen_param = (GLint) intValue(args[3]);
    glTexEnvi(__gen_target, __gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glTexEnviv, args, ac) {
    GL_CHK_ARG(3, glTexEnviv(target, pname, params));
    pushException("Not implemented function glTexEnviv(...)");
    return 0;
}


GL_FUNC(glTexGend, args, ac) {
    GL_CHK_ARG(3, glTexGend(coord, pname, param));
    GLenum __gen_coord = (GLenum) intValue(args[1]);
    GLenum __gen_pname = (GLenum) intValue(args[2]);
    GLdouble __gen_param = (GLdouble) doubleValue(args[3]);
    glTexGend(__gen_coord, __gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glTexGendv, args, ac) {
    GL_CHK_ARG(3, glTexGendv(coord, pname, params));
    pushException("Not implemented function glTexGendv(...)");
    return 0;
}


GL_FUNC(glTexGenf, args, ac) {
    GL_CHK_ARG(3, glTexGenf(coord, pname, param));
    GLenum __gen_coord = (GLenum) intValue(args[1]);
    GLenum __gen_pname = (GLenum) intValue(args[2]);
    GLfloat __gen_param = (GLfloat) doubleValue(args[3]);
    glTexGenf(__gen_coord, __gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glTexGenfv, args, ac) {
    GL_CHK_ARG(3, glTexGenfv(coord, pname, params));
    pushException("Not implemented function glTexGenfv(...)");
    return 0;
}


GL_FUNC(glTexGeni, args, ac) {
    GL_CHK_ARG(3, glTexGeni(coord, pname, param));
    GLenum __gen_coord = (GLenum) intValue(args[1]);
    GLenum __gen_pname = (GLenum) intValue(args[2]);
    GLint __gen_param = (GLint) intValue(args[3]);
    glTexGeni(__gen_coord, __gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glTexGeniv, args, ac) {
    GL_CHK_ARG(3, glTexGeniv(coord, pname, params));
    pushException("Not implemented function glTexGeniv(...)");
    return 0;
}


GL_FUNC(glTexImage1D, args, ac) {
    GL_CHK_ARG(8, glTexImage1D(target, level, internalformat, width, border, format, type, pixels));
    pushException("Not implemented function glTexImage1D(...)");
    return 0;
}


GL_FUNC(glTexImage2D, args, ac) {
    GL_CHK_ARG(9, glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels));
    pushException("Not implemented function glTexImage2D(...)");
    return 0;
}


GL_FUNC(glTexParameterf, args, ac) {
    GL_CHK_ARG(3, glTexParameterf(target, pname, param));
    GLenum __gen_target = (GLenum) intValue(args[1]);
    GLenum __gen_pname = (GLenum) intValue(args[2]);
    GLfloat __gen_param = (GLfloat) doubleValue(args[3]);
    glTexParameterf(__gen_target, __gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glTexParameterfv, args, ac) {
    GL_CHK_ARG(3, glTexParameterfv(target, pname, params));
    pushException("Not implemented function glTexParameterfv(...)");
    return 0;
}


GL_FUNC(glTexParameteri, args, ac) {
    GL_CHK_ARG(3, glTexParameteri(target, pname, param));
    GLenum __gen_target = (GLenum) intValue(args[1]);
    GLenum __gen_pname = (GLenum) intValue(args[2]);
    GLint __gen_param = (GLint) intValue(args[3]);
    glTexParameteri(__gen_target, __gen_pname, __gen_param);
    return 0;
}


GL_FUNC(glTexParameteriv, args, ac) {
    GL_CHK_ARG(3, glTexParameteriv(target, pname, params));
    pushException("Not implemented function glTexParameteriv(...)");
    return 0;
}


GL_FUNC(glTexSubImage1D, args, ac) {
    GL_CHK_ARG(7, glTexSubImage1D(target, level, xoffset, width, format, type, pixels));
    pushException("Not implemented function glTexSubImage1D(...)");
    return 0;
}


GL_FUNC(glTexSubImage2D, args, ac) {
    GL_CHK_ARG(9, glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels));
    pushException("Not implemented function glTexSubImage2D(...)");
    return 0;
}


GL_FUNC(glTranslated, args, ac) {
    GL_CHK_ARG(3, glTranslated(x, y, z));
    GLdouble __gen_x = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_y = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_z = (GLdouble) doubleValue(args[3]);
    glTranslated(__gen_x, __gen_y, __gen_z);
    return 0;
}


GL_FUNC(glTranslatef, args, ac) {
    GL_CHK_ARG(3, glTranslatef(x, y, z));
    GLfloat __gen_x = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_y = (GLfloat) doubleValue(args[2]);
    GLfloat __gen_z = (GLfloat) doubleValue(args[3]);
    glTranslatef(__gen_x, __gen_y, __gen_z);
    return 0;
}


GL_FUNC(glVertex2d, args, ac) {
    GL_CHK_ARG(2, glVertex2d(x, y));
    GLdouble __gen_x = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_y = (GLdouble) doubleValue(args[2]);
    glVertex2d(__gen_x, __gen_y);
    return 0;
}


GL_FUNC(glVertex2dv, args, ac) {
    GL_CHK_ARG(1, glVertex2dv(v));
    pushException("Not implemented function glVertex2dv(...)");
    return 0;
}


GL_FUNC(glVertex2f, args, ac) {
    GL_CHK_ARG(2, glVertex2f(x, y));
    GLfloat __gen_x = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_y = (GLfloat) doubleValue(args[2]);
    glVertex2f(__gen_x, __gen_y);
    return 0;
}


GL_FUNC(glVertex2fv, args, ac) {
    GL_CHK_ARG(1, glVertex2fv(v));
    pushException("Not implemented function glVertex2fv(...)");
    return 0;
}


GL_FUNC(glVertex2i, args, ac) {
    GL_CHK_ARG(2, glVertex2i(x, y));
    GLint __gen_x = (GLint) intValue(args[1]);
    GLint __gen_y = (GLint) intValue(args[2]);
    glVertex2i(__gen_x, __gen_y);
    return 0;
}


GL_FUNC(glVertex2iv, args, ac) {
    GL_CHK_ARG(1, glVertex2iv(v));
    pushException("Not implemented function glVertex2iv(...)");
    return 0;
}


GL_FUNC(glVertex2s, args, ac) {
    GL_CHK_ARG(2, glVertex2s(x, y));
    GLshort __gen_x = (GLshort) intValue(args[1]);
    GLshort __gen_y = (GLshort) intValue(args[2]);
    glVertex2s(__gen_x, __gen_y);
    return 0;
}


GL_FUNC(glVertex2sv, args, ac) {
    GL_CHK_ARG(1, glVertex2sv(v));
    pushException("Not implemented function glVertex2sv(...)");
    return 0;
}


GL_FUNC(glVertex3d, args, ac) {
    GL_CHK_ARG(3, glVertex3d(x, y, z));
    GLdouble __gen_x = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_y = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_z = (GLdouble) doubleValue(args[3]);
    glVertex3d(__gen_x, __gen_y, __gen_z);
    return 0;
}


GL_FUNC(glVertex3dv, args, ac) {
    GL_CHK_ARG(1, glVertex3dv(v));
    pushException("Not implemented function glVertex3dv(...)");
    return 0;
}


GL_FUNC(glVertex3f, args, ac) {
    GL_CHK_ARG(3, glVertex3f(x, y, z));
    GLfloat __gen_x = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_y = (GLfloat) doubleValue(args[2]);
    GLfloat __gen_z = (GLfloat) doubleValue(args[3]);
    glVertex3f(__gen_x, __gen_y, __gen_z);
    return 0;
}


GL_FUNC(glVertex3fv, args, ac) {
    GL_CHK_ARG(1, glVertex3fv(v));
    pushException("Not implemented function glVertex3fv(...)");
    return 0;
}


GL_FUNC(glVertex3i, args, ac) {
    GL_CHK_ARG(3, glVertex3i(x, y, z));
    GLint __gen_x = (GLint) intValue(args[1]);
    GLint __gen_y = (GLint) intValue(args[2]);
    GLint __gen_z = (GLint) intValue(args[3]);
    glVertex3i(__gen_x, __gen_y, __gen_z);
    return 0;
}


GL_FUNC(glVertex3iv, args, ac) {
    GL_CHK_ARG(1, glVertex3iv(v));
    pushException("Not implemented function glVertex3iv(...)");
    return 0;
}


GL_FUNC(glVertex3s, args, ac) {
    GL_CHK_ARG(3, glVertex3s(x, y, z));
    GLshort __gen_x = (GLshort) intValue(args[1]);
    GLshort __gen_y = (GLshort) intValue(args[2]);
    GLshort __gen_z = (GLshort) intValue(args[3]);
    glVertex3s(__gen_x, __gen_y, __gen_z);
    return 0;
}


GL_FUNC(glVertex3sv, args, ac) {
    GL_CHK_ARG(1, glVertex3sv(v));
    pushException("Not implemented function glVertex3sv(...)");
    return 0;
}


GL_FUNC(glVertex4d, args, ac) {
    GL_CHK_ARG(4, glVertex4d(x, y, z, w));
    GLdouble __gen_x = (GLdouble) doubleValue(args[1]);
    GLdouble __gen_y = (GLdouble) doubleValue(args[2]);
    GLdouble __gen_z = (GLdouble) doubleValue(args[3]);
    GLdouble __gen_w = (GLdouble) doubleValue(args[4]);
    glVertex4d(__gen_x, __gen_y, __gen_z, __gen_w);
    return 0;
}


GL_FUNC(glVertex4dv, args, ac) {
    GL_CHK_ARG(1, glVertex4dv(v));
    pushException("Not implemented function glVertex4dv(...)");
    return 0;
}


GL_FUNC(glVertex4f, args, ac) {
    GL_CHK_ARG(4, glVertex4f(x, y, z, w));
    GLfloat __gen_x = (GLfloat) doubleValue(args[1]);
    GLfloat __gen_y = (GLfloat) doubleValue(args[2]);
    GLfloat __gen_z = (GLfloat) doubleValue(args[3]);
    GLfloat __gen_w = (GLfloat) doubleValue(args[4]);
    glVertex4f(__gen_x, __gen_y, __gen_z, __gen_w);
    return 0;
}


GL_FUNC(glVertex4fv, args, ac) {
    GL_CHK_ARG(1, glVertex4fv(v));
    pushException("Not implemented function glVertex4fv(...)");
    return 0;
}


GL_FUNC(glVertex4i, args, ac) {
    GL_CHK_ARG(4, glVertex4i(x, y, z, w));
    GLint __gen_x = (GLint) intValue(args[1]);
    GLint __gen_y = (GLint) intValue(args[2]);
    GLint __gen_z = (GLint) intValue(args[3]);
    GLint __gen_w = (GLint) intValue(args[4]);
    glVertex4i(__gen_x, __gen_y, __gen_z, __gen_w);
    return 0;
}


GL_FUNC(glVertex4iv, args, ac) {
    GL_CHK_ARG(1, glVertex4iv(v));
    pushException("Not implemented function glVertex4iv(...)");
    return 0;
}


GL_FUNC(glVertex4s, args, ac) {
    GL_CHK_ARG(4, glVertex4s(x, y, z, w));
    GLshort __gen_x = (GLshort) intValue(args[1]);
    GLshort __gen_y = (GLshort) intValue(args[2]);
    GLshort __gen_z = (GLshort) intValue(args[3]);
    GLshort __gen_w = (GLshort) intValue(args[4]);
    glVertex4s(__gen_x, __gen_y, __gen_z, __gen_w);
    return 0;
}


GL_FUNC(glVertex4sv, args, ac) {
    GL_CHK_ARG(1, glVertex4sv(v));
    pushException("Not implemented function glVertex4sv(...)");
    return 0;
}


GL_FUNC(glVertexPointer, args, ac) {
    GL_CHK_ARG(4, glVertexPointer(size, type, stride, pointer));
    pushException("Not implemented function glVertexPointer(...)");
    return 0;
}


// GL_FUNC(glViewport, args, ac) {
    // GL_CHK_ARG(4, glViewport(x, y, width, height));
    // GLint __gen_x = (GLint) intValue(args[1]);
    // GLint __gen_y = (GLint) intValue(args[2]);
    // GLsizei __gen_width = (GLsizei) intValue(args[3]);
    // GLsizei __gen_height = (GLsizei) intValue(args[4]);
    // glViewport(__gen_x, __gen_y, __gen_width, __gen_height);
    // return 0;
// }


void auto_bind_glew_h(VM*vm, LocalVal& gl) {
    GL_BIND(glAccum);
    GL_BIND(glAlphaFunc);
    GL_BIND(glAreTexturesResident);
    GL_BIND(glArrayElement);
    GL_BIND(glBegin);
    GL_BIND(glBindTexture);
    GL_BIND(glBitmap);
    GL_BIND(glBlendFunc);
    GL_BIND(glCallList);
    GL_BIND(glCallLists);
    GL_BIND(glClear);
    GL_BIND(glClearAccum);
    GL_BIND(glClearColor);
    GL_BIND(glClearDepth);
    GL_BIND(glClearIndex);
    GL_BIND(glClearStencil);
    GL_BIND(glClipPlane);
    GL_BIND(glColor3b);
    GL_BIND(glColor3bv);
    GL_BIND(glColor3d);
    GL_BIND(glColor3dv);
    GL_BIND(glColor3f);
    GL_BIND(glColor3fv);
    GL_BIND(glColor3i);
    GL_BIND(glColor3iv);
    GL_BIND(glColor3s);
    GL_BIND(glColor3sv);
    GL_BIND(glColor3ub);
    GL_BIND(glColor3ubv);
    GL_BIND(glColor3ui);
    GL_BIND(glColor3uiv);
    GL_BIND(glColor3us);
    GL_BIND(glColor3usv);
    GL_BIND(glColor4b);
    GL_BIND(glColor4bv);
    GL_BIND(glColor4d);
    GL_BIND(glColor4dv);
    GL_BIND(glColor4f);
    GL_BIND(glColor4fv);
    GL_BIND(glColor4i);
    GL_BIND(glColor4iv);
    GL_BIND(glColor4s);
    GL_BIND(glColor4sv);
    GL_BIND(glColor4ub);
    GL_BIND(glColor4ubv);
    GL_BIND(glColor4ui);
    GL_BIND(glColor4uiv);
    GL_BIND(glColor4us);
    GL_BIND(glColor4usv);
    GL_BIND(glColorMask);
    GL_BIND(glColorMaterial);
    GL_BIND(glColorPointer);
    GL_BIND(glCopyPixels);
    GL_BIND(glCopyTexImage1D);
    GL_BIND(glCopyTexImage2D);
    GL_BIND(glCopyTexSubImage1D);
    GL_BIND(glCopyTexSubImage2D);
    GL_BIND(glCullFace);
    GL_BIND(glDeleteLists);
    GL_BIND(glDeleteTextures);
    GL_BIND(glDepthFunc);
    GL_BIND(glDepthMask);
    GL_BIND(glDepthRange);
    GL_BIND(glDisable);
    GL_BIND(glDisableClientState);
    GL_BIND(glDrawArrays);
    GL_BIND(glDrawBuffer);
    GL_BIND(glDrawElements);
    GL_BIND(glDrawPixels);
    GL_BIND(glEdgeFlag);
    GL_BIND(glEdgeFlagPointer);
    GL_BIND(glEdgeFlagv);
    GL_BIND(glEnable);
    GL_BIND(glEnableClientState);
    GL_BIND(glEnd);
    GL_BIND(glEndList);
    GL_BIND(glEvalCoord1d);
    GL_BIND(glEvalCoord1dv);
    GL_BIND(glEvalCoord1f);
    GL_BIND(glEvalCoord1fv);
    GL_BIND(glEvalCoord2d);
    GL_BIND(glEvalCoord2dv);
    GL_BIND(glEvalCoord2f);
    GL_BIND(glEvalCoord2fv);
    GL_BIND(glEvalMesh1);
    GL_BIND(glEvalMesh2);
    GL_BIND(glEvalPoint1);
    GL_BIND(glEvalPoint2);
    GL_BIND(glFeedbackBuffer);
    GL_BIND(glFinish);
    GL_BIND(glFlush);
    GL_BIND(glFogf);
    GL_BIND(glFogfv);
    GL_BIND(glFogi);
    GL_BIND(glFogiv);
    GL_BIND(glFrontFace);
    GL_BIND(glFrustum);
    GL_BIND(glGenLists);
    GL_BIND(glGenTextures);
    GL_BIND(glGetBooleanv);
    GL_BIND(glGetClipPlane);
    GL_BIND(glGetDoublev);
    GL_BIND(glGetError);
    GL_BIND(glGetFloatv);
    GL_BIND(glGetIntegerv);
    GL_BIND(glGetLightfv);
    GL_BIND(glGetLightiv);
    GL_BIND(glGetMapdv);
    GL_BIND(glGetMapfv);
    GL_BIND(glGetMapiv);
    GL_BIND(glGetMaterialfv);
    GL_BIND(glGetMaterialiv);
    GL_BIND(glGetPixelMapfv);
    GL_BIND(glGetPixelMapuiv);
    GL_BIND(glGetPixelMapusv);
    GL_BIND(glGetPointerv);
    GL_BIND(glGetPolygonStipple);
    GL_BIND(glGetString);
    GL_BIND(glGetTexEnvfv);
    GL_BIND(glGetTexEnviv);
    GL_BIND(glGetTexGendv);
    GL_BIND(glGetTexGenfv);
    GL_BIND(glGetTexGeniv);
    GL_BIND(glGetTexImage);
    GL_BIND(glGetTexLevelParameterfv);
    GL_BIND(glGetTexLevelParameteriv);
    GL_BIND(glGetTexParameterfv);
    GL_BIND(glGetTexParameteriv);
    GL_BIND(glHint);
    GL_BIND(glIndexMask);
    GL_BIND(glIndexPointer);
    GL_BIND(glIndexd);
    GL_BIND(glIndexdv);
    GL_BIND(glIndexf);
    GL_BIND(glIndexfv);
    GL_BIND(glIndexi);
    GL_BIND(glIndexiv);
    GL_BIND(glIndexs);
    GL_BIND(glIndexsv);
    GL_BIND(glIndexub);
    GL_BIND(glIndexubv);
    GL_BIND(glInitNames);
    GL_BIND(glInterleavedArrays);
    GL_BIND(glIsEnabled);
    GL_BIND(glIsList);
    GL_BIND(glIsTexture);
    GL_BIND(glLightModelf);
    GL_BIND(glLightModelfv);
    GL_BIND(glLightModeli);
    GL_BIND(glLightModeliv);
    GL_BIND(glLightf);
    GL_BIND(glLightfv);
    GL_BIND(glLighti);
    GL_BIND(glLightiv);
    GL_BIND(glLineStipple);
    GL_BIND(glLineWidth);
    GL_BIND(glListBase);
    GL_BIND(glLoadIdentity);
    GL_BIND(glLoadMatrixd);
    GL_BIND(glLoadMatrixf);
    GL_BIND(glLoadName);
    GL_BIND(glLogicOp);
    GL_BIND(glMap1d);
    GL_BIND(glMap1f);
    GL_BIND(glMap2d);
    GL_BIND(glMap2f);
    GL_BIND(glMapGrid1d);
    GL_BIND(glMapGrid1f);
    GL_BIND(glMapGrid2d);
    GL_BIND(glMapGrid2f);
    GL_BIND(glMaterialf);
    GL_BIND(glMaterialfv);
    GL_BIND(glMateriali);
    GL_BIND(glMaterialiv);
    GL_BIND(glMatrixMode);
    GL_BIND(glMultMatrixd);
    GL_BIND(glMultMatrixf);
    GL_BIND(glNewList);
    GL_BIND(glNormal3b);
    GL_BIND(glNormal3bv);
    GL_BIND(glNormal3d);
    GL_BIND(glNormal3dv);
    GL_BIND(glNormal3f);
    GL_BIND(glNormal3fv);
    GL_BIND(glNormal3i);
    GL_BIND(glNormal3iv);
    GL_BIND(glNormal3s);
    GL_BIND(glNormal3sv);
    GL_BIND(glNormalPointer);
    GL_BIND(glOrtho);
    GL_BIND(glPassThrough);
    GL_BIND(glPixelMapfv);
    GL_BIND(glPixelMapuiv);
    GL_BIND(glPixelMapusv);
    GL_BIND(glPixelStoref);
    GL_BIND(glPixelStorei);
    GL_BIND(glPixelTransferf);
    GL_BIND(glPixelTransferi);
    GL_BIND(glPixelZoom);
    GL_BIND(glPointSize);
    GL_BIND(glPolygonMode);
    GL_BIND(glPolygonOffset);
    GL_BIND(glPolygonStipple);
    GL_BIND(glPopAttrib);
    GL_BIND(glPopClientAttrib);
    GL_BIND(glPopMatrix);
    GL_BIND(glPopName);
    GL_BIND(glPrioritizeTextures);
    GL_BIND(glPushAttrib);
    GL_BIND(glPushClientAttrib);
    GL_BIND(glPushMatrix);
    GL_BIND(glPushName);
    GL_BIND(glRasterPos2d);
    GL_BIND(glRasterPos2dv);
    GL_BIND(glRasterPos2f);
    GL_BIND(glRasterPos2fv);
    GL_BIND(glRasterPos2i);
    GL_BIND(glRasterPos2iv);
    GL_BIND(glRasterPos2s);
    GL_BIND(glRasterPos2sv);
    GL_BIND(glRasterPos3d);
    GL_BIND(glRasterPos3dv);
    GL_BIND(glRasterPos3f);
    GL_BIND(glRasterPos3fv);
    GL_BIND(glRasterPos3i);
    GL_BIND(glRasterPos3iv);
    GL_BIND(glRasterPos3s);
    GL_BIND(glRasterPos3sv);
    GL_BIND(glRasterPos4d);
    GL_BIND(glRasterPos4dv);
    GL_BIND(glRasterPos4f);
    GL_BIND(glRasterPos4fv);
    GL_BIND(glRasterPos4i);
    GL_BIND(glRasterPos4iv);
    GL_BIND(glRasterPos4s);
    GL_BIND(glRasterPos4sv);
    GL_BIND(glReadBuffer);
    GL_BIND(glReadPixels);
    GL_BIND(glRectd);
    GL_BIND(glRectdv);
    GL_BIND(glRectf);
    GL_BIND(glRectfv);
    GL_BIND(glRecti);
    GL_BIND(glRectiv);
    GL_BIND(glRects);
    GL_BIND(glRectsv);
    GL_BIND(glRenderMode);
    GL_BIND(glRotated);
    GL_BIND(glRotatef);
    GL_BIND(glScaled);
    GL_BIND(glScalef);
    GL_BIND(glScissor);
    GL_BIND(glSelectBuffer);
    GL_BIND(glShadeModel);
    GL_BIND(glStencilFunc);
    GL_BIND(glStencilMask);
    GL_BIND(glStencilOp);
    GL_BIND(glTexCoord1d);
    GL_BIND(glTexCoord1dv);
    GL_BIND(glTexCoord1f);
    GL_BIND(glTexCoord1fv);
    GL_BIND(glTexCoord1i);
    GL_BIND(glTexCoord1iv);
    GL_BIND(glTexCoord1s);
    GL_BIND(glTexCoord1sv);
    GL_BIND(glTexCoord2d);
    GL_BIND(glTexCoord2dv);
    GL_BIND(glTexCoord2f);
    GL_BIND(glTexCoord2fv);
    GL_BIND(glTexCoord2i);
    GL_BIND(glTexCoord2iv);
    GL_BIND(glTexCoord2s);
    GL_BIND(glTexCoord2sv);
    GL_BIND(glTexCoord3d);
    GL_BIND(glTexCoord3dv);
    GL_BIND(glTexCoord3f);
    GL_BIND(glTexCoord3fv);
    GL_BIND(glTexCoord3i);
    GL_BIND(glTexCoord3iv);
    GL_BIND(glTexCoord3s);
    GL_BIND(glTexCoord3sv);
    GL_BIND(glTexCoord4d);
    GL_BIND(glTexCoord4dv);
    GL_BIND(glTexCoord4f);
    GL_BIND(glTexCoord4fv);
    GL_BIND(glTexCoord4i);
    GL_BIND(glTexCoord4iv);
    GL_BIND(glTexCoord4s);
    GL_BIND(glTexCoord4sv);
    GL_BIND(glTexCoordPointer);
    GL_BIND(glTexEnvf);
    GL_BIND(glTexEnvfv);
    GL_BIND(glTexEnvi);
    GL_BIND(glTexEnviv);
    GL_BIND(glTexGend);
    GL_BIND(glTexGendv);
    GL_BIND(glTexGenf);
    GL_BIND(glTexGenfv);
    GL_BIND(glTexGeni);
    GL_BIND(glTexGeniv);
    GL_BIND(glTexImage1D);
    GL_BIND(glTexImage2D);
    GL_BIND(glTexParameterf);
    GL_BIND(glTexParameterfv);
    GL_BIND(glTexParameteri);
    GL_BIND(glTexParameteriv);
    GL_BIND(glTexSubImage1D);
    GL_BIND(glTexSubImage2D);
    GL_BIND(glTranslated);
    GL_BIND(glTranslatef);
    GL_BIND(glVertex2d);
    GL_BIND(glVertex2dv);
    GL_BIND(glVertex2f);
    GL_BIND(glVertex2fv);
    GL_BIND(glVertex2i);
    GL_BIND(glVertex2iv);
    GL_BIND(glVertex2s);
    GL_BIND(glVertex2sv);
    GL_BIND(glVertex3d);
    GL_BIND(glVertex3dv);
    GL_BIND(glVertex3f);
    GL_BIND(glVertex3fv);
    GL_BIND(glVertex3i);
    GL_BIND(glVertex3iv);
    GL_BIND(glVertex3s);
    GL_BIND(glVertex3sv);
    GL_BIND(glVertex4d);
    GL_BIND(glVertex4dv);
    GL_BIND(glVertex4f);
    GL_BIND(glVertex4fv);
    GL_BIND(glVertex4i);
    GL_BIND(glVertex4iv);
    GL_BIND(glVertex4s);
    GL_BIND(glVertex4sv);
    GL_BIND(glVertexPointer);
    // GL_BIND(glViewport);
}
