//
// 在 OpenGL 上做一层 api, 使绘制函数更易于使用.
//
console.log('GLFW version:', gl.glfwGetVersionString());
export default {
  createWindow          : createWindow,
  checkGLerr            : checkGLerr,
  createShader          : createShader,
  createProgram         : createProgram,
  createBasicDrawObject : createBasicDrawObject,
};


function createWindow(w, h, title) {
  if (!w) w = 1024;
  if (!h) h = 768;

  var moni = gl.glfwGetPrimaryMonitor();
  var mode = gl.glfwGetVideoMode(moni);
  console.log("Primary Monitor:", JSON.stringify(mode));

  var window = gl.glfwCreateWindow(w, h, title || "PlayJS");
  gl.glfwMakeContextCurrent(window);
  gl.glewInit();
  gl.glEnable(gl.GL_DEPTH_TEST);  
  gl.glViewport(0, 0, w, h);

  var clearFlag = gl.GL_DEPTH_BUFFER_BIT | gl.GL_COLOR_BUFFER_BIT;
  var key_listener = [];
  var draw_list = [];

  return {
    fullscreen    : fullscreen,
    destroy       : destroy,
    onKey         : onKey,
    setClearColor : setClearColor,
    nextFrame     : nextFrame,
    add           : add,
    shouldClose   : shouldClose,
  };

  //
  // 添加一个可绘制对象
  //
  function add(drawable) {
    if (!drawable.draw) throw new Error("not drawable");
    draw_list.push(drawable);
  }

  //
  // 绘制下一帧, 如果窗口需要关闭返回 false.
  //
  function nextFrame() {
    if (gl.glfwWindowShouldClose(window))
      return false;
    
    for (var i=key_listener.length-1; i>=0; --i) {
      var li = key_listener[i];
      if (gl.glfwGetKey(window, li[0]) == li[1]) {
        li[2](li[3]);
      }
    }

    gl.glClear(clearFlag);

    for (var i=draw_list.length-1; i>=0; --i) {
      draw_list[i].draw();
    }

    gl.glfwSwapBuffers(window);
    gl.glfwPollEvents();
    return true;
  }

  //
  // 通知窗口应该关闭
  //
  function shouldClose() {
    gl.glfwSetWindowShouldClose(window, gl.GL_TRUE);
  }
  
  //
  // 设置为全屏
  //
  function fullscreen() {
    gl.glfwSetWindowMonitor(window, moni, 0, 0, 
        mode.width, mode.height, mode.refreshRate);
  }

  //
  // 释放内存
  //
  function destroy() {
    gl.glfwDestroyWindow(window);
  }

  //
  // 绑定键盘事件
  //
  function onKey(keycode, state, data, callback) {
    key_listener.push([keycode, state || gl.GLFW_PRESS, callback, data]);
  }

  //
  // 设置背景颜色
  //
  function setClearColor(a) {
    gl.glClearColor(a[0], a[1], a[2], a[3]);
  }
}


//
// 创建着色器
//
function createShader(txtCode, type) {
  var shader = gl.glCreateShader(type);
  gl.glShaderSource(shader, txtCode);
  gl.glCompileShader(shader);
  if (!gl.glGetShaderiv(shader, gl.GL_COMPILE_STATUS)) {
    var msg = gl.glGetShaderInfoLog(shader);
    throw new Error(msg);
  }
  checkGLerr("createShader");
  return shader;
}


//
// 创建着色器程序, 并连接多个着色器
//
function createProgram() {
  var program = gl.glCreateProgram();
  var uniformMap = {};

  return {
    attach        : attach,
    link          : link,
    _program      : program,
    getUniform    : getUniform,
  };

  //
  // 连接着色器
  //
  function attach(shader) {
    gl.glAttachShader(program, shader);
    gl.glDeleteShader(shader);
  }

  //
  // 编译连接程序
  //
  function link() {
    gl.glLinkProgram(program);

    if(! gl.glGetProgramiv(program, gl.GL_LINK_STATUS)) {
      var msg = gl.glGetProgramInfoLog(program);
      throw new Error(msg);
    }
  }

  function getUniform(name) {
    var uni = uniformMap[name];
    if (!uni) { 
      var loc = gl.glGetUniformLocation(program, name);
      uni = uniformMap[name] = Uniform(loc, program);
    }
    return uni;
  }
}


//
// 设置全局变量
//
function Uniform(loc, program) {
  return {
    _loc : loc,
    active : active,
    setUniform4f : setUniform4f,
    setUniform1f : setUniform1f,
    setUniform1i : setUniform1i,
    setMatrix4fv : setMatrix4fv,
  };

  //
  // 在 set (多个)变量前, 执行一次该方法.
  //
  function active() {
    gl.glUseProgram(program); 
  }

  function setUniform4f(v1, v2, v3, v4) {
    gl.glUniform4f(loc, v1, v2, v3, v4);
  }

  function setUniform1f(v1) {
    gl.glUniform1f(loc, v1);
  }

  function setUniform1i(v1) {
    gl.glUniform1i(loc, v1);
  }

  function setMatrix4fv(count, transpose, value) {
    gl.glUniformMatrix4fv(loc, count, transpose, value);
  }
}


