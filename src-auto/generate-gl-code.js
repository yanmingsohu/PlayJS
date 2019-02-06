//
// 该脚本用 nodejs 运行, 用来读取 c++ 头文件, 并自动生成 js 绑定代码.
// 如果 cpp 源代码改变, 新增的函数实现会和自动生成的函数有冲突,
// 此时应运行该脚本, 刷新自动生成的函数(解决冲突).
//
// !!!生成的代码必须人工审核!!!
//
const fs   = require('fs');
const path = require('path');
const EE   = "\r\n\r\n";
const TAB  = "    ";

var outfile;
//
// 函数原型定义, 用于生成 cpp 头文件
//
var cppFunctionPrototype = [];
var cppFunctionCall = [];

//
// 需要解析的 GL 头文件
//
const heades = [
  path.join(__dirname, '../deps/glfw/include/GLFW/glfw3.h'),
  'C:/Program Files (x86)/Windows Kits/8.1/Include/um/gl/GL.h'
];

//
// 已经实现的代码
//
const sourceCC = [
  path.join(__dirname, '../src/glfw.cpp'),
  path.join(__dirname, '../src/glcore.cpp'),
];


function pushFunc(retType, fname, argDef, argCall) {
  var pp = retType+ ' '+ fname + argDef;
  cppFunctionCall.push(fname + argCall);
  cppFunctionPrototype.push(pp);
  return pp;
}


//
// 生成产量绑定到 js 对象的代码
//
(function() {
  outfile = __dirname +'/const.cc';
  newfile('Bind CONST to js');
  var pp = pushFunc('void', 'auto_gl_Const', 
                    "(VM* vm, LocalVal& _const)", '(vm, _const)');
  append(EE+ pp +' {');
  heades.forEach(parseConst);
  append('}');
})();


//
// 生成 GL 函数到 js 函数的包装器默认实现, 跳过已经实现的函数.
//
(function() {
  var skipFunc = {};

  sourceCC.forEach(function(f) {
    checkFunc(f, skipFunc);
  });

  heades.forEach(function(f) {
    outfile = __dirname +'/'+ path.basename(f) +".cc";
    parseFunction(f, skipFunc);
  });
})();


//
// 生成头文件
//
(function() {
  outfile = __dirname +'/glauto.h';
  newfile("Auto Generate Hander");
  
  //
  // 生成一个宏定义, 在代码中引入
  //
  var txt = [EE, '#define INCLUDE_AUTO_GL_CODE(vm, gl, _const) \\\r\n'];
  cppFunctionCall.forEach(function(name) {
    txt.push('    ', name, '; \\\r\n');
  });
  txt.push(EE);

  cppFunctionPrototype.forEach(function(code) {
    txt.push(code, ';\r\n');
  });

  append(txt.join(''));
})();


function checkFunc(file, skipFunc) {
  var f = fs.readFileSync(file, 'utf8');
  var lines = f.split('\n');
  const find = 'GL_BIND(';
  const end = ');';

  lines.forEach(function(line) {
    line = line.trim();
    var a = line.indexOf(find);
    var b = line.indexOf(end, a);
    if (a >=0 && b > a) {
      var fn = line.substring(a+find.length, b);
      console.log('跳过生成', fn, '(...)');
      skipFunc[fn] = 1;
    }
  });
}


