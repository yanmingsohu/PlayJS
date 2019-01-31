export default {}
import hex from '../boot/hex.js';

console.log(new Error('test').stack);
console.log('hello world 中文正常!!');

var a1 = new Int8Array(8);
var a2 = new Uint32Array(3);
a1[0] = 1000;
a2[0] = 1000;
console.log('Int8Array', a1)
console.log('Uint32Array', a2);

//
// 读取 utf8 文本
//
var filename = "README.md";
var fd = fs.open(filename, 'rb');
var buf = new Uint8Array(1000);
var rlen = fs.read(fd, buf, 0, buf.length);
fs.close(fd);
console.log(filename, "BIN", buf.slice(0, rlen+10));

var str = Unicode.toUtf8String(buf, rlen);
console.log(filename, "GBK TXT", str);

//
// 读取 gbk 文本
//
filename = "eXeScope.ini";
fd = fs.open(filename, 'rb');
rlen = fs.read(fd, buf, 0, buf.length);
fs.close(fd);
str = Unicode.toGbkString(buf, rlen);
console.log(filename, "TXT", str);

//
// 带偏移位的读写
//
filename = "./demo/test.txt";
var a3 = new Uint8Array(10);
for (var i=0; i<10; ++i) {
    a3[i] = 0x41 + i;
}
hex.printHex(a3, 10);
fd = fs.open(filename, "wb+");
fs.write(fd, a3, 0, 2, 10);

var a4 = new Uint8Array(20);
fs.read(fd, a4, 0, 20, 0);
hex.printHex(a4, 13);

fs.read(fd, a4, 0, 20, 10);
hex.printHex(a4, 13);
fs.close(fd);
console.log(filename, "size:", fs.fileSize(filename));

//
// 启动线程
//
thread.run('./demo/pi.js');