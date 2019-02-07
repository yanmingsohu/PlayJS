module.exports = {
  gl: gl,
  glfw : glfw,
};


function gl(line) {
  return line.startsWith('GLAPI');
}


function glfw(line) {
  return line.startsWith('GLFWAPI');
}

