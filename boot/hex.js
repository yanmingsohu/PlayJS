export default {
printHex : printHex,
h        : h,
t10      : t10,
};

    
var str = "1234567890-=_+\\|~`qwertyuiopasdfghjklzxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM<>?:{}[];',./";
var dict = {};
for (var i=0; i<str.length; ++i) {
    dict[str.charCodeAt(i)] = str[i];
}


function printHex(b, lineC) {
    if (!lineC) lineC = 16;
    for (var i = 0; i < b.length;) {
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

        console.log(line.join(''));
        i += a;
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