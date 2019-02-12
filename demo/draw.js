export default {}
import draw from '../boot/draw.js'

var window = draw.createWindow();
window.setClearColor([0.2, 0.3, 0.3, 1]);

//
// 顶点着色器
//
var shaderSource = `
#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1

uniform float off;
  
out vec3 ourColor; // output a color to the fragment shader

void main()
{
    gl_Position = vec4(aPos.x + off -2, -aPos.y, aPos.z, 1.0);
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
}`;

var vertexShader = draw.createShader(
    shaderSource, gl.GL_VERTEX_SHADER);

//
// 片段着色器
//
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


var vertices = new Float32Array([
  // positions         // colors
    0.5, -0.5, 0.0,  1.0, 0.0, 0.0,   // bottom right
   -0.5, -0.5, 0.0,  0.0, 1.0, 0.0,   // bottom left
    0.0,  0.5, 0.0,  0.0, 0.0, 1.0    // top 
]);
var d1 = draw.createBasicDrawObject(shaderProgram);
d1.addVertices(vertices, 3);
d1.setAttr({ index: 0, vsize: 3, stride: 6*gl.sizeof$float });
d1.setAttr({ index: 1, vsize: 3, stride: 6*gl.sizeof$float, 
             offset: 3*gl.sizeof$float });
window.add(d1);


// var vertices2 = new Float32Array([
//   0.5,  0.5, 0.0,  // top right
//   0.5, -0.5, 0.0,  // bottom right
//  -0.5, -0.5, 0.0,  // bottom left
//  -0.5,  0.5, 0.0   // top left 
// ]);
// var indices2 = new Uint32Array([  // note that we start from 0!
//  0, 1, 3,   // first triangle
//  1, 2, 3    // second triangle
// ]);
// d1.addVerticesElements(vertices2, indices2, vattr);


window.onKey(gl.GLFW_KEY_ESCAPE, gl.GLFW_PRESS, 0, function() {
  window.shouldClose();
});


while (window.nextFrame()) {
  var timeValue = gl.glfwGetTime();
  var greenValue = Math.sin(timeValue) / 2.0 + 0.5;
  shaderProgram.setUniform4f("ourColor", 0, greenValue, 0, 1);
  shaderProgram.setUniform1f('off', timeValue%4);
}


window.destroy();

