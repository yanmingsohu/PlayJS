//
// 使 gl-matrix.js 中的方法导出为模块
//
const exports = {};
const files = [
  'deps/gl-matrix/dist/gl-matrix.js',
  'boot/gl-matrix.js',
];

export default exports


function define(_, factory) {
  factory(exports);
}
define.amd = 1;


function getCode(fname) {
  var fd = fs.open(fname, 'rb');
  var buf = new Uint8Array(fs.fileSize(fname));
  var rlen = fs.read(fd, buf, 0, buf.length, 0);
  fs.close(fd);
  return Unicode.toUtf8String(buf, rlen);
}


function checkFile() {
  for (var i=files.length-1; i>=0; --i) {
    if (fs.exists(files[i])) {
      return files[i];
    }
  }
}


var fname = checkFile();
if (!fname) {
  throw new Error("cannot found gl-matrix.js");
}
var code = getCode(fname);
eval(code);


