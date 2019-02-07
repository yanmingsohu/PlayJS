export default {}

var version = gl.glfwGetVersion();
console.log('GLFW version:');
console.log('\t', JSON.stringify(version));
console.log('\t',gl.glfwGetVersionString());

var moni = gl.glfwGetPrimaryMonitor();
var mode = gl.glfwGetVideoMode(moni);
console.log("MODE:", JSON.stringify(mode));

// 窗口
var window = gl.glfwCreateWindow(1028, 768, "Test from JS");
// 全屏
// var window = gl.glfwCreateWindow(
//     mode.width, mode.height, "Full", moni, 0);
gl.glfwMakeContextCurrent(window);

var { GLFW_KEY_ESCAPE, GLFW_PRESS, GL_TRUE, GL_COLOR_BUFFER_BIT,
      GL_ARRAY_BUFFER, GL_STATIC_DRAW } = gl.const;
var a = 1.0;


var vertices = new Float32Array([
  -0.5, -0.5, 0.0,
   0.5, -0.5, 0.0,
   0.0,  0.5, 0.0,
]);
var VBO = gl.glGenBuffers(1);
gl.glBindBuffer(GL_ARRAY_BUFFER, VBO);  
gl.glBufferData(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);


while (!gl.glfwWindowShouldClose(window)) {
  if (gl.glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    gl.glfwSetWindowShouldClose(window, GL_TRUE);
  }

  gl.glClearColor(a, a, a, 1.0);
  gl.glClear(GL_COLOR_BUFFER_BIT);

  a += 0.1;
  if (a>=1) {
    a = 0.1;
  }

  gl.glfwSwapBuffers(window);
  gl.glfwPollEvents();
}

gl.glfwDestroyWindow(window);