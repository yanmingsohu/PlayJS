//var fs = require("fs");
//var zlib = require('zlib');
export default {}


var files = {};
var fileCount = 0;

[ 
  'Shape000.PCK', 
  'Shape001.PCK',
  'Shape002.PCK',
  'Shape003.PCK',
  'Shape004.PCK',
  'Shape005.PCK',
  'Shape006.PCK',
  'ShapeFix.PCK',
  'Patch.PCK',
  'GameData.PCK',
].forEach(function(fname) {
  var pckfile = pck(fname);
  pckfile.parseFileList(function(file) {
    file[file.name] = file;
    ++fileCount;
  });
  console.log('load', fname, 'success');
});

console.log('check out', fileCount, 'files');


function pck(fname) {
  var fd = fs.openSync(fname, 'r');
  var fstat = fs.fstatSync(fd);
  var listOffset = fileListOffset(findHead());
  
  // console.log(fname, listOffset.toString(16));
  
  return {
    parseFileList: parseFileList,
    close: close,
  };


  function close() {
    fs.closeSync(fd);
  }


  function parseFileList(cb) {
    var buf = Buffer.alloc(fstat.size - listOffset);
    fs.readSync(fd, buf, 0, buf.length, listOffset);
    var ls = zlib.inflateRawSync(buf);
    
    var begin = nextSlice(ls, 0);
    while (begin >= 0) {
      var n = nextSlice(ls, begin+4);
      var fileBin = ls.slice(begin, n);
      try {
        // printHex(fileBin);
        cb(parseFile(fileBin));
      } catch(e) {
        printHex(fileBin);
        console.log(e.stack);
      }
      begin = n;
    }
  }


  function fileType(t) {
    switch (t) {
      case 0x14: return 'file';
      case 0x0a: return 'dir';
      default: return 'unknow';
    }
  }


  function parseFile(bin) {
    var file    = {};
    file.type   = fileType(bin[6]);
    file.name   = bin.slice(0x2E).toString('utf8');
    file.offset = bin.readUInt32LE(0x2A);
    file.length = bin.readUInt32LE(0x14);
    file.zip    = bin[10] & 0x08;
    if (file.type == 'file') {
      if (file.zip) {
        file.read = readInflate;
      } else {
        file.read = readClear;
      }
    }
    return file;
  }


  function readInflate() {
    var buf = Buffer.alloc(this.length);
    fs.readSync(fd, buf, 0, buf.length, this.offset);
    return zlib.inflateRawSync(buf);
  }


  function readClear() {
    var buf = Buffer.alloc(this.length);
    fs.readSync(fd, buf, 0, buf.length, this.offset);
    return buf;
  }


  function nextSlice(buf, begin) {
    for (var i=begin; i<buf.length; ++i) {
      if (buf[i+2]==1 && buf[i+3]==2 
         && ((buf[i]==0x50 && buf[i+1]==0x4b)
           ||(buf[i]==0x4f && buf[i+1]==0x44))) {
             return i;
           }
    }
    return -1;
  }


  function findHead() {
    var rlen = 0x2B4;
    var begin = fstat.size - rlen;
    var buf = Buffer.alloc(rlen);
    fs.readSync(fd, buf, 0, rlen, begin);
    
    for (var i=rlen-4; i>=0; --i) {
      if (buf[i+3] == 0x06 && buf[i+2] == 0x05
         && ( (buf[i] == 0x4f && buf[i+1] == 0x44)
            ||(buf[i] == 0x50 && buf[i+1] == 0x4b) )) {
        return buf.slice(i);
      }
    }
    throw new Error("not .pck file");
  }


  function fileListOffset(headbuf) {
    for (var i=4; i<headbuf.length; ++i) {
      headbuf[i] = (i*3 - 0x5B) ^ headbuf[i];
    }
    //console.log(headbuf);
    return headbuf.readUInt32LE(headbuf.length-6) + 6;
  }
}