function createBasicDrawObject(programObj) {
  var program = programObj._program;
  var VAO = gl.glGenVertexArrays(1);
  var vertices_count = 0;
  var element_count = 0;

  const _ret = {
    draw        : draw,
    setAttr     : setAttr,
    addVertices : addVertices,
    addVerticesElements : addVerticesElements,
    loadTexImage : loadTexImage,
  };
  return _ret;

  function loadTexImage(file) {
    image.flip_vertically_on_load(true);
    var img = image.load(file);
    var texture = gl.glGenTextures(1);
    gl.glBindTexture(gl.GL_TEXTURE_2D, texture);  

    gl.glTexParameteri(gl.GL_TEXTURE_2D, 
      gl.GL_TEXTURE_WRAP_S, gl.GL_MIRRORED_REPEAT);
    gl.glTexParameteri(gl.GL_TEXTURE_2D, 
      gl.GL_TEXTURE_MIN_FILTER, gl.GL_LINEAR_MIPMAP_LINEAR);
    gl.glTexParameteri(gl.GL_TEXTURE_2D, 
      gl.GL_TEXTURE_MAG_FILTER, gl.GL_LINEAR);
    
    gl.glTexImage2D(gl.GL_TEXTURE_2D, 0, gl.GL_RGB, 
            img.x, img.y, 0, gl.GL_RGB, gl.GL_UNSIGNED_BYTE, img.data);
    gl.glGenerateMipmap(gl.GL_TEXTURE_2D);
  }

  //
  // vertices : Float32Array 对象, 存储顶点
  // attr : 属性配置, 
  //
  function addVertices(vertices, _vertices_count, usage) {
    _vertices(vertices, usage || gl.GL_STATIC_DRAW);
    vertices_count = _vertices_count;
    _ret.draw = draw1;
  }

  //
  // vertices : Float32Array 对象, 存储顶点
  // indices : Uint32Array  对象, 存储索引
  //
  function addVerticesElements(vertices, indices, usage) {
    var usage = usage || gl.GL_STATIC_DRAW;
    _vertices(vertices, usage);
    _indices(indices, usage);
    element_count = indices.length;
    _ret.draw = draw2;
  }

  //
  // 必须在绑定了顶点缓冲区之后再设置属性
  // 属性在 GLSL 中用 `layout (location = 0)` 来定义,
  // location 与 attr.index 对应.
  // 
  //    attr.usage  -- 默认 gl.GL_STATIC_DRAW
  //    attr.type   -- 默认 gl.GL_FLOAT
  //    attr.vsize  -- 每个顶点的单元数量, 必须是 1,2,3,4
  //    attr.stride -- 字节, 顶点之间的间隙长度
  //    attr.normalized -- 默认 false
  //    attr.index  -- 顶点属性索引
  //    attr.offset -- 数据指针偏移
  //
  function setAttr(attr) {
    gl.glVertexAttribPointer(
        attr.index, 
        attr.vsize, 
        attr.type || gl.GL_FLOAT, 
        attr.normalized || gl.GL_FALSE, 
        attr.stride, 
        attr.offset || 0);
    gl.glEnableVertexAttribArray(attr.index);
  }

  function _vertices(vertices, usage) {
    var VBO = gl.glGenBuffers(1);
    gl.glBindVertexArray(VAO);
    gl.glBindBuffer(gl.GL_ARRAY_BUFFER, VBO);  
    gl.glBufferData(gl.GL_ARRAY_BUFFER, vertices, usage);
  }

  function _indices(indices, usage) {
    var EBO = gl.glGenBuffers(1);
    gl.glBindBuffer(gl.GL_ELEMENT_ARRAY_BUFFER, EBO);
    gl.glBufferData(gl.GL_ELEMENT_ARRAY_BUFFER, indices, usage);
  }

  function draw() {
    throw new Error("No data to be drawn");
  }

  function draw1() {
    gl.glUseProgram(program);
    gl.glBindVertexArray(VAO);
    gl.glDrawArrays(gl.GL_TRIANGLES, 0, vertices_count);
  }

  function draw2() {
    gl.glUseProgram(program);
    gl.glBindVertexArray(VAO);
    gl.glDrawElements(gl.GL_TRIANGLES, element_count, gl.GL_UNSIGNED_INT, 0)
  }
}


function checkGLerr(name) {
  var code = gl.glGetError();
  var msg;
  switch(code) {
    case gl.GL_INVALID_ENUM:
        msg = `An unacceptable value is specified for an enumerated argument. 
        The offending command is ignored and has no other side effect than to 
        set the error flag.`;
        break;
    case gl.GL_INVALID_VALUE:
        msg = `A numeric argument is out of range. The offending command is 
        ignored and has no other side effect than to set the error flag.`;
        break;
    case gl.GL_INVALID_OPERATION:
        msg = `The specified operation is not allowed in the current state. 
        The offending command is ignored and has no other side effect than 
        to set the error flag.`;
        break;
    case gl.GL_INVALID_FRAMEBUFFER_OPERATION:
        msg = `The framebuffer object is not complete. The offending command 
        is ignored and has no other side effect than to set the error flag.`;
        break;
    case gl.GL_OUT_OF_MEMORY:
        msg = `There is not enough memory left to execute the command. 
        The state of the GL is undefined, except for the state of the error flags, 
        after this error is recorded.`;
        break;
    case gl.GL_STACK_UNDERFLOW:
        msg = `An attempt has been made to perform an operation that would 
        cause an internal stack to underflow.`;
        break;
    case gl.GL_STACK_OVERFLOW:
        msg = `An attempt has been made to perform an operation that would 
        cause an internal stack to overflow.`;
        break;

    default:
        'unknow';

    case gl.GL_NO_ERROR:
        return;
  }
  console.log("GL err:", name, '0x'+code.toString(16), msg);
}