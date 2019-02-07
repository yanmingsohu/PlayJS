//
// 该脚本用 nodejs 运行, 用来读取 c++ 头文件, 并自动生成 js 绑定代码.
// 如果 cpp 源代码改变, 新增的函数实现会和自动生成的函数有冲突,
// 此时应运行该脚本, 刷新自动生成的函数(解决冲突).
//
// !!!生成的代码必须人工审核!!!
//
const fs   = require('fs');
const path = require('path');
const cppf = require('./cpp-function.js');
const config = require('./config.js');
const EE   = "\r\n\r\n";
const TAB  = "    ";

var __tab_count = 0;
var __comment = 0;

var outfile;
//
// 函数原型定义, 用于生成 cpp 头文件
//
var cppFunctionPrototype = [];
var cppFunctionCall = [];

const heades = config.heades;
const sourceCC = config.sourceCC;


function pushFunc(retType, fname, argDef, argCall) {
  var pp = retType+ ' '+ fname + argDef;
  cppFunctionCall.push(fname + argCall);
  cppFunctionPrototype.push(pp);
  return pp;
}


//
// 生成常量绑定到 js 对象的代码
//
(function() {
  outfile = __dirname +'/const.cc';
  newfile('Bind CONST to js');
  var pp = pushFunc('void', 'auto_gl_Const', 
                    "(VM* vm, LocalVal& _const)", '(vm, _const)');
  append(EE+ pp +' {');
  heades.forEach(generateConstCppFile);
  append('}');
})();


//
// 生成 GL 函数到 js 函数的包装器默认实现, 跳过已经实现的函数.
//
(function() {
  var skipFunc = config.skipFunc || {};

  sourceCC.forEach(function(f) {
    checkFunc(f, skipFunc);
  });

  heades.forEach(function(config) {
    outfile = __dirname +'/'+ path.basename(config.file) +".cc";
    generateFunctionDefCppFile(config, skipFunc);
  });
})();


//
// 生成头文件
//
(function() {
  outfile = __dirname +'/glauto.h';
  newfile("Auto Generate Hander");
  append();
  
  //
  // 生成一个宏定义, 在代码中引入
  //
  append('#define INCLUDE_AUTO_GL_CODE(vm, gl, _const) \\');
  indentation(function() {
    cppFunctionCall.forEach(function(name, i) {
      var last = (i<cppFunctionCall.length-1) ? '; \\': '';
      append(name + last);
    });
  });

  append();
  cppFunctionPrototype.forEach(function(code) {
    append(code +';');
  });
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


function generateFunctionDefCppFile(config, skipFunc) {
  var file = config.file;
  newfile(file);

  var f = fs.readFileSync(file, 'utf8');
  var lines = f.split('\n');
  var funcBind = [];

  lines.forEach(function(line) {
    if (!config.parser(line)) return;
    
    var cppfunction = cppf.parse(line);

    if (cppfunction) {
      generate_cpp(cppfunction);
    } else {
      console.log("ERR", line);
    }
  });

  var bname = path.basename(file).replace('.', '_');
  var pp = pushFunc('void', 'auto_bind_'+ bname, 
                    '(VM*vm, LocalVal& gl)', '(vm, gl)');
  append(EE+ pp +' {');
  indentation(function() {
    funcBind.forEach(function(b) {
      __comment = skipFunc[b];
      append('GL_BIND('+ b +');');
    });
  });
  __comment = 0;
  append('}');


  function generate_cpp(func) {
    // console.log(JSON.stringify(func, 0, 2));
    append('');
    append('');

    __comment = skipFunc[func.name];
    cppf.genCppCode(func, append, indentation, __comment);
    __comment = 0;
    funcBind.push(func.name);
  }
}


function generateConstCppFile(config) {
  var file = config.file;
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


function writeConst(name, needComment) {
  indentation(function() {
    var code = 'GL_INT_ENUM('+ name +');';
    __comment = needComment;
    append(code);
    __comment = 0;
    // console.log(code);
  });
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
  comment(function() {
    [
      '',
      ntime.toLocaleDateString() +' '+ ntime.toLocaleTimeString(),
      'create from '+ __filename, 
      ''
    ].forEach(append);
  });
}


function newfile(txt) {
  if (fs.existsSync(outfile)) {
    fs.truncateSync(outfile, 0);
  }
  writeHeander();
  append('// '+ txt);
  append('//');
  append('#include "../src/gl.h"');
  append('#include "../src/gldeleter.h"');
}


function append(t) {
  (t||'').split('\n').forEach(function(t) {
    for (var i=0; i<__tab_count; ++i) {
      fs.appendFileSync(outfile, TAB);
    }
    if (__comment) fs.appendFileSync(outfile, '// ');
    fs.appendFileSync(outfile, t +'\r\n');
  });
}


function indentation(fn) {
  ++__tab_count;
  fn();
  --__tab_count;
}


function comment(fn) {
  __comment = 1;
  fn();
  __comment = 0;
}