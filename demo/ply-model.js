export default {}

import draw   from '../boot/draw.js'
import matrix from '../boot/matrix.js'
import model  from '../boot/model.js'

var window = draw.createWindow();
window.setClearColor([0.2, 0.3, 0.3, 1]);

var shaderSource = `
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform mat4 transform;
uniform mat4 projection;

void main()
{
    gl_Position = projection * transform 
            * vec4(aPos[0]/100, aPos[1]/100, aPos[2]/100, 1.0);
    ourColor = vec3(aColor[0]/255, aColor[1]/255, aColor[2]/255);
}`;

var vertexShader = draw.createShader(
    shaderSource, gl.GL_VERTEX_SHADER);

var fragmentSource = `
#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
}`;

var fragmentShader = draw.createShader(
    fragmentSource, gl.GL_FRAGMENT_SHADER);

//
// 编译/链接着色器
//
var shaderProgram = draw.createProgram();
shaderProgram.attach(vertexShader);
shaderProgram.attach(fragmentShader);
shaderProgram.link();


var d1 = draw.createBasicDrawObject(shaderProgram);

console.log("start ply model..");
// ** parse PLY file use javascript.
// import ply from '../boot/model-ply.js'
// var opt = { pos_normalized: 1, color_normalized: 1 };
// var model0 = ply.read('art/monu1.ply', opt);
// d1.addVerticesElements(model0.vertex.data, model0.face.data);

var plyfile = 'art/chr_rain.ply'; //'art/monu1.ply';
var m3d = model.load(plyfile);
d1.addVerticesElements(m3d.vertex, m3d.index);

d1.setAttr({ index: 0, vsize: 3, stride: 6*gl.sizeof$float });
d1.setAttr({ index: 1, vsize: 3, stride: 6*gl.sizeof$float,
             offset: 3*gl.sizeof$float });
// d1.loadTexImage("./art/container.jpg");
window.add(d1);


var frameCount = 0;
var transform = shaderProgram.getUniform('transform');
var tmat = matrix.mat4.create(1);
matrix.mat4.rotateX(tmat, tmat, 4.5);
tmat[13] -= 0.5;
tmat[14] = -1.13;
transform.active();
transform.setMatrix4fv(1, gl.GL_FALSE, tmat);

var proj = matrix.mat4.create(1);
matrix.mat4.perspective(proj, 45, 1024/768, 0.1, 100.0);
var projectionVar = shaderProgram.getUniform('projection');
projectionVar.active();
projectionVar.setMatrix4fv(1, gl.GL_FALSE, proj);


window.onKey(gl.GLFW_KEY_ESCAPE, gl.GLFW_PRESS, 0, function() {
    window.shouldClose();
});

window.onKey(gl.GLFW_KEY_W, gl.GLFW_PRESS, 0, function() {
    tmat[14] -= 0.01;
});
window.onKey(gl.GLFW_KEY_S, gl.GLFW_PRESS, 0, function() {
    tmat[14] += 0.01;
});
window.onKey(gl.GLFW_KEY_D, gl.GLFW_PRESS, 0, function() {
    matrix.mat4.rotateZ(tmat, tmat, -0.01);
});
window.onKey(gl.GLFW_KEY_A, gl.GLFW_PRESS, 0, function() {
    matrix.mat4.rotateZ(tmat, tmat, 0.01);
});

while (window.nextFrame()) {
  var timeValue = gl.glfwGetTime();
  ++frameCount;
  transform.active();
  transform.setMatrix4fv(1, gl.GL_FALSE, tmat);
  console.line('total:', frameCount, 'rate:', parseInt(frameCount/timeValue));
}

console.log("Exit Frame Loop .......");
window.destroy();

