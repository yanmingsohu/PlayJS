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

while (!gl.glfwWindowShouldClose(window)) {
  gl.glfwSwapBuffers(window);
  gl.glfwPollEvents();
}

gl.glfwDestroyWindow(window);