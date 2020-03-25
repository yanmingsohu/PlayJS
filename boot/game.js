import node from '../boot/node.js'

const matrix = node.load('boot/gl-matrix.js');
const yaml = node.load('boot/js-yaml.js');
const { mat4, vec3, vec4 } = matrix;

// 单位矩阵
const ONE = mat4.create();
// 默认操作者
const DEF_OP = { draw: function() {} };


export default {
  createSprite,
  createCamera,
  Vec3Transition,
  Pos3Transition,
  Pos3TransitionLine,
  readSkeleton,
  createAnimation,
  Transformation,
};


//
// 向量的线性过渡, 
// ctrl_vec3 计算结果保存到的向量
// speed 到达目标需要的时间单位秒
//
function Vec3Transition(ctrl_vec3, speed) {
  if (!speed) speed = 1;
  return {
    line,
    speed : setSpeed,
  };

  function setSpeed(s) {
    if (s) speed = s;
  }

  function line(used, end_vec3) {
    let f = speed / used;
    ctrl_vec3[0] = ctrl_vec3[0] + (end_vec3[0] - ctrl_vec3[0])/f;
    ctrl_vec3[1] = ctrl_vec3[1] + (end_vec3[1] - ctrl_vec3[1])/f;
    ctrl_vec3[2] = ctrl_vec3[2] + (end_vec3[2] - ctrl_vec3[2])/f;
  }
}


//
// 向量的线性过渡, 用 xyz 属性表示, 该方法在远离目标时速度快, 接近后速度变慢.
//
function Pos3Transition(ctrl_pos3, speed) {
  if (!speed) speed = 1;
  if (!ctrl_pos3) ctrl_pos3 = {x:0, y:0, z:0};
  return {
    line,
    pos,
    speed : _setSpeed,
  };

  function pos() {
    return ctrl_pos3;
  }

  function _setSpeed(s) {
    speed = s;
  }

  function line(used, end_pos3) {
    let f = used / speed;
    // console.log(ctrl_pos3.y, end_pos3.y, f, speed, used, '*');
    ctrl_pos3.x = ctrl_pos3.x + (end_pos3.x - ctrl_pos3.x)*f;
    ctrl_pos3.y = ctrl_pos3.y + (end_pos3.y - ctrl_pos3.y)*f;
    ctrl_pos3.z = ctrl_pos3.z + (end_pos3.z - ctrl_pos3.z)*f;
    // console.log(ctrl_pos3.y, end_pos3.y, f, speed, used);
  }
}


//
// 向量的线性过渡, 用 xyz 属性表示, 该方法在任何距离上都是线性移动.
//
function Pos3TransitionLine(ctrl_pos3, speed) {
  if (!speed) speed = 1;
  if (!ctrl_pos3) ctrl_pos3 = {x:0, y:0, z:0};
  let last_pos = {x:0, y:0, z:0};

  return {
    line,
    pos,
    speed : _setSpeed,
    update,
  };

  function pos() {
    return ctrl_pos3;
  }

  function _setSpeed(s) {
    speed = s;
  }

  function line(used, end_pos3) {
    let f = used / speed;
    // console.log(ctrl_pos3.y, end_pos3.y, f, speed, used, '*');
    ctrl_pos3.x = last_pos.x + (end_pos3.x - last_pos.x)*f;
    ctrl_pos3.y = last_pos.y + (end_pos3.y - last_pos.y)*f;
    ctrl_pos3.z = last_pos.z + (end_pos3.z - last_pos.z)*f;
    // console.log(ctrl_pos3.y, end_pos3.y, f, speed, used);
  }

  function update(pos3) {
    if (!pos3) pos3 = ctrl_pos3;
    last_pos.x = pos3.x;
    last_pos.y = pos3.y;
    last_pos.z = pos3.z;
  }
}


