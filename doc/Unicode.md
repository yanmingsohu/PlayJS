# Unicode

字符串编码, 可以在任意模块之间调用.


## String toUtf8String(TypedArray)

认为二进制缓冲区中的数据是 UTF-8 格式字符串, 并构建字符串对象.
一般与 Uint8Array 配合从 fs 中读取文本文件.

(该方法不负责编码转换)


## String toGbkString(TypedArray)

认为二进制缓冲区中的数据是 GBK 格式字符串, 并构建字符串对象.
一般与 Uint8Array 配合从 fs 中读取文本文件.

(该方法不负责编码转换)