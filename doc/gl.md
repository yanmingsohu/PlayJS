# gl

OpenGL 应用库, 可以在任意模块直接调用.  
该模块语法与 [GLFW](https://www.glfw.org/docs/latest/modules.html) 语法非常接近可以直接参考.
CPP 参考中的 NULL 值在 js 中用 0 替代.
CPP 参考中的各种指针, 在 js 中都是整数(句柄).

* [OpenGL API 参考](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/)
* [GLFW API 参考](https://www.glfw.org/docs/latest/modules.html)
* [OpenGL 学习1](http://openglbook.com/the-book.html)
* [OpenGL 学习2](https://open.gl/)
* [OpenGL 学习3](https://learnopengl.com/)
* [OpenGL 学习4](http://ogldev.atspace.co.uk/)


# TODO

* [ ] 完成更多 GLFW 函数
* [ ] 完成更多 OpenGL 函数
* [ ] 完成文档


# API

## Version glfwGetVersion()

## string glfwGetVersionString()

## Window glfwCreateWindow(width, height, title[, monitor, share])

## void glfwDestroyWindow(Window)

## Monitor glfwGetPrimaryMonitor()

## Mode glfwGetVideoMode(Monitor)

## void glfwSetWindowMonitor(Window, Monitor, xpos, ypos, width, height, refreshRate)

## void glfwSetWindowSize(Window, width, height)

## void glfwWindowHint(hint, value)


# Class

## Version

当前 GLFW 版本, 该对象有以下属性

* major
* minor
* rev


## Mode

显示器模式, 有以下属性

* width
* height
* redBits
* greenBits
* blueBits
* refreshRate


## Window

窗口句柄, 通过消息总线传递, 支持多线程访问.
用完后需要释放句柄.


## Monitor

监视器句柄, 通过消息总线传递, 支持多线程访问.
句柄无需释放.


# const

gl.const 来引用这些常量

## GLFW_RESIZABLE