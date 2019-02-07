const path = require('path');
const cppp = require('./parser.js');


module.exports = {
//
// 需要解析的 GL 头文件
//
heades : [
  {
    file: path.join(__dirname, '../deps/glfw/include/GLFW/glfw3.h'),
    parser : cppp.glfw,
  },
  {
    // file: 'C:/Program Files (x86)/Windows Kits/8.1/Include/um/gl/GL.h',
    file: path.join(__dirname, '../deps/glew/include/GL/glew.h'),
    parser : cppp.gl,
  },
],

//
// 已经实现的代码
//
sourceCC : [
  path.join(__dirname, '../src/glfw.cpp'),
  path.join(__dirname, '../src/glcore.cpp'),
],

//
// c++ 中空返回值的符号列表
//
voidType: {
  'void': 1,
  'GLvoid': 1,
},

//
// 跳过这些函数的代码生成
//
skipFunc : {
  'glfwInit' :1,
  'glfwTerminate' :1,
  'glfwSetErrorCallback' :1,
  'glfwSetMonitorUserPointer': 1,
  'glfwGetMonitorUserPointer': 1,
  'glfwSetMonitorCallback':1,
  'glfwSetMouseButtonCallback':1, 
  'glfwSetKeyCallback': 1, 
  'glfwSetCharCallback': 1, 
  'glfwSetCharModsCallback': 1,
  'glfwSetCursorPosCallback':1, 
  'glfwSetCursorEnterCallback':1,
  'glfwSetScrollCallback':1,
  'glfwSetDropCallback':1,
  'glfwSetJoystickCallback':1,
  'glfwSetWindowSizeCallback':1,
  'glfwSetWindowCloseCallback':1,
  'glfwSetWindowRefreshCallback':1,
  'glfwSetWindowFocusCallback':1,
  'glfwSetWindowPosCallback': 1,
  'glfwSetWindowIconifyCallback':1,
  'glfwSetWindowMaximizeCallback':1,
  'glfwSetFramebufferSizeCallback':1,
  'glfwSetWindowContentScaleCallback':1,
  'glfwSetWindowUserPointer':1,
  'glfwSetJoystickUserPointer':1,
  'glfwGetRequiredInstanceExtensions':1,
  'glfwGetInstanceProcAddress':1,
  'glfwGetPhysicalDevicePresentationSupport':1,
  'glfwCreateWindowSurface':1,
},

};
