const _IN_PARM  = 1;
const _OUT_PARM = 2;
const _RES_REF  = 3;

module.exports = {
  //
  // {参数描述符: 参数处理器}
  // 参数处理器 = function(varName, argConfig, index, argName)
  // 返回 : {
  //    type: 0, // 类型 0:无效, 1:输入, 2:输出, 等..
  //    code: '',  // 生成参数的处理代码
  // }
  //
  param: {
    'int'           : int_in,
    'int*'          : primitive_ref('int', 0),
    'float'         : float_in,
    'float*'        : primitive_ref('float', 0),
    'double'        : double_in,
    'double*'       : primitive_ref('double', 0),
    'const/char**'  : const_string_ref,
    'const/char*'   : string_in,

    'GLenum'        : convert_int('GLenum'),
    'GLboolean'     : convert_int('GLboolean'),
    'GLbitfield'    : convert_int('GLbitfield'),
    'GLbyte'        : convert_int('GLbyte'),
    'GLshort'       : convert_int('GLshort'),
    'GLint'         : convert_int('GLint'),
    'GLsizei'       : convert_int('GLsizei'),
    'GLubyte'       : convert_int('GLubyte'),
    'GLushort'      : convert_int('GLushort'),
    'GLuint'        : convert_int('GLuint'),
    'GLfloat'       : convert_double('GLfloat'),
    'GLclampf'      : convert_double('GLclampf'),
    'GLdouble'      : convert_double('GLdouble'),
    'GLclampd'      : convert_double('GLclampd'),

    'GLFWmonitor*'  : shared_resource_in('GLFWmonitor'),
    'GLFWwindow*'   : shared_resource_in('GLFWwindow'),
    'GLFWcursor*'   : shared_resource_in('GLFWcursor'),
    'GLFWgamepadstate*'     : shared_resource_in('GLFWgamepadstate'),
    'const/GLFWgammaramp*'  : shared_resource_in('GLFWgammaramp'),
    'const/GLFWimage*'      : shared_resource_in('GLFWimage'),
  },

  //
  // 特定函数返回值处理器
  // {函数名: 返回值处理器}
  //
  returnData: {
  },
};


function convert_int(srcType) {
  return function(vname, arg, index, an) {
    return {
      type: _IN_PARM,
      code: `${srcType} ${vname} = (${srcType}) intValue(${an});`,
    };
  };
}


function convert_double(srcType) {
  return function(vname, arg, index, an) {
    return {
      type: _IN_PARM,
      code: `${srcType} ${vname} = (${srcType}) doubleValue(${an});`,
    };
  };
}


function skip() {
  return function() {
    return 'SKIP';
  }
}


function int_in(vname, arg, index, an) {
  return {
    type: _IN_PARM,
    code: `int ${vname} = intValue(${an});`,
  };
}


function float_in(v, a, i, n) {
  return {
    type: _IN_PARM,
    code: `float ${v} = floatValue(${n});`,
  };
}


function double_in(v, a, i, n) {
  return {
    type: _IN_PARM,
    code: `double ${v} = doubleValue(${n});`,
  };
}


function primitive_ref(type, val) {
  return function (v, a, i, n) {
    return {
      type: _OUT_PARM,
      code: `${type} ${v} = ${val};`,
    };
  }
}


function const_string_ref(vn, arg, i) {
  return {
    type: _OUT_PARM,
    code: `const char *${vn} = 0;`,
  };
}


function string_in(v, a, i, n) {
  return {
    type: _IN_PARM,
    code: `std::string __${v} = toString(${n});
           const char* ${v} = __${v}.c_str();`,
  }
}


function shared_resource_in(type) {
  return function monitor_ref(v, a, i, an) {
    return {
      type: _RES_REF,
      code: `JS_HANDLE(${v}, ${an}, ${type});`,
    };
  }
}