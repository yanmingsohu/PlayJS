module.exports = {
  gl: gl,
  glfw : glfw,
};


function gl(line) {
  return line.startsWith('WINGDIAPI');
}


function glfw(line) {
  return line.startsWith('GLFWAPI');
}

