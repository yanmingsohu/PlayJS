// 
// 2019-02-07 16:38:15
// create from D:\game\sanguo7\src-auto\generate-code.js
// 
// Auto Generate Hander
//
#include "../src/gl.h"
#include "../src/gldeleter.h"

#define INCLUDE_AUTO_GL_CODE(vm, gl, _const) \
    auto_gl_Const(vm, _const); \
    auto_bind_glfw3_h(vm, gl); \
    auto_bind_glew_h(vm, gl)

void auto_gl_Const(VM* vm, LocalVal& _const);
void auto_bind_glfw3_h(VM*vm, LocalVal& gl);
void auto_bind_glew_h(VM*vm, LocalVal& gl);
