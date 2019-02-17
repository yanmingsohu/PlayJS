const cache = {};


export default {
  load : load,
};


//
// 加载 nodejs 模块, 返回导出对象.
//
function load(scriptfile) {
  if (cache[scriptfile]) {
    return cache[scriptfile];
  }

  const module = { exports : {} };

  function define(_, factory) {
    var ext = factory(module.exports);
    if (ext) {
      module.exports = ext;
    }
  }
  define.amd = 1;

  var code = getCode(scriptfile);
  try {
    eval(code);
    return cache[scriptfile] = module.exports;
  } catch(e) {
    console.error("Load node script", scriptfile, "faild.");
    throw e;
  }
}



function getCode(fname) {
  var fd = fs.open(fname, 'rb');
  var buf = new Uint8Array(fs.fileSize(fname));
  var rlen = fs.read(fd, buf, 0, buf.length, 0);
  fs.close(fd);
  return Unicode.toUtf8String(buf, rlen);
}