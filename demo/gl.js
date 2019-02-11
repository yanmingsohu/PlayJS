export default {}

var version = gl.glfwGetVersion();
console.log('GLFW version:');
console.log('\t', JSON.stringify(version));
console.log('\t',gl.glfwGetVersionString());

var moni = gl.glfwGetPrimaryMonitor();
var mode = gl.glfwGetVideoMode(moni);
console.log("Screen MODE:", JSON.stringify(mode));

//
// 窗口
//
var window = gl.glfwCreateWindow(1028, 768, "Test from JS");
//
// 全屏
//
// var window = gl.glfwCreateWindow(
//     mode.width, mode.height, "Full", moni, 0);

gl.glfwMakeContextCurrent(window);
//
// 必须在 glfwMakeContextCurrent 之后调用
//
gl.glewInit();
gl.glViewport(0, 0, 1028, 768);
checkGLerr("init");

var { GLFW_KEY_ESCAPE, GLFW_PRESS, GL_TRUE, GL_COLOR_BUFFER_BIT,
      GL_ARRAY_BUFFER, GL_STATIC_DRAW } = gl;
var a = [1.0, 1, 1];


var shaderSource = `
    #version 330 core
    layout (location = 0) in vec3 aPos;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }`;

var vertexShader = gl.glCreateShader(gl.GL_VERTEX_SHADER);
gl.glShaderSource(vertexShader, shaderSource);
gl.glCompileShader(vertexShader);
if (!gl.glGetShaderiv(vertexShader, gl.GL_COMPILE_STATUS)) {
    console.log(gl.glGetShaderInfoLog(vertexShader));
}
checkGLerr("vertex shader");

var fragmentShaderSource = `
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    } `

var fragmentShader = gl.glCreateShader(gl.GL_FRAGMENT_SHADER);
gl.glShaderSource(fragmentShader, fragmentShaderSource);
gl.glCompileShader(fragmentShader);
if (!gl.glGetShaderiv(fragmentShader, gl.GL_COMPILE_STATUS)) {
    console.log(gl.glGetShaderInfoLog(fragmentShader));
}
checkGLerr("fragmentShader");
var shaderProgram = gl.glCreateProgram();
gl.glAttachShader(shaderProgram, vertexShader);
gl.glAttachShader(shaderProgram, fragmentShader);
gl.glLinkProgram(shaderProgram);
if(! gl.glGetProgramiv(shaderProgram, gl.GL_LINK_STATUS)) {
    console.log(glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog));
}
checkGLerr('shaderProgram');

var vertices = new Float32Array([
    -0.5, -0.5, 0.0,
     0.5, -0.5, 0.0,
     0.0,  0.5, 0.0,
  ]);

var VAO = gl.glGenVertexArrays(1);
var VBO = gl.glGenBuffers(1);

gl.glBindVertexArray(VAO);
gl.glBindBuffer(GL_ARRAY_BUFFER, VBO);  
gl.glBufferData(GL_ARRAY_BUFFER, vertices, gl.GL_STATIC_DRAW);

var attrid = 0;
gl.glVertexAttribPointer(attrid, 3, gl.GL_FLOAT, 
        gl.GL_FALSE, 3 * gl.sizeof$float, 0);
gl.glEnableVertexAttribArray(attrid);
gl.glBindBuffer(GL_ARRAY_BUFFER, attrid); 
gl.glBindVertexArray(0);



var aindex = 0;
while (!gl.glfwWindowShouldClose(window)) {
  if (gl.glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    gl.glfwSetWindowShouldClose(window, GL_TRUE);
  }

  gl.glClearColor(a[0], a[1], a[2], 1.0);
  gl.glClear(GL_COLOR_BUFFER_BIT);

  gl.glUseProgram(shaderProgram);
  gl.glBindBuffer(GL_ARRAY_BUFFER, VBO);
  gl.glBindVertexArray(VAO);
  gl.glEnableVertexAttribArray(attrid);
  gl.glVertexAttribPointer(attrid, 3, gl.GL_FLOAT,
        gl.GL_FALSE, 3 * gl.sizeof$float, 0);
  gl.glDrawArrays(gl.GL_TRIANGLES, 0, 3);
  gl.glDisableVertexAttribArray(attrid);

  if ((a[aindex] +=0.01) > 1) {
      a[aindex] = 0;
      aindex += 1;
      if (aindex > 2) aindex = 0;
  }

  gl.glfwSwapBuffers(window);
  gl.glfwPollEvents();
}

gl.glfwDestroyWindow(window);


function checkGLerr(name) {
    var code = gl.glGetError();
    var msg;
    switch(code) {
        case gl.GL_INVALID_ENUM:
            msg = 'An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.';
            break;
        case gl.GL_INVALID_VALUE:
            msg = 'A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.';
            break;
        case gl.GL_INVALID_OPERATION:
            msg = 'The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.';
            break;
        case gl.GL_INVALID_FRAMEBUFFER_OPERATION:
            msg = 'The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.';
            break;
        case gl.GL_OUT_OF_MEMORY:
            msg = 'There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.';
            break;
        case gl.GL_STACK_UNDERFLOW:
            msg = 'An attempt has been made to perform an operation that would cause an internal stack to underflow.';
            break;
        case gl.GL_STACK_OVERFLOW:
            msg = 'An attempt has been made to perform an operation that would cause an internal stack to overflow.';
            break;
        case gl.GL_NO_ERROR:
            return;
        default:
            'unknow';
    }
    console.log("GL err:", name, code.toString(16), msg);
}