//
// 3D 转换
// ext - 对象与 ext 组合
//
function Transformation(ext) {
  // 对象的变换矩阵
  const objTr = mat4.create();
  // 对象的中心在模型上的偏移
  const center = vec3.create();
  // 对象的中心在时间上的偏移, 每次都生成新的数组造成内存浪费
  const _where = vec3.create();
  // 变换矩阵初始状态
  var initTr  = ONE;

  const sp = {
    fromTranslate,
    fromRotate,
    translate,
    scale,
    reset,
    rotate,
    rotateX,
    rotateY,
    rotateZ,
    objTr,
    setCenter,
    where,
  };
  return Object.assign(sp, ext);

  //
  // 平移到指定位置 (绝对位移)
  //
  function fromTranslate(vec3pos) {
    mat4.fromTranslation(objTr, vec3pos);
  }

  //
  // 初始化一个单位矩阵并按照给定轴 vec3pos
  // 旋转到指定弧度 rad (绝对角度旋转) 旋转单位: 弧度
  //
  function fromRotate(rad, vec3pos) {
    mat4.fromRotation(objTr, rad, vec3pos);
  }
  
  //
  // 平移 (在当前位置的基础上做相对运动)
  //
  function translate(vec3pos) {
    mat4.translate(objTr, objTr, vec3pos);
  }

  //
  // 不使用矢量化，按给定vec3中的尺寸缩放,
  // vec3s: [x, y, z]
  //
  function scale(vec3s) {
    mat4.scale(objTr, objTr, vec3s); // 缩放
  }

  //
  // 在 x 轴上旋转 rad 弧度.
  //
  function rotateX(rad) {
    mat4.rotateX(objTr, objTr, rad);
  }

  //
  // 在 y 轴上旋转 rad 弧度.
  //
  function rotateY(rad) {
    mat4.rotateY(objTr, objTr, rad);
  }

  //
  // 在 z 轴上旋转 rad 弧度.
  //
  function rotateZ(rad) {
    mat4.rotateY(objTr, objTr, rad);
  }

  //
  // 围绕给定轴 axis 的向量旋转 rad 弧度,
  // axis: [x, y, z]
  //
  function rotate(rad, axis) {
    mat4.retate(objTr, objTr, rad, axis);
  }

  //
  // 设置对象中心在模型中的偏移
  //
  function setCenter(x, y, z) {
    vec3.set(center, x, y, z);
  }

  //
  // 返回对象在世界中的位置
  //
  function where() {
    vec3.transformMat4(_where, center, objTr);
    return _where;
  }

  //
  // 还原到 ma4 状态并记忆该状态;
  // 如果 mat4 为空, 则使用最近一次记忆的状态, 默认状态为单位矩阵
  //
  function reset(m4) {
    if (mat4) {
      mat4.copy(objTr, m4);
      initTr = m4;
    } else {
      mat4.copy(objTr, initTr);
    }
  }
}


//
// 创建摄像机, 可绘制; 要求着色器变量 `mat4 camera`
// operator{draw:Function(used, time, camera)}
//
function createCamera(program, operator) {
  if (!operator) operator = DEF_OP;
  const cameraUi = program.getUniform('camera');

  const cameraPos   = vec3.fromValues(0.0, 1.0,  3.0);
  const cameraFront = vec3.fromValues(0.0, 0.0, -1.0);
  const cameraUp    = vec3.fromValues(0.0, 1.0,  0.0);

  const thiz = Transformation({
    draw,
    setPos,
    lookAt,
    lookAtSprite,
    lookWhere,
    pos,
    up,
    transform,
  });
  return thiz;

  function setPos(x, y, z) {
    vec3.set(cameraPos, x, y, z);
  }

  function lookAt(x, y, z) {
    vec3.set(cameraFront, x, y, z);
  }

  function lookAtSprite(sp) {
    vec3.copy(cameraFront, sp.where());
  }

  //
  // 返回摄像机观察目标向量的引用
  //
  function lookWhere() {
    return cameraFront;
  }

  //
  // 返回摄像机位置的向量引用
  //
  function pos() {
    return cameraPos;
  }

  function up() {
    return cameraUp;
  }

  function draw(used, time) {
    cameraUi.active();
    operator.draw(used, time, thiz);
    mat4.lookAt(thiz.objTr, cameraPos, cameraFront, cameraUp);
    cameraUi.setMatrix4fv(1, gl.GL_FALSE, thiz.objTr);
  }

  //
  // 使用相机矩阵变换顶点坐标
  //
  function transform(outv4, srcv4) {
    mat4.lookAt(thiz.objTr, cameraPos, cameraFront, cameraUp);
    vec4.transformMat4(outv4, srcv4, thiz.objTr);
  }
}


//
// 创建精灵对象, 多个精灵可以引用同一个可绘制对象(模型)
// 精灵对象本身可绘制, 
// 要求着色器变量: `mat4 model`, 或者提供绑定的着色器变量 _shader_var
// operator{draw:Function(used, time, sprite)} 操作者对象, draw 在每一帧上被调用
//
function createSprite(drawObj, operator, _shader_var) {
  const modelUi = drawObj.program.getUniform(_shader_var || 'model', true);
  const draw_arr = [ drawObj ];
  if (!operator) operator = DEF_OP;
  let hidden = false;

  const sp = Transformation({
    draw,
    free,
    add,
    hide,
    show,
  }); 
  return sp;

  //
  // 一个精灵可以有多个可绘制对象组成
  //
  function add(drawable) {
    if (!drawable.draw) throw new Error("not drawable");
    draw_arr.push(drawable);
  }

  //
  // 由框架调用, 用户不要直接调用
  //
  function draw(used, time) {
    if (hidden) return;
    modelUi.active();
    operator.draw(used, time, sp);
    modelUi.setMatrix4fv(1, gl.GL_FALSE, sp.objTr);
    for (let i=0, len=draw_arr.length; i<len; ++i) {
      draw_arr[i].draw(used, time);
    }
  }

  function free() {
    for (let i=0, len=draw_arr.length; i<len; ++i) {
      draw_arr[i].free();
    }
    draw_arr.length = 0;
  }

  function hide() {
    hidden = true;
  }

  function show() {
    hidden = false;
  }
}


