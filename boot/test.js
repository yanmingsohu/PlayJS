export default {}

console.log(new Error('test').stack);

var a1 = new Int8Array(8);
var a2 = new Uint32Array(3);
a1[0] = 1000;
a2[0] = 1000;
console.log(a1, a2);

var fd = fs.open("eXeScope.ini", 'r');
var buf = new Uint8Array(100);
fs.read(fd, buf, 0, buf.length, 0);
console.log(buf);
fs.close(fd);
var str = Unicode.toUtf8String(buf);
console.log(str);

console.log('hello world 你好!!');