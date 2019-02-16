export default {}

import draw   from '../boot/draw.js'
import matrix from '../boot/matrix.js'
import model  from '../boot/model.js'

var window = draw.createWindow();
window.setClearColor([0.2, 0.3, 0.3, 1]);

//
// 编译/链接着色器
//
var shaderProgram = draw.createProgram();
shaderProgram.readVertexShader("demo/ply.vert");
shaderProgram.readFragShader("demo/basic.flag");
shaderProgram.link();
shaderProgram.setProjection(45, 1024/768, 0.01, 100);


var d1 = draw.createBasicDrawObject(shaderProgram);

// 动画: https://www.khronos.org/opengl/wiki/Skeletal_Animation
// 资产导入: https://github.com/assimp/assimp
console.log("start ply model..");

// ** parse PLY file use javascript.
// import ply from '../boot/model-ply.js'
// var opt = { pos_normalized: 1, color_normalized: 1 };
// var model0 = ply.read('art/monu1.ply', opt);
// d1.addVerticesElements(model0.vertex.data, model0.face.data);

var frameCount = 0;
var transform = shaderProgram.getUniform('transform');
var tmat = matrix.mat4.create(1);
matrix.mat4.rotateX(tmat, tmat, 4.5);
tmat[13] -= 0.5;
tmat[14] = -1.13;
transform.active();
transform.setMatrix4fv(1, gl.GL_FALSE, tmat);

var modelTrans = shaderProgram.getUniform('model');
var viewTrans = shaderProgram.getUniform('view');
modelTrans.setMatrix4fv(1, gl.GL_FALSE, matrix.mat4.create(1));
viewTrans.setMatrix4fv(1, gl.GL_FALSE, matrix.mat4.create(1));


var plyfile = 'art/chr_rain.ply'; //'art/monu1.ply';
var m3d = model.load(plyfile);
d1.addVerticesElements(m3d.vertex, m3d.index);

d1.setAttr({ index: 0, vsize: 3, stride: 6*gl.sizeof$float });
d1.setAttr({ index: 1, vsize: 3, stride: 6*gl.sizeof$float,
             offset: 3*gl.sizeof$float });
// d1.loadTexImage("./art/container.jpg");
// window.add(d1);


var cubePositions = [
    matrix.vec3.fromValues( 0.0,  0.0,  0.0), 
    matrix.vec3.fromValues( 2.0,  5.0, -15.0), 
    matrix.vec3.fromValues(-1.5, -2.2, -2.5),  
    matrix.vec3.fromValues(-3.8, -2.0, -12.3),  
    matrix.vec3.fromValues( 2.4, -0.4, -3.5),  
    matrix.vec3.fromValues(-1.7,  3.0, -7.5),  
    matrix.vec3.fromValues( 1.3, -2.0, -2.5),  
    matrix.vec3.fromValues( 1.5,  2.0, -2.5), 
    matrix.vec3.fromValues( 1.5,  0.2, -1.5), 
    matrix.vec3.fromValues(-1.3,  1.0, -1.5),
];

for (var i=0; i<1000; ++i) {
(function() {
    var ref = {};
    var x = i%10;
    var y = i/10 %10;
    var z = i/100 %10;
    var pos = matrix.vec3.fromValues(x, y, z);

    var m = matrix.mat4.create(1);
    matrix.mat4.translate(m, m, pos);//平移
    var scale = Math.random()* 9;
    matrix.mat4.scale(m, m, [scale, scale, scale]); // 缩放

    ref.draw = function() {
        var mm = matrix.mat4.create(1);
        matrix.mat4.translate(mm, m, [
            Math.random()*0.01, Math.random()*0.01, Math.random()*0.01]);//平移
        modelTrans.setMatrix4fv(1, gl.GL_FALSE, mm);
        d1.draw();
    };

    window.add(ref);
})();
}


window.onKey(gl.GLFW_KEY_ESCAPE, gl.GLFW_PRESS, 0, function() {
    window.shouldClose();
});

window.onKey(gl.GLFW_KEY_S, gl.GLFW_PRESS, 0, function() {
    tmat[14] -= 0.01;
});
window.onKey(gl.GLFW_KEY_W, gl.GLFW_PRESS, 0, function() {
    tmat[14] += 0.01;
});
window.onKey(gl.GLFW_KEY_D, gl.GLFW_PRESS, 0, function() {
    matrix.mat4.rotateZ(tmat, tmat, -0.01);
});
window.onKey(gl.GLFW_KEY_A, gl.GLFW_PRESS, 0, function() {
    matrix.mat4.rotateZ(tmat, tmat, 0.01);
});
window.onKey(gl.GLFW_KEY_J, gl.GLFW_PRESS, 0, function() {
    tmat[12] -= 0.01;
});
window.onKey(gl.GLFW_KEY_L, gl.GLFW_PRESS, 0, function() {
    tmat[12] += 0.01;
});
window.onKey(gl.GLFW_KEY_K, gl.GLFW_PRESS, 0, function() {
    tmat[13] -= 0.01;
});
window.onKey(gl.GLFW_KEY_I, gl.GLFW_PRESS, 0, function() {
    tmat[13] += 0.01;
});

var lastTime = gl.glfwGetTime();
while (window.nextFrame()) {
  var timeValue = gl.glfwGetTime();
  var used = timeValue - lastTime;
  lastTime = timeValue;

  ++frameCount;
  transform.active();
  transform.setMatrix4fv(1, gl.GL_FALSE, tmat);

  console.line('total:', frameCount, 
        ', average rate:', parseInt(frameCount/timeValue), 
        ', frame rate:', parseInt(1/used));
}

console.log("Exit Frame Loop .......");
window.destroy();

