# gl

3D 视频加速库继承了 GLFW 与 GLEW, 将所有公共的 c/c++ 函数导出到 javascript
中, 命名空间为 `gl` 函数名原样保留, 常量名和宏定义名原样保留; 如果本机方法没有
返回值, js 方法返回 `undefined`; 如果本机方法返回一个变量, js 原样返回这个包装
后的变量, 数字/字符串/数组类型原样返回, 如果本机返回指针, js 返回一个代表句柄
的普通数字; 如果本机方法通过多个指针返回多个值, 在 js 函数上, 直接用对象返回
多个值, 并且这些参数不在形参列表中出现;


# GLFW

可以在 js 环境的 'gl' 前缀中直接方法这些方法和常量;
glfwGetPrimaryMonitor() 返回的句柄可以直接传给 glfwGetVideoMode()
句柄的有效期由 PlayJS 管理.


## 特殊说明

Monitor/Window 等句柄可以跨线程访问.
Window 句柄用 glfwDestroyWindow() 方法释放.


#### Monitor glfwGetPrimaryMonitor()

返回主显示器的句柄, 实际的本机指针由 PlayJS 管理.


#### Mode glfwGetVideoMode(Monitor)

Mode 是个对象, 对象中有 `width`, `height` 等属性来描述给定监视器当前状态.


# GLEW

可以在 js 环境的 'gl' 前缀中直接方法这些方法和常量;
glBufferData() 的本机方法中有一个参数指向数组, 该参数 用 js 环境中的 
TypedArray 代替, 长度参数被省略,  常量参数直接从 `gl` 中取值.
倘若需要 c 语言环境中 `sizeof(float)` 的值, 
则在 js 中访问 `gl.sizeof$float` 这个常量.


## 特殊说明


#### Array|int glGenBuffers(size)

如果 size == 1, 则返回一个数字; 如果 size > 1, 则返回一个数组包含指定数量的数字;
该数字是 OpenGL 状态机生成的缓冲区句柄.


# 参考

* [OpenGL API 参考](https://www.khronos.org/registry/OpenGL-Refpages)
* [GLFW API 参考](https://www.glfw.org/docs/latest/modules.html)
* [OpenGL 学习1](http://openglbook.com/the-book.html)
* [OpenGL 学习2](https://open.gl/)
* [OpenGL 学习3](https://learnopengl.com/)
* [OpenGL 学习4](http://ogldev.atspace.co.uk/)


# TODO

* [ ] 完成更多 GLFW 函数
* [ ] 完成更多 OpenGL 函数
* [ ] 完成文档
