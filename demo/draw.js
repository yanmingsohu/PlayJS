export default {}
import draw from '../boot/draw.js'
import matrix from '../boot/matrix.js'

var window = draw.createWindow();
window.setClearColor([0.2, 0.3, 0.3, 1]);

//
// 顶点着色器
//
var shaderSource = `
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;
uniform mat4 transform;


void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
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
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
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
   // positions          // colors           // texture coords
   0.5,  0.5, 0.0,   1.0, 0.0, 0.0,   1.0, 1.0,   // top right
   0.5, -0.5, 0.0,   0.0, 1.0, 0.0,   1.0, 0.0,   // bottom right
  -0.5, -0.5, 0.0,   0.0, 0.0, 1.0,   0.0, 0.0,   // bottom left
  -0.5,  0.5, 0.0,   1.0, 1.0, 0.0,   0.0, 1.0,   // top left 
]);
var indices = new Uint32Array([  // note that we start from 0!
 0, 1, 3,   // first triangle
 1, 2, 3    // second triangle
]);
var d1 = draw.createBasicDrawObject(shaderProgram);
// d1.addVertices(vertices, 3);
d1.addVerticesElements(vertices, indices);
d1.setAttr({ index: 0, vsize: 3, stride: 8*gl.sizeof$float });
d1.setAttr({ index: 1, vsize: 3, stride: 8*gl.sizeof$float, 
             offset: 4*gl.sizeof$float });
d1.setAttr({ index: 2, vsize: 2, stride: 8*gl.sizeof$float, 
             offset: 6*gl.sizeof$float });
d1.loadTexImage("./art/container.jpg");
window.add(d1);


window.onKey(gl.GLFW_KEY_ESCAPE, gl.GLFW_PRESS, 0, function() {
  window.shouldClose();
});

var frameCount = 0;
var transform = shaderProgram.getUniform('transform');
var tmat = matrix.mat4.create(1);

while (window.nextFrame()) {
  var timeValue = gl.glfwGetTime();
  ++frameCount;
  transform.active();
  matrix.mat4.rotateY(tmat, tmat, 0.01);
  transform.setMatrix4fv(1, gl.GL_FALSE, tmat);
  console.line('total:', frameCount, 'rate:', parseInt(frameCount/timeValue));
}

console.log("Exit Frame Loop .......");
window.destroy();