//
// 读取骨骼动画数据, 并绑定到着色器和顶点, 骨骼长度最大 10.
// filename 骨骼动画配置文件
// vertexCount 顶点数量(一个顶点可能包含x,y,z坐标占3个float, 这算一个顶点)
// program 已经编译的着色器程序
//
function readSkeleton(filename, vertexCount) {
  if (!vertexCount) throw new Error('vertexCount > 0');
  const SKE_MAX_SIZE = 10;
  const BIND_LEN = 2;

  var config = yaml.load(fs.read_txt(filename));
  if (config.type != 'skeleton') {
    throw new Error("bad file type `"+ config.type +"` in "+ filename);
  }
  if (config.bone.size > SKE_MAX_SIZE) {
    throw new Error("bone size max:"+ SKE_MAX_SIZE);
  }

  var bind = new Float32Array(vertexCount * BIND_LEN);

  bind.fill(-1);
  config.vbind  && _bind(config.bindex, config.vbind,  bind, 1);
  config.vbind4 && _bind(config.bindex, config.vbind4, bind, 4);

  return {
    bind,
    bone : config.bone,
  };

  function _bind(bindex, vbind, to, count) {
    for (var t in vbind) {
      var data = bindex[t];
      var varr = vbind[t];

      for (var vi = 0; vi < varr.length; ++vi) {
        var idx = varr[vi] << 1;
        switch (count) { // no break;
          case 4:
            to[idx+6] = data[0];
            to[idx+7] = data[1];
          case 3:
            to[idx+4] = data[0];
            to[idx+5] = data[1];
          case 2:
            to[idx+2] = data[0];
            to[idx+3] = data[1];
          default:
          case 1:
            to[idx]   = data[0];
            to[idx+1] = data[1];
        }
      }
    }
  }
}


//
// 将骨骼动画与模型绑定
// https://www.khronos.org/opengl/wiki/Skeletal_Animation
// 骨骼会产生两个缓冲区, 一个偏移, 一个旋转,
// 这些行为与着色器脚本绑定.
//
function createAnimation(drawObj) {
  const skeObj = drawObj.getSkeleton();
  if (!skeObj) {
    throw new Error("drawable object must has Skeleton");
  }

  const OFFSET_BUF_SIZE = 3;
  const ROTATE_BUF_SIZE = 9;
  const _pose = {};
  var currentpose;

  const loc = drawObj.program.getLocationIndex('skBind');
  drawObj.bindBuffer(skeObj.bind);
  drawObj.setAttr({ index: loc, vsize: 2, stride: 2 *gl.sizeof$float });

  const bone = skeObj.bone;
  const skeletonUi = drawObj.program.getUniform('skeleton');
  const off = new Float32Array(bone.size * OFFSET_BUF_SIZE);
  //TODO: 需要在着色器中设置变量
  // const rot = new Float32Array(bone.size * ROTATE_BUF_SIZE);

  const animData = {
    offsetBuf : off,
    getOffset,
    getRotate,
  };

  const thiz = {
    pose,
    draw,
    addPose,
  };
  return thiz;

  //
  // 切换动作
  // TODO: 动作混合
  //
  function pose(name) {
    currentpose = _pose[name];
  }

  //
  // 添加一个动作动画
  //
  function addPose(name, animFunc) {
    if (!name) throw new Error("name is null");
    if (!animFunc) throw new Error("animFunc is null");
    _pose[name] = animFunc(animData);
  }

  //
  // 下一帧动画
  //
  function draw(used, time) {
    if (currentpose) {
      currentpose.draw(used, time);
      skeletonUi.setUniform3fv(off);
    }
  }

  //
  // 返回第 i 个偏移参数的缓冲区片段
  //
  function getOffset(i) {
    let begin = i* OFFSET_BUF_SIZE;
    return off.subarray(begin, begin + OFFSET_BUF_SIZE);
  }

  //
  // 返回第 i 个旋转参数的缓冲区片段
  //
  function getRotate(i) {
    let begin = i* ROTATE_BUF_SIZE;
    return rot.subarray(begin, begin + ROTATE_BUF_SIZE);
  }
}

