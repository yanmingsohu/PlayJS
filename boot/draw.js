//
// 在 OpenGL 上做一层 api, 使绘制函数更易于使用.
//
console.log('GLFW version:', gl.glfwGetVersionString());
import node from '../boot/node.js'
const matrix = node.load('boot/gl-matrix.js');

export default {
  createWindow,
  checkGLerr,
  createShader,
  createProgram,
  createBasicDrawObject,
  createTexture,
  delayDraw,
  showRate,
};


function createWindow(w, h, title) {
  if (!w) w = global.screen.width  || 1024;
  if (!h) h = global.screen.height || 768;

  const moni = gl.glfwGetPrimaryMonitor();
  const mode = gl.glfwGetVideoMode(moni);
  console.log("Primary Monitor:", JSON.stringify(mode));

  // 4 倍抗锯齿
  gl.glfwWindowHint(gl.GLFW_SAMPLES, 4);
  const window = gl.glfwCreateWindow(w, h, title || "PlayJS");
  gl.glfwMakeContextCurrent(window);
  gl.glewInit();
  gl.glEnable(gl.GL_DEPTH_TEST);
  gl.glEnable(gl.GL_MULTISAMPLE);  
  gl.glViewport(0, 0, w, h);

  let clearFlag = gl.GL_DEPTH_BUFFER_BIT | gl.GL_COLOR_BUFFER_BIT;
  let inputs = createInput(window);
  let draw_list = [];
  let timeValue, used, lastTime = gl.glfwGetTime();

  return {
    fullscreen,
    destroy,
    onKey,
    center,
    setClearColor,
    nextFrame,
    add,
    remove,
    shouldClose,
    notClosed,
    prepareDraw,
    input,
  };

  //
  // 添加一个可绘制对象
  //
  function add(drawable) {
    if (!drawable.draw) throw new Error("not drawable");
    draw_list.push(drawable);
  }

  //
  // 删除绘制对象, 成功返回 true.
  // 找不到该对象返回 false.
  //
  function remove(drawable) {
    for (let i=0, len=draw_list.length; i<len; ++i) {
      if (draw_list[i] == drawable) {
        draw_list.splice(i, 1);
        return true;
      }
    }
    return false;
  }

  //
  // 窗口移动到屏幕中央
  //
  function center() {
    var wsize = gl.glfwGetWindowSize(window);
    var x = (mode.width - wsize.width)/2;
    var y = (mode.height - wsize.height)/2;
    gl.glfwSetWindowPos(window, x, y);
  }

  //
  // 在进入循环前执行一次
  //
  function prepareDraw() {
    lastTime = gl.glfwGetTime();

    for (var len = draw_list.length, i=0; i<len; ++i) {
      if (draw_list[i].prepareDraw) {
        draw_list[i].prepareDraw();
      }
    }
  }

  //
  // 绘制下一帧, 如果窗口需要关闭返回 false.
  //
  function nextFrame() {
    timeValue = gl.glfwGetTime();
    used = timeValue - lastTime;
    lastTime = timeValue;
    
    inputs.check(used, timeValue);
    gl.glClear(clearFlag);

    for (var len = draw_list.length, i=0; i<len; ++i) {
      draw_list[i].draw(used, timeValue);
    }

    gl.glfwSwapBuffers(window);
    gl.glfwPollEvents();
    return !gl.glfwWindowShouldClose(window);
  }

  //
  // 通知窗口应该关闭
  //
  function shouldClose() {
    gl.glfwSetWindowShouldClose(window, gl.GL_TRUE);
  }

  //
  // 不应该退出返回 true.
  //
  function notClosed() {
    return !gl.glfwWindowShouldClose(window);
  }
  
  //
  // 设置为全屏
  //
  function fullscreen() {
    gl.glfwSetWindowMonitor(window, moni, 0, 0, 
        mode.width, mode.height, mode.refreshRate);
    gl.glViewport(0, 0, mode.width, mode.height);
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
    inputs.onKey(keycode, state, data, callback);
  }

  //
  // 返回用户输入对象
  //
  function input() {
    return inputs;
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
  // 如果 glfw 没有初始化会崩溃
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
  const proj = matrix.mat4.create(1);
  const program = gl.glCreateProgram();
  const uniformMap = {};

  return {
    attach,
    getUniform,
    setProjection,
    getProjection,
    readShader,
    readFragShader,
    readVertexShader,
    readGeoShader,
    getLocationIndex,
    active,
    link,
    _program : program,
  };

  function active() {
    gl.glUseProgram(program); 
  }

  //
  // 从文件中读取着色器, 并绑定到当前程序, 返回 shader 句柄.
  //
  function readShader(filename, type) {
    var code = fs.read_txt(filename);
    var shader = createShader(code, type);
    attach(shader);
    return shader;
  }

  function readVertexShader(filename) {
    return readShader(filename, gl.GL_VERTEX_SHADER);
  }

  function readFragShader(filename) {
    return readShader(filename, gl.GL_FRAGMENT_SHADER);
  }

  function readGeoShader(filename) {
    return readShader(filename, gl.GL_GEOMETRY_SHADER);
  }

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

  function getUniform(name, ignore_errors) {
    var uni = uniformMap[name];
    if (!uni) { 
      var loc = gl.glGetUniformLocation(program, name);
      if (loc < 0) {
        if (!ignore_errors) {
          throw new Error("Uniform '"+ name +"' not exists in shader");
        } else {
          console.warn("Uniform '"+ name +"' not exists in shader");
        }
      }
      uni = uniformMap[name] = Uniform(loc, program);
    }
    return uni;
  }

  function setProjection(fovy, aspect, near, far) {
    matrix.mat4.perspective(proj, fovy, aspect, near, far);
    var projectionVar = getUniform('projection');
    projectionVar.active();
    projectionVar.setMatrix4fv(1, gl.GL_FALSE, proj);
  }

  function getProjection() {
    return proj;
  }

  //
  // 返回着色器中变量 name 的 location 索引值
  //
  function getLocationIndex(name) {
    var i = gl.glGetAttribLocation(program, name);
    if (i < 0) throw new Error("location not found "+ name);
    return i;
  }
}


//
// 设置全局变量
//
function Uniform(loc, program) {
  return {
    _loc : loc,
    active,
    setMatrix4fv,
    setUniform4f,
    setUniform3f,
    setUniform1f,
    setUniform1i,
    setUniform2uiv,
    setUniform3fv,
    setUniform4fv,
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

  function setUniform3f(v1, v2, v3) {
    gl.glUniform3f(loc, v1, v2, v3);
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

  function setUniform2uiv(uint_arr) {
    if (uint_arr.constructor != Uint32Array) {
      throw new Error("must Uint32Array");
    }
    gl.glUniform2uiv(loc, uint_arr);
  }

  function setUniform3fv(float32arr) {
    if (float32arr.constructor != Float32Array) {
      throw new Error("must Float32Array");
    }
    gl.glUniform3fv(loc, float32arr);
  }

  function setUniform4fv(float32arr) {
    if (float32arr.constructor != Float32Array) {
      throw new Error("must Float32Array");
    }
    gl.glUniform4fv(loc, float32arr);
  }
}


//
// 一个对象可以绘制多次
//
function createBasicDrawObject(programObj) {
  let program = programObj._program;
  let VAO = gl.glGenVertexArrays(1);
  let buffers = [];
  let vertices_count = 0;
  let element_count = 0;
  let skeleton;
  let texture = createTexture();
  let drawMode = gl.GL_TRIANGLES;
  // 顶点索引数组类型
  let index_ele_type;

  const thiz = {
    draw,               
    prepareDraw,
    setAttr,
    setAttrI,
    addVertices,
    addVerticesElements,
    bindBuffer,
    setModelData,
    setSkeleton,
    getSkeleton,
    setMode,
    free,
    getTexture,
    setAttrF : setAttr,
    program  : programObj,
  };
  return thiz;

  
  function prepareDraw() {}

  //
  // 返回绑定的纹理对象
  //
  function getTexture() {
    return texture;
  }

  //
  // 把模型数据作为当前绘制对象的数据
  //
  function setModelData(modelObj) {
    if (!modelObj.setupDraw) {
      throw new Error("model obj cannot 'setupDraw()'");
    }
    modelObj.setupDraw(thiz, programObj);
  }

  //
  // vertices : Float32Array 对象, 存储顶点
  // a_vertices_count: 顶点数量 (每个顶点可以存储多种数据)
  // attr : 属性配置, 
  //
  function addVertices(vertices, a_vertices_count, usage) {
    gl.glBindVertexArray(VAO);
    _vertices(vertices, usage || gl.GL_STATIC_DRAW);
    vertices_count = a_vertices_count;
    thiz.draw = draw1;
  }

  //
  // vertices : Float32Array 对象, 存储顶点
  // indices : Uint32Array  对象, 存储索引
  //
  function addVerticesElements(vertices, indices, usage) {
    gl.glBindVertexArray(VAO);
    usage = usage || gl.GL_STATIC_DRAW;
    _vertices(vertices, usage);
    _indices(indices, usage);
    element_count = indices.length;
    thiz.draw = draw2;
  }

  //
  // 绑定着色器的浮点类型缓冲区指针
  // 必须在绑定了顶点缓冲区之后再设置属性
  // 属性在 GLSL 中用 `layout (location = 0)` 来定义,
  // location 与 attr.index 对应.
  // 
  //    attr.usage  -- 默认 gl.GL_STATIC_DRAW
  //    attr.type   -- 默认 gl.GL_FLOAT
  //    attr.vsize  -- 每个顶点的单元数量, 必须是 1,2,3,4
  //    attr.stride -- 字节, 顶点之间的间隙长度, 字节
  //    attr.normalized -- 默认 false
  //    attr.index  -- 顶点属性索引
  //    attr.offset -- 数据指针偏移
  //
  function setAttr(attr) {
    _check_attr(attr);
    gl.glVertexAttribPointer(
      attr.index, 
      attr.vsize, 
      attr.type || gl.GL_FLOAT, 
      attr.normalized || gl.GL_FALSE, 
      attr.stride, 
      attr.offset || 0);
    checkGLerr("glVertexAttribPointer", 1);
    gl.glEnableVertexAttribArray(attr.index);
  }


  //
  // 绑定着色器的整数类型缓冲区指针
  // 必须在绑定了顶点缓冲区之后再设置属性
  //
  function setAttrI(attr) {
    _check_attr(attr);
    gl.glVertexAttribIPointer(
      attr.index,
      attr.vsize,
      attr.type || gl.GL_INT,
      attr.stride,
      attr.offset || 0);
    checkGLerr("glVertexAttribIPointer", 1);
    gl.glEnableVertexAttribArray(attr.index);
  }


  function _check_attr(attr) {
    if (!attr.vsize) throw new Error("'vsize' must number");
    if (!attr.stride) throw new Error("'stride' must number");
    if (isNaN(attr.index)) throw new Error("'index' must number");
  }


  function _vertices(vertices, usage) {
    let VBO = gl.glGenBuffers(1);
    buffers.push(VBO);
    gl.glBindBuffer(gl.GL_ARRAY_BUFFER, VBO);  
    gl.glBufferData(gl.GL_ARRAY_BUFFER, vertices, usage);
  }


  function _indices(indices, usage) {
    index_ele_type = _check_index_ele_type(indices);
    var EBO = gl.glGenBuffers(1);
    buffers.push(EBO);
    gl.glBindBuffer(gl.GL_ELEMENT_ARRAY_BUFFER, EBO);
    gl.glBufferData(gl.GL_ELEMENT_ARRAY_BUFFER, indices, usage);
  }

  //
  // 绑定一个非顶点缓冲区, 用于自定义数据.
  //
  function bindBuffer(typedarr, type, usage) {
    gl.glBindVertexArray(VAO);
    if (!usage) usage = gl.GL_STATIC_DRAW;
    if (!type)  type = gl.GL_ARRAY_BUFFER;

    var bo = gl.glGenBuffers(1);
    buffers.push(bo);
    gl.glBindBuffer(type, bo);
    gl.glBufferData(type, typedarr, usage);
    return bo;
  }


  function draw() {
    throw new Error("No data to be drawn");
  }


  function draw1(u, t) {
    gl.glUseProgram(program);
    gl.glBindVertexArray(VAO);
    texture.draw(u, t);
    gl.glDrawArrays(drawMode, 0, vertices_count);
  }


  function draw2(u, t) {
    gl.glUseProgram(program);
    gl.glBindVertexArray(VAO);
    texture.draw(u, t);
    gl.glDrawElements(drawMode, element_count, index_ele_type, 0)
  }


  function _check_index_ele_type(t) {
    if (t.constructor === Uint32Array) {
      return gl.GL_UNSIGNED_INT;
    }
    if (t.constructor === Uint8Array) {
      return gl.GL_UNSIGNED_BYTE;
    }
    if (t.constructor === Uint16Array) {
      return gl.GL_UNSIGNED_SHORT;
    }
    throw new TypeError("Index Array "
      +"Must be Uint32Array or Uint8Array or Uint16Array");
  }


  //
  // 模式: GL_POINTS, GL_LINES, GL_TRIANGLES(默认), GL_TRIANGLE_STRIP
  //
  function setMode(mode) {
    drawMode = mode;
  }


  function setSkeleton(sk) {
    if (!sk) throw new Error("null argument");
    skeleton = sk;
  }


  function getSkeleton() {
    return skeleton;
  }


  function free() {
    for (var i=0; i<buffers.length; ++i) {
      gl.glDeleteBuffers(buffers[i]);
    }
    gl.glDeleteVertexArrays(VAO);
    texture.free();
    // console.debug("VAO and VBO delete");
  }
}


//
// 创建一个纹理, 该纹理始终绑定一个纹理缓冲区
// 纹理可以释放或切换到其他图片, 切换时之前管理的缓冲区将被释放.
//
function createTexture() {
  let _texture = -1;
  let _target;

  const thiz = {
    bindTexImage,
    loadTexImage,
    setParameter,
    bindCubeMap,
    draw,
    free,
  };
  return thiz;
  
  //
  // format - GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, 
  //    GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER, 
  //    GL_RGBA_INTEGER, GL_BGRA_INTEGER, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, 
  //    GL_DEPTH_STENCIL
  //
  // vtype - GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, 
  //    GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, 
  //    GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, 
  //    GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV, 
  //    GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, 
  //    GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV, 
  //    GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV, 
  //    GL_UNSIGNED_INT_10_10_10_2, and GL_UNSIGNED_INT_2_10_10_10_REV
  //
  // _internal - GL_RGB(默认), GL_RGBA
  //
  function bindTexImage(buffer, width, height, format, vtype, _internal) {
    free();
    _texture = gl.glGenTextures(1);
    _target = gl.GL_TEXTURE_2D;
    gl.glBindTexture(_target, _texture);
    gl.glTexImage2D(_target, 0, _internal || gl.GL_RGB,
        width, height, 0, format, vtype, buffer);
    gl.glGenerateMipmap(_target);
  }

  //
  // TODO: 设置天空盒纹理
  //
  function bindCubeMap() {
    throw new Error("未实现");
    _target = gl.GL_TEXTURE_CUBE_MAP;
  }

  //
  // 设置纹理属性
  //
  function setParameter(name, param) {
    gl.glBindTexture(_target, _texture);
    gl.glTexParameteri(_target, name, param);
    // gl.glTexParameteri(gl.GL_TEXTURE_2D, 
    //   gl.GL_TEXTURE_WRAP_S, gl.GL_MIRRORED_REPEAT);
    // gl.glTexParameteri(gl.GL_TEXTURE_2D, 
    //   gl.GL_TEXTURE_MIN_FILTER, gl.GL_LINEAR_MIPMAP_LINEAR);
    // gl.glTexParameteri(gl.GL_TEXTURE_2D, 
    //   gl.GL_TEXTURE_MAG_FILTER, gl.GL_LINEAR);
  }

  function loadTexImage(file) {
    image.flip_vertically_on_load(true);
    let img = image.load(file);
    bindTexImage(img.data, img.x, img.y, gl.GL_RGB, gl.GL_UNSIGNED_BYTE);
  }

  function draw() {
    if (_texture > 0) {
      gl.glBindTexture(gl.GL_TEXTURE_2D, _texture);
    }
  }

  function free() {
    if (_texture > 0) {
      gl.glDeleteTextures(_texture);
      _texture = null;
    }
  }
}


function createInput(window) {
  const key_listener = [];
  let paused = false;

  const thiz = {
    check,
    onKey,
    pressOnce,
    pause,
    unbind,
  };
  return thiz;

  //
  // 由系统调用
  //
  function check(u, t) {
    if (paused) return;
    for (var i=0; i<key_listener.length; ++i) {
      var li = key_listener[i];
      if (gl.glfwGetKey(window, li[0]) == li[1]) {
        li[2](li[3]);
      }
    }
  }

  //
  // bool 为 true 时暂停输入判断, 默认为 false
  //
  function pause(bool) {
    paused = (true == bool);
  }

  //
  // 绑定一个键盘事件的回调函数
  //
  function onKey(keycode, state, data, callback) {
    key_listener.push([keycode, state || 0, callback, data]);
  }

  //
  // 绑定一个键盘按键, 在按下后释放前只触发一次.
  //
  function pressOnce(key, press, _release) {
    let notrel = 0;
    if (press == null && _release == null)
      throw new Error("set press or release callback function");
  
    onKey(key, gl.GLFW_PRESS, 0, function() {
      if (notrel) return;
      notrel = true;
      press && press();
    });
  
    onKey(key, gl.GLFW_RELEASE, 0, function() {
      if (!notrel) return;
      notrel = false;
      _release && _release();
    });
  }

  //
  // 解除按键绑定的回调函数
  //
  function unbind(keycode) {
    for (var i=key_listener.length-1; i>=0; --i) {
      var li = key_listener[i];
      if (li[0] === keycode) {
        key_listener.splice(i, 1);
      }
    }
  }
}


//
// 对于不需要每帧都绘制的对象, 延迟绘制.
//
function delayDraw(wrapDrawble, wait) {
  if (!wrapDrawble.draw) throw new Error("not drawable");
  let total = 0;
  return {
    draw : draw,
  }

  function draw(used, time) {
    total += used;
    if (total > wait) {
      total = 0;
      wrapDrawble.draw(used, time);
    }
  }
}


//
// 用于显示帧率
//
function showRate() {
  var frameCount = 0;
  var min = 1000;
  var max = 0;
  var c = 0;

  return {
    draw : draw,
  };

  function draw(used) {
    ++frameCount;  
    c = parseInt(1 / used);

    if (frameCount % 1000 == 0) {
      max = 0; min = 1000;
    }
    if (c > max) max = c;
    if (c < min) min = c;

    if (frameCount % 10 == 0) {
      console.line('Frame:', frameCount, 
        'Avg:', parseInt(frameCount / gl.glfwGetTime()), 
        'Real:', c, '[', min, '-', max, ']   ');
    }
  }
}


function checkGLerr(name, _throw) {
  let code = gl.glGetError();
  let msg;
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
  let str = [ "GL err:", name||'', '0x'+code.toString(16), msg ].join(' ');
  if (_throw) {
    throw new Error(str);
  }
  console.log(str);
}