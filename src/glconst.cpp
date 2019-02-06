#include "gl.h"

#define INT_ENUM(name) _const.put(#name, wrapJs(name));


void installGLFWConst(VM* vm, LocalVal& _const) {
    INT_ENUM(GLFW_TRUE);
    INT_ENUM(GLFW_FALSE);
    INT_ENUM(GLFW_DONT_CARE);
    INT_ENUM(GLFW_OPENGL_API);

    INT_ENUM(GLFW_COCOA_RETINA_FRAMEBUFFER);
    INT_ENUM(GLFW_COCOA_FRAME_NAME);
    INT_ENUM(GLFW_COCOA_GRAPHICS_SWITCHING);

    INT_ENUM(GLFW_X11_CLASS_NAME);
    INT_ENUM(GLFW_X11_INSTANCE_NAME);

    INT_ENUM(GLFW_NO_API);
    INT_ENUM(GLFW_OPENGL_API);
    INT_ENUM(GLFW_OPENGL_ES_API);

    INT_ENUM(GLFW_NO_ROBUSTNESS);
    INT_ENUM(GLFW_NO_RESET_NOTIFICATION);
    INT_ENUM(GLFW_LOSE_CONTEXT_ON_RESET);

    INT_ENUM(GLFW_OPENGL_ANY_PROFILE);
    INT_ENUM(GLFW_OPENGL_CORE_PROFILE);
    INT_ENUM(GLFW_OPENGL_COMPAT_PROFILE);

    INT_ENUM(GLFW_CURSOR);
    INT_ENUM(GLFW_STICKY_KEYS);
    INT_ENUM(GLFW_STICKY_MOUSE_BUTTONS);
    INT_ENUM(GLFW_LOCK_KEY_MODS);

    INT_ENUM(GLFW_CURSOR_NORMAL);
    INT_ENUM(GLFW_CURSOR_HIDDEN);
    INT_ENUM(GLFW_CURSOR_DISABLED);

    INT_ENUM(GLFW_ANY_RELEASE_BEHAVIOR);
    INT_ENUM(GLFW_RELEASE_BEHAVIOR_FLUSH);
    INT_ENUM(GLFW_RELEASE_BEHAVIOR_NONE);

    INT_ENUM(GLFW_NATIVE_CONTEXT_API);
    INT_ENUM(GLFW_EGL_CONTEXT_API);
    INT_ENUM(GLFW_OSMESA_CONTEXT_API);

    INT_ENUM(GLFW_RESIZABLE);
    INT_ENUM(GLFW_VISIBLE);
    INT_ENUM(GLFW_DECORATED);
    INT_ENUM(GLFW_FOCUSED);
    INT_ENUM(GLFW_AUTO_ICONIFY);
    INT_ENUM(GLFW_FLOATING);
    INT_ENUM(GLFW_MAXIMIZED);
    INT_ENUM(GLFW_RED_BITS);
    INT_ENUM(GLFW_GREEN_BITS);
    INT_ENUM(GLFW_BLUE_BITS);
    INT_ENUM(GLFW_ALPHA_BITS);
    INT_ENUM(GLFW_DEPTH_BITS);
    INT_ENUM(GLFW_STENCIL_BITS);
    INT_ENUM(GLFW_ACCUM_RED_BITS);
    INT_ENUM(GLFW_ACCUM_GREEN_BITS);
    INT_ENUM(GLFW_ACCUM_BLUE_BITS);
    INT_ENUM(GLFW_ACCUM_ALPHA_BITS);
    INT_ENUM(GLFW_AUX_BUFFERS);
    INT_ENUM(GLFW_SAMPLES);
    INT_ENUM(GLFW_REFRESH_RATE);
    INT_ENUM(GLFW_STEREO);
    INT_ENUM(GLFW_SRGB_CAPABLE);
    INT_ENUM(GLFW_DOUBLEBUFFER);
    INT_ENUM(GLFW_CLIENT_API);
    INT_ENUM(GLFW_CONTEXT_CREATION_API);
    INT_ENUM(GLFW_CONTEXT_VERSION_MAJOR);
    INT_ENUM(GLFW_CONTEXT_VERSION_MINOR);
    INT_ENUM(GLFW_CONTEXT_ROBUSTNESS);
    INT_ENUM(GLFW_CONTEXT_RELEASE_BEHAVIOR);
    INT_ENUM(GLFW_OPENGL_FORWARD_COMPAT);
    INT_ENUM(GLFW_OPENGL_DEBUG_CONTEXT);
    INT_ENUM(GLFW_OPENGL_PROFILE);
}