import node from '../boot/node.js'

const matrix = node.load('boot/gl-matrix.js');
const yaml = node.load('boot/js-yaml.js');

// 单位矩阵
const ONE = matrix.mat4.create(1);
// 默认操作者
const DEF_OP = { op: function() {} };


export default {
  createSprite    : createSprite,
  createShowRate  : createShowRate,
  createCamera    : createCamera,
  Vec3Transition  : Vec3Transition,
  readSkeleton    : readSkeleton,
  createAnimation : createAnimation,
  FixedWalk       : FixedWalk,
};


//
// 向量的线性过渡, 
// ctrl_vec3 计算结果保存到的向量
// speed 到达目标需要的时间单位秒
//
function Vec3Transition(ctrl_vec3, speed) {
  if (!speed) speed = 1;
  return {
    line : line,
  };

  function line(used, end_vec3) {
    var f = speed / used;
    ctrl_vec3[0] = ctrl_vec3[0] + (end_vec3[0] - ctrl_vec3[0])/f;
    ctrl_vec3[1] = ctrl_vec3[1] + (end_vec3[1] - ctrl_vec3[1])/f;
    ctrl_vec3[2] = ctrl_vec3[2] + (end_vec3[2] - ctrl_vec3[2])/f;
  }
}


//
// 3D 转换
//
function Transformation() {
  // 对象的变换矩阵
  const objTr = matrix.mat4.create(1);
  // 对象的中心在模型上的偏移
  const center = matrix.vec3.create();
  // 对象的中心在时间上的偏移, 每次都生成新的数组造成内存浪费
  const _where = matrix.vec3.create();
  // 变换矩阵初始状态
  var initTr  = ONE;

  const sp = {
    translate : translate,
    scale     : scale,
    reset     : reset,
    rotate    : rotate,
    rotateX   : rotateX,
    rotateY   : rotateY,
    rotateZ   : rotateZ,
    objTr     : objTr,
    setCenter : setCenter,
    where     : where,
  };
  return sp;
  
  //
  // 平移
  //
  function translate(vec3pos) {
    matrix.mat4.translate(objTr, objTr, vec3pos);
  }

  //
  // 不使用矢量化，按给定vec3中的尺寸缩放,
  // vec3s: [x, y, z]
  //
  function scale(vec3s) {
    matrix.mat4.scale(objTr, objTr, vec3s); // 缩放
  }

  //
  // 在 x 轴上旋转 rad 弧度.
  //
  function rotateX(rad) {
    matrix.mat4.rotateX(objTr, objTr, rad);
  }

  //
  // 在 y 轴上旋转 rad 弧度.
  //
  function rotateY(rad) {
    matrix.mat4.rotateY(objTr, objTr, rad);
  }

  //
  // 在 z 轴上旋转 rad 弧度.
  //
  function rotateZ(rad) {
    matrix.mat4.rotateY(objTr, objTr, rad);
  }

  //
  // 围绕给定轴 axis 的向量旋转 rad 弧度,
  // axis: [x, y, z]
  //
  function rotate(rad, axis) {
    matrix.mat4.retate(objTr, objTr, rad, axis);
  }

  //
  // 设置对象中心在模型中的偏移
  //
  function setCenter(x, y, z) {
    matrix.vec3.set(center, x, y, z);
  }

  //
  // 返回对象在世界中的位置
  //
  function where() {
    matrix.vec3.transformMat4(_where, center, objTr);
    return _where;
  }

  //
  // 还原到 ma4 状态并记忆该状态;
  // 如果 mat4 为空, 则使用最近一次记忆的状态, 默认状态为单位矩阵
  //
  function reset(mat4) {
    if (mat4) {
      matrix.mat4.copy(objTr, mat4);
      initTr = mat4;
    } else {
      matrix.mat4.copy(objTr, initTr);
    }
  }
}


