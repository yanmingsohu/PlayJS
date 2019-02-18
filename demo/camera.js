export default {}

import draw   from '../boot/draw.js'
import node   from '../boot/node.js'
import model  from '../boot/model.js'
import game   from '../boot/game.js'

const matrix = node.load('boot/gl-matrix.js');
const PI = Math.PI;

var window = draw.createWindow();
window.setClearColor([0.2, 0.3, 0.3, 1]);

//
// 编译/链接着色器
//
var shaderProgram = draw.createProgram();
shaderProgram.readVertexShader("boot/game.vert");
shaderProgram.readFragShader("boot/game.frag");
shaderProgram.link();
shaderProgram.setProjection(45, 1024/768, 0.01, 100);


var plyfile = 'art/chr_rain.ply';
var m3d = model.load(plyfile);
var d1 = draw.createBasicDrawObject(shaderProgram);
d1.setModelData(m3d);

shaderProgram.getUniform('colorCoefficient').setUniform1f(1/255);
shaderProgram.getUniform('sizeCoefficient').setUniform1f(0.1);

var sk = game.readSkeleton("demo/skeleton.yaml", m3d.vertex.length/3);
var anim = game.FixedWalk(d1, sk);
window.add(anim);

var lastModel = [];
for (var i=0; i<10; ++i) {
  // for (var j=0; j<100; ++j) {
    var m = matrix.mat4.create(1);
    matrix.mat4.rotateX(m, m, -90*PI/180);
    matrix.mat4.translate(m, m, [i*5, 0, 0]);
    var sp = game.createSprite(d1);
    sp.reset(m);
    window.add(sp);
    lastModel.push(sp);
  // }
}

window.add(game.createShowRate());


var camera = game.createCamera(shaderProgram, { op: surroundOP });
var cameraLookAt = game.Vec3Transition(camera.lookWhere());
var camMoveTo = game.Vec3Transition(camera.pos(), 4);
window.add(camera);

function surroundOP(used, time, cm) {
  // var radius = 10.0;
  var time = gl.glfwGetTime()+1300;
  // var x = Math.sin(time) * radius;
  // var z = Math.cos(time) * radius;
  var index = parseInt(time/3) % lastModel.length;
  var mod = lastModel[index];
  // cm.lookAtSprite(mod);
  var modwhere = mod.where();
  // 线性移动摄像头
  cameraLookAt.line(used, modwhere);
  camMoveTo.line(used, [modwhere[0]+0.5, 1, modwhere[2]+3]);
}


window.onKey(gl.GLFW_KEY_ESCAPE, gl.GLFW_PRESS, 0, function() {
    window.shouldClose();
});

// window.onKey(gl.GLFW_KEY_S, gl.GLFW_PRESS, 0, function() {
//     tmat[14] -= 0.01;
// });
// window.onKey(gl.GLFW_KEY_W, gl.GLFW_PRESS, 0, function() {
//     tmat[14] += 0.01;
// });
// window.onKey(gl.GLFW_KEY_D, gl.GLFW_PRESS, 0, function() {
//     matrix.mat4.rotateZ(tmat, tmat, -0.01);
// });
// window.onKey(gl.GLFW_KEY_A, gl.GLFW_PRESS, 0, function() {
//     matrix.mat4.rotateZ(tmat, tmat, 0.01);
// });
// window.onKey(gl.GLFW_KEY_L, gl.GLFW_PRESS, 0, function() {
//     tmat[12] -= 0.01;
// });
// window.onKey(gl.GLFW_KEY_J, gl.GLFW_PRESS, 0, function() {
//     tmat[12] += 0.01;
// });
// window.onKey(gl.GLFW_KEY_I, gl.GLFW_PRESS, 0, function() {
//     tmat[13] -= 0.01;
// });
// window.onKey(gl.GLFW_KEY_K, gl.GLFW_PRESS, 0, function() {
//     tmat[13] += 0.01;
// });

window.prepareDraw();
while (window.nextFrame()) {
}
window.destroy();