function parseFunction(file, skipFunc) {
  newfile(file);

  var f = fs.readFileSync(file, 'utf8');
  var lines = f.split('\n');
  var funcBind = [];

  lines.forEach(function(line) {
    var items = line.split(' ');
    items = clearsp(items);

    if (items[0] == 'WINGDIAPI') {
      _gl(items);
    } else if (items[0] == 'GLFWAPI') {
      __glfw(items);
    }
  });

  var bname = path.basename(file).replace('.', '_');
  var pp = pushFunc('void', 'auto_bind_'+ bname, 
                    '(VM*vm, LocalVal& gl)', '(vm, gl)');
  append(EE+ pp +' {');

  funcBind.forEach(function(b) {
    if (skipFunc[b]) {
      append(TAB +'// GL_BIND('+ b +');');
    } else {
      append(TAB +'GL_BIND('+ b +');');
    }
  });
  append('}');


  function _gl(items) {
    var st = 0;
    for (var i=0; i<items.length; ++i) {
      if (items[i] == 'APIENTRY') {
        st = i+1;
      }
    }
    var arg = items.slice(st+1);

    arg = clearArg(arg);
    var funcname = items[st];
    var def = f_tpl(funcname, arg.join(', '), arg.length);
    // console.log(funcname);
    if (!funcname.startsWith('gl')) {
      console.log("BAD", items);
    }
    append(def);
    funcBind.push(funcname);
  }


  function __glfw(items) {
    while (items[1] == 'const' || items[1] == 'unsigned') {
      items.splice(1, 1);
    }
    var tmp = items[2].split('(');
    var funcname = tmp[0];
    var arg = tmp.slice(1).concat(items.slice(3));

    arg = clearArg(arg);
    var def = f_tpl(funcname, arg.join(', '), arg.length);
    // console.log(funcname);
    if (!funcname.startsWith('glfw')) {
      console.log("BAD", items);
    }
    append(def);
    funcBind.push(funcname);
  }


  function clearArg(arg) {
    var r = [];
    arg.join(' ').split(',').forEach(function(a) {
      var i = a.split(' ');
      if (i.length > 1) {
        var v = i[i.length-1]; 
        while (v[0] == '(') v = v.substr(1);
        while (v[0] == '*') v = v.substr(1);
        while (v[v.length-1] == ';') v = v.substr(0, v.length-1);
        while (v[v.length-1] == ')') v = v.substr(0, v.length-1);
        r.push(v);
      }
    });
    return r;
  }


  function f_tpl(funcName, argsStr, argCount) {
    var st = skipFunc[funcName] ? '// ': '';
    return '\r\n\r\n'+
`${st}GL_FUNC(${funcName}, args, ac) {
${st}${TAB}GL_CHK_ARG(${argCount}, ${funcName}(${argsStr}));
${st}${TAB}pushException("Not implemented function ${funcName}(...)");
${st}${TAB}return 0;
${st}}`;
  }
}


function parseConst(file) {
  append(TAB +'// '+ file);

  var f = fs.readFileSync(file, 'utf8');
  var lines = f.split('\n');
  var varmap = {};

  lines.forEach(function(line) {
    if (! line.startsWith('#define')) return;
    var items = line.split(' ');
    items = clearsp(items);
    var name = items[1];
    var val  = parseInt(items[2]);

    varmap[name] = val;
    var nc = isNaN(val);

    if (nc && !isNaN(varmap[items[2]])) {
      nc = false;
      console.log("交叉引用", name, '->', items[2]);
    }
    writeConst(name, nc);
  });
}


function writeConst(name, needComment) {
  var code = (needComment ?TAB+'// ' :TAB) +'GL_INT_ENUM('+ name +');';
  append(code);
  // console.log(code);
}


function clearsp(arr) {
  var ret = [];
  arr.forEach(function(v) {
    if (v !=='' && v !== null && v !== undefined) {
      if (v.trim) {
        ret.push(v.trim());
      } else {
        ret.push(v);
      }
    }
  });
  return ret;
}


function writeHeander() {
  var ntime = new Date();
  var txt = [
    '//\r\n',
    '// ', ntime.toLocaleDateString(), 
    ' ', ntime.toLocaleTimeString(), '\r\n',
    '// create from ', __filename, ' \r\n', 
    '//'
  ];
  append(txt.join(''));
}


function newfile(txt) {
  if (fs.existsSync(outfile)) {
    fs.truncateSync(outfile, 0);
  }
  writeHeander();
  append('// '+ txt);
  append('#include "../src/gl.h"');
}


function append(t) {
  fs.appendFileSync(outfile, t +'\r\n');
}