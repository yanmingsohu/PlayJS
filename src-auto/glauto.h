//
// 2019-02-06 21:29:41
// create from D:\game\sanguo7\src-auto\generate-gl-code.js 
//
// Auto Generate Hander
#include "../src/gl.h"


#define INCLUDE_AUTO_GL_CODE(vm, gl, _const) \
    auto_gl_Const(vm, _const); \
    auto_bind_glfw3_h(vm, gl); \
    auto_bind_GL_h(vm, gl); \


void auto_gl_Const(VM* vm, LocalVal& _const);
void auto_bind_glfw3_h(VM*vm, LocalVal& gl);
void auto_bind_GL_h(VM*vm, LocalVal& gl);

