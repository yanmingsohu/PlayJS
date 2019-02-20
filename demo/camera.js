export default {}

import Draw   from '../boot/draw.js'
import Node   from '../boot/node.js'
import Game   from '../boot/game.js'
import Res    from '../boot/resource.js'

const matrix = Node.load('boot/gl-matrix.js');
const PI = Math.PI;

var window = Draw.createWindow();
window.setClearColor([0.2, 0.3, 0.3, 1]);
window.center();
window.add(Draw.showRate());

//
// 编译/链接着色器
//
var shaderProgram = Draw.createProgram();
shaderProgram.readVertexShader("demo/camera.vert");
shaderProgram.readFragShader("demo/camera.frag");
shaderProgram.link();
shaderProgram.setProjection(45, 4/3, 0.01, 100);

var res_ctx = Res.context(shaderProgram);


var lastModel = [];
for (var i=0; i<10; ++i) {
  for (var j=0; j<10; ++j) {
    var m = matrix.mat4.create(1);
    matrix.mat4.rotateX(m, m, -90*PI/180);
    matrix.mat4.translate(m, m, [j*5, i*5, 0]);
    
    var sp = res_ctx.load('art/chr_rain.sprite.yaml');
    sp.reset(m);
    
    window.add(sp);
    lastModel.push(sp);
  }
}

var camera = Game.createCamera(shaderProgram, { draw: surroundOP });
var cameraLookAt = Game.Vec3Transition(camera.lookWhere());
var camMoveTo = Game.Vec3Transition(camera.pos(), 4);
window.add(camera);


// 镜头切换时间
var switchTime = 3;
function surroundOP(used, time, cm) {
  // var radius = 10.0;
  var time = gl.glfwGetTime();
  // var x = Math.sin(time) * radius;
  // var z = Math.cos(time) * radius;
  var index = parseInt(time/switchTime) % lastModel.length;
  var mod = lastModel[index];
  // cm.lookAtSprite(mod);
  var modwhere = mod.where();
  // 线性移动摄像头
  modwhere[1] += 0.6;
  cameraLookAt.line(used, modwhere);
  camMoveTo.line(used, [modwhere[0]+0.5, 1, modwhere[2]+3]);
}


window.onKey(gl.GLFW_KEY_ESCAPE, gl.GLFW_PRESS, 0, function() {
    window.shouldClose();
});

window.prepareDraw();
while (window.nextFrame()) {
}
res_ctx.free();
window.destroy();
