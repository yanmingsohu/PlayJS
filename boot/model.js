//
// 解析3d模型文件
//
export default {
  load : load,
  ply  : ply,
};


function load(file) {
  console.debug("Load model", file);
  
  if (file.endsWith('.ply')) {
    return ply(file);
  }

  throw new Error("Unsupport file format: "+ file);
}


function ply(file) {
  var ret    = model_parser.ply(file);
  var vertex = new Float32Array(ret.vertex);
  var index  = new Uint32Array(ret.index); 

  return {
    vertex    : vertex,
    index     : index,
    setupDraw : setupDraw,
  };

  //
  // 模型必须实现该方法, 将缓冲区数据绑定到着色器.
  //
  function setupDraw(drawable, program) {
    var pos = program.getLocationIndex('aPos');
    var col = program.getLocationIndex('aColor');
    drawable.addVerticesElements(vertex, index);
    drawable.setAttr({ index: pos, vsize: 3, stride: 6*gl.sizeof$float });
    drawable.setAttr({ index: col, vsize: 3, stride: 6*gl.sizeof$float,
                       offset: 3*gl.sizeof$float });
  }
}