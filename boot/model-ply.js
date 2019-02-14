export default {
  parse : parse,
  read  : read,
};


function readFile(fname) {
  var fd = fs.open(fname, 'rb');
  var buf = new Uint8Array(fs.fileSize(fname));
  var rlen = fs.read(fd, buf, 0, buf.length, 0);
  fs.close(fd);
  return Unicode.toUtf8String(buf, rlen);
}


function read(file, opt) {
  var txt = readFile(file);
  return parse(txt, opt);
}


function parse(txt, opt) {
  if (!opt) opt = {};
  var pos_nor = opt.pos_normalized || 1;
  var clr_nor = opt.color_normalized || 1;
  var len = txt.length;
  var ch, ls = 0;
  var state = 0;
  var elements = [];
  var curr_element;
  var ei = 0;
  var ec = 0;
  var ret = {
    _meta : elements,
  };

  for (var i=0; i<len; ++i) {
    ch = txt.charAt(i);
    if (ch == '\n') {
      _state(ls, i, txt);
      ls = i+1;
    }
  }

  return ret;


  function save_curr_element() {
    var ele;
    if (curr_element.type == 'vertex') {
      ele = create_vertex(curr_element);
    }
    else if (curr_element.type == 'face') {
      ele = create_face(curr_element);
    }
    else {
      throw new Error("Unsupport type "+ curr_element.type);
    }
    
    ret[curr_element.type] = ele;
    elements.push(ele);
  }


  function create_vertex(cnf) {
    var vertex = new Float32Array(cnf.count * cnf.attr.length);
    var vi = 0;
    var attrmap = {};
    cnf.attr.forEach(function(n, i) {
      attrmap[n.name] = i;
    });

    return {
      data : vertex,
      push : push,
      count : cnf.count,
    };

    function push(arr) {
      // x, y, z, r, g, b
      vertex[vi++] = arr[ attrmap['x'] ]/pos_nor;
      vertex[vi++] = arr[ attrmap['y'] ]/pos_nor;
      vertex[vi++] = arr[ attrmap['z'] ]/pos_nor;
      vertex[vi++] = arr[ attrmap['red'] ]  /clr_nor;
      vertex[vi++] = arr[ attrmap['green'] ]/clr_nor;
      vertex[vi++] = arr[ attrmap['blue'] ] /clr_nor;
    }
  }


  function create_face(cnf) {
    // 每个面 2 个三角形, 每个三角形 3 个顶点
    var face = new Uint32Array(cnf.count * 2 * 3);
    var fi = 0;

    return {
      data : face,
      push : push,
      count : cnf.count,
    }

    function push(arr) {
      if (arr[0] == 4) {
        face[fi++] = arr[1];
        face[fi++] = arr[2];
        face[fi++] = arr[4];
        face[fi++] = arr[2];
        face[fi++] = arr[3];
        face[fi++] = arr[4];
      } else {
        throw new Error("Unsupport size "+ arr[0]);
      }
    }
  }

  
  function _state(begin, end, str) {
    const l = str.substring(begin, end).trim();

    if (state == 0) {
      if (l == 'ply') {
        state = 1;
        return;
      } else {
        throw new Error("not fly file");
      }
    }

    if (state == 1) {
      var arg = l.split(' ');

      switch (arg[0]) {
        case 'element':
          if (curr_element) {
            save_curr_element();
          }
          curr_element = { 
            type  : arg[1], 
            count : parseInt(arg[2]),
            attr  : [],
          };
          break;
        
        case 'property':
          curr_element.attr.push({
            type : arg[1],
            name : arg[2],
          });
          break;

        case 'end_header':
          if (curr_element) {
            save_curr_element();
          }
          if (elements.length < 1) {
            throw new Error("No more elements in ply");
          }
          state = 2;
          break;
      }
      return;
    }

    if (state == 2) {
      var arr = l.split(' ');
      elements[ei].push(arr);
      if (++ec >= elements[ei].count) {
        ec = 0;
        if (++ei >= elements.length) {
          state = 3;
        }
      }
      return;
    }

    if (state == 3) {
      throw new Error("file end.");
    }
  }
}