//
// 创建摄像机, 可绘制; 要求着色器变量 `mat4 camera`
// operator{op:Function(used, camera)}
//
function createCamera(program, operator) {
  if (!operator) operator = DEF_OP;
  const cameraUi = program.getUniform('camera');

  const cameraPos   = matrix.vec3.fromValues(0.0, 1.0,  3.0);
  const cameraFront = matrix.vec3.fromValues(0.0, 0.0, -1.0);
  const cameraUp    = matrix.vec3.fromValues(0.0, 1.0,  0.0);

  const cm = Transformation(); 
  cm.draw         = draw;
  cm.setPos       = setPos;
  cm.lookAt       = lookAt;
  cm.lookAtSprite = lookAtSprite;
  cm.lookWhere    = lookWhere;
  cm.pos          = pos;
  return cm;

  function setPos(x, y, z) {
    matrix.vec3.set(cameraPos, x, y, z);
  }

  function lookAt(x, y, z) {
    matrix.vec3.set(cameraFront, x, y, z);
  }

  function lookAtSprite(sp) {
    matrix.vec3.copy(cameraFront, sp.where());
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

  function draw(used, time) {
    operator.op(used, time, cm);
    matrix.mat4.lookAt(cm.objTr, cameraPos, cameraFront, cameraUp);
    cameraUi.active();
    cameraUi.setMatrix4fv(1, gl.GL_FALSE, cm.objTr);
  }
}


//
// 创建精灵对象, 多个精灵可以引用同一个可绘制对象(模型)
// 精灵对象本身可绘制, 
// 要求着色器变量: `mat4 model`,
// operator{op:Function(used, sprite)} 操作者对象, op 在每一帧上被调用
//
function createSprite(drawObj, operator) {
  const modelUi = drawObj.program.getUniform('model');
  if (!operator) operator = DEF_OP;

  const sp = Transformation(); 
  sp.draw  = draw;
  return sp;

  //
  // 由框架调用, 用户不要直接调用
  //
  function draw(used) {
    operator.op(used, sp);
    modelUi.active();
    modelUi.setMatrix4fv(1, gl.GL_FALSE, sp.objTr);
    drawObj.draw(used);
  }
}


//
// 用于显示帧率
//
function createShowRate() {
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
        'Real:', c,
        'Min:', min,
        'Max:', max);
    }
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
  const SKE_SIZE = 10;
  const SKE_ELE_LEN = 3;
  const BIND_LEN = 2;

  var txt = fs.read_txt(filename);
  var config = yaml.load(txt);
  var bind = new Float32Array(vertexCount * BIND_LEN);
  var ske = new Float32Array(SKE_SIZE*SKE_ELE_LEN);

  bind.fill(-1);
  _bind(config.bindex, config.vbind, bind, 1);
  _bind(config.bindex, config.vbind4, bind, 4);

  // console.log(JSON.stringify(config, 0, 2));
  for (var i=0; i<config.bone.length; ++i) {
    var j = i*SKE_ELE_LEN;
    matrix.vec4.copy(ske.subarray(j, j+SKE_ELE_LEN), config.bone[i]);
  }

  return {
    bind : bind,
    ske  : ske,
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
//
function createAnimation(drawObj, skeObj) {
  const thiz = {
    pose : pose,
    draw : draw,
  };
  return thiz;

  //
  // 切换动作
  //
  function pose(name) {
  }

  //
  // 下一帧动画
  //
  function draw(used, time) {
  }
}


//
// 固定行走动画
// TODO: 参数都与模型和骨骼绑定, 不通用.
//
function FixedWalk(drawObj, skeObj) {
  var rand = Math.random();
  var loc = drawObj.program.getLocationIndex('skBind');
  drawObj.bindBuffer(skeObj.bind);
  drawObj.setAttr({ index: loc, vsize: 2, 
      stride: 2 * gl.sizeof$float });

  var skeleton = drawObj.program.getUniform('skeleton');
  skeleton.setUniform3fv(skeObj.ske);

  var rightFoot = skeObj.ske.subarray(0, 3);
  var leftFoot  = skeObj.ske.subarray(3, 6);
  var rightHead = skeObj.ske.subarray(9, 12);
  var leftHead  = skeObj.ske.subarray(12, 15);
  var mawe1     = skeObj.ske.subarray(15, 18);
  var eye       = skeObj.ske.subarray(18, 21);

  const r = {
    pose : pose,
    draw : draw,
  };
  return r;

  //
  // 切换动作
  //
  function pose(name) {
  }

  //
  // 下一帧动画
  //
  function draw(used, time) {
    // matrix.vec4.rotateX(rightFoot, rightFoot, used);
    time += rand;
    var speed = 8;
    var pos = time*speed;
    var ssin = Math.sin(pos);
    var scos = Math.cos(pos);

    rightFoot[1] = ssin/8;
    rightFoot[2] = -scos/50;

    leftFoot[1] = -ssin/8;
    leftFoot[2] = scos/50;

    rightHead[1] = -ssin/20;
    leftHead[1]  = ssin/20;

    pos = time*(speed-2)
    // mawe1[1] = Math.sin(pos)/50;
    mawe1[2] = scos/70;
    eye[2] = (parseInt(time*10)%40 < 2)? -0.09: 0;

    skeleton.setUniform3fv(skeObj.ske);
  }
}