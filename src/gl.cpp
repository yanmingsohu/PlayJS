#include "glfw/include/GLFW/glfw3.h"
#include "vm.h"
#include "util.h"

#include <atomic>
#include <system_error>

static const char* INIT_FAIL = "cannot init glfw";
static std::atomic<int> gl_count = 0;


JS_FUNC_TPL(js_glfwCreateWindow, callee, args, argc, info, vm) {
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        println("window terminate");
        return 0;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    return 0;
}


static void gl_error_callback(int error, const char* desc) {
    println(desc, 0, LERROR);
}


void installGL(VM* vm) {
    if (gl_count == 0) {
        glfwSetErrorCallback(&gl_error_callback);
        
        if (GLFW_FALSE == glfwInit())
            throw std::runtime_error(INIT_FAIL);
    }
    ++gl_count;

    DEF_GLOBAL(vm, gl);
    DEF_JS_FUNC(vm, 0, gl, glfwCreateWindow, js_glfwCreateWindow);
}


void unstallGL(VM* vm) {
    if (--gl_count <= 0) {
        gl_count = 0;
        glfwTerminate();
    }
}