const pp = require("./parameter-processing.js");
const config = require("./config.js");
const _IN_PARM  = 1;
const _OUT_PARM = 2;
const _RES_REF  = 3;

module.exports = {
  parse: parse,
  genCppCode : genCppCode,
};


function clearSp(line) {
  var ret = line.trim().split(' ');
  for (var i=0; i<ret.length; ++i) {
    if (ret[i] == '') ret.splice(i, 1);
  }
  return ret.join(' ');
}


function genCppCode(func, append, indentation, skipBody) {
  var returnCode = "return 0;";

  append(`GL_FUNC(${func.name}, args, ac) {`);
  indentation(function() {
    if (func.args.length > 0) {
      append(`GL_CHK_ARG(${func.args.length}, ${func.name}(${argsStr()}));`);
      var argOk = false;
      var cppCode = [];
      argmentsProcess(cppCode);

      if (cppCode.length == func.args.length) {
        if (genCallCppFuncCode(cppCode))
          return;
      } else {
        append(`pushException("Not implemented function ${func.name}(...)");`);
      }
    } else {
      append(funcRetType() +`${func.name}();`);
    }
    append(returnCode);
  });
  append('}');


  function argmentsProcess(cppCode) {
    func.args.forEach(function(arg, i) {
      var desc = arg.type.join('/');
      var processor = pp.param[desc];

      if (!processor) {
        skipBody || console.log("NO PARAM Process", '`'+ desc +'`');
        skipBody || console.log(JSON.stringify(func, 0, 2));
        return;
      }

      var localvar = '__gen_'+ arg.name;
      // CPP 本机函数参数从 1 开始, 0 是 this
      var arg_index = i+1;
      // CPP 变量名称, 映射到 js 参数.
      var arg_name = 'args['+ arg_index +']';
      var codedesc = processor(localvar, arg, arg_index, arg_name);

      if (codedesc == 'SKIP') {
        console.log("SKIP PARAM TYPE", func.name, desc);
        return;
      } 

      if (!codedesc) {
        skipBody || console.log("FAIL PARAM TYPE", desc);
        skipBody || console.log(JSON.stringify(func, 0, 2));
        return;
      }

      // 生成的局部变量名称
      codedesc.varname = localvar;
      // 变量的原始名称
      codedesc.srcname = arg.name;
      cppCode.push(codedesc);
    });
  }


  //
  // 如果返回 false 则需要生成默认返回值.
  //
  function genCallCppFuncCode(cppCode) {
    var call = [];
    var outparm = [];

    cppCode.forEach(function(c) {
      append(c.code);
      var vname;

      switch (c.type) {
        case _IN_PARM:
          vname = c.varname; 
          break;

        case _OUT_PARM:
          vname = '&'+ c.varname; 
          outparm.push(c);
          break;

        case _RES_REF:
          vname = c.varname +'.get()';
          break;

        default:
          throw new Error("不支持的类型 "+ c.code);
      }
      call.push(vname);
    });

    append(funcRetType() + `${func.name}(${call.join(', ')});` );
    if (outparm.length > 0) {
      genRetJsObject(outparm);
      return true;
    }
  }


  function funcRetType() {
    var is_void = false;
    for (var i=0; i<func.rettype.length; ++i) {
      if (config.voidType[ func.rettype[i] ]) {
        is_void = true;
        break;
      }
    }
    if (is_void) return '';
    var rvn = '__return_'+ func.name;
    returnCode = 'return wrapJs('+ rvn +');';
    return 'auto '+ rvn +' = ';
  }


  function genRetJsObject(outparm) {
    if (outparm.length > 1) {
      append(`auto __retjs = JVM->createObject();`);
      outparm.forEach(function(o) {
        append(`__retjs.put("${o.srcname}", wrapJs(${o.varname}));`);
      });
      append('return __retjs;');
    } else {
      append(`return wrapJs(${outparm[0].varname});`);
    }
  }


  function argsStr() {
    return func.args.map(function(v) {
      return v.name;
    }).join(', ');
  }
}


//
// 返回解析后的 cpp 函数信息, 否则返回 null,
// 依赖前置判断是否是函数声明
//
function parse(line) {
  var args = [];
  var name = null;
  var rettype = [];
  var state = 1;
  var st = 0;
  var currentArg = {type:[], name:null};

  line = clearSp(line);
  if (line[0] == '#') return;

  for (var i=0; i<line.length; ++i) {
    var c = line.charAt(i);
    switch (state) {
      case 1:
        if (c ==' ' || c=='\t') {
          var it = line.substring(st, i).trim();
          if (it.length > 0) {
            rettype.push(it);
          }
          st = i+1;
        }
        else if (c == '(') {
          var it = line.substring(st, i).trim();
          if (it.length > 0) {
            name = it;
          } else {
            name = rettype.pop();
          }
          st = i+1;
          state = 2;
        }
        break;
      
      case 2:
        if (c == ' ') {
          var it = line.substring(st, i).trim();
          if (it.length > 0) {
            currentArg.type.push(it);
          }
          st = i+1;
        }
        else if (c == ',' || c == ')') {
          var it = line.substring(st, i).trim();
          if (it.length > 0) {
            currentArg.name = it;
          } else {
            currentArg.name = currentArg.type.pop();
          }

          if (!currentArg.name || currentArg.type<1) 
            break;

          if (currentArg.name[0] == '*') {
            currentArg.name = currentArg.name.substr(1);
            currentArg.type.push('*');
          } else if (currentArg.name[0] == '&') {
            currentArg.name = currentArg.name.substr(1);
            currentArg.type.push('&');
          }

          args.push(currentArg);
          currentArg = {type:[], name:null};
          st = i+1;
          if (c == ')') break;
        }
        break;
    }
  }

  return name==null ? null : {
    name : name,
    args : args,
    rettype : rettype,
  };
}