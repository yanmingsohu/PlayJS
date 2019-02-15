//
// 解析3d模型文件
//
export default {
  load : load,
  ply  : ply,
};


function load(file) {
  if (file.endsWith('.ply')) {
    return ply(file);
  }

  throw new Error("Unsupport format:"+ file);
}


function ply(file) {
  var ret = model_parser.ply(file);
  return {
    vertex : new Float32Array(ret.vertex),
    index  : new Uint32Array(ret.index),
  };
}