export default {
  printHex,
  h,
  t10,
  printFloat,
};

// 每行头部固定长度
const LINE_PREFIX_LEN = 18;
const str = "1234567890-=_+\\|~`qwertyuiopasdfghjklzxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM<>?:{}[];',./";
const dict = {};
for (var i=0; i<str.length; ++i) {
    dict[str.charCodeAt(i)] = str[i];
}


function printHex(b, lineC, maxlength) {
    if (!lineC) lineC = 16;
    let len = maxlength ? Math.min(b.length, maxlength) : b.length;

    for (var i = 0; i < len;) {
        var a = Math.min(b.length - i, lineC);
        var s = b.slice(i, i + a);
        var line = [];

        for (var j = 0; j < a; ++j) {
            var ch = s[j].toString(16);
            if (s[j] < 0x10) ch = '0' + ch;
            line[j] = ch + ' ';
            line[16 + j] = dict[s[j]] || '.';
        }

        for (var j = a; j < lineC; ++j) {
            line[j] = '   ';
        }

        console.debug(line.join(''));
        i += a;
    }
}


//
// b - FloatArray
// length - 最多打印元素数量, 默认 100
// lc - 每行最多打印数量, 不设置则尽可能打满行 
//
function printFloat(b, length, lc) {
  const line = [];
  let sl = 1;
  let max = Number.MIN_VALUE, min = Number.MAX_VALUE;

  if (!length) length = 100;
  length = Math.min(length, b.length);
  console.debug("--- Float Array", b.length, '=>', length);

  for (let i=0; i<length; ++i) {
    let s = ' '+ b[i];
    min = Math.min(min, b[i]);
    max = Math.max(max, b[i]);

    if (s.length > sl) {
      sl = s.length;
    }
    line.push(s);
    if (line.length > 200) {
      _print();
    }
  }

  _print();
  console.debug("--- END Max:", max, ", Min:", min);

  function _print() {
    const enter = lc || Math.floor((80-LINE_PREFIX_LEN) / sl)-1;
    const tmp = [];

    for (let i=0; i<line.length; ++i) {
      let s = line[i];
      for (let n=s.length; n<sl; ++n) tmp.push(' ');
      tmp.push(s);
      if (i % enter == enter-1) {
        console.debug(tmp.join(''));
        tmp.length = 0;
      }
    }
    if (tmp.length > 0) {
      console.debug(tmp.join(''));
    }
    line.length = 0;
  }
}


function h(i) {
  return i +' [0x'+ i.toString(16) +']';
}


function t10(buf) {
    var s = [];
    var len = Math.min(buf.length, 30);
    var sum = 0;
    for (var i=0; i<len; ++i) {
        s.push(buf[i]);
        sum += buf[i];
    }
    s.push('['+sum+']');
    return s.join(' ');
}