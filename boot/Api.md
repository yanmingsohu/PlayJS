# Api 

# 全局对象

可在脚本中直接引用.

脚本也可以通过 import/export 来加载其他脚本, 请参考 ES6 模块.


# fs

文件系统, 一下操作失败后都会抛出异常.

## fd open(path, mode)

打开文件, 返回句柄, 失败会抛出异常, path 相对于程序启动目录.
mode可以是 'w' 写文件, 'r' 读文件等.

## void close(fd)

关闭文件句柄.

## int fpos(fd)

使用文件句柄获得文件当前指针位置.

## int read(fd, buffer, b_offset, b_length[, f_pos])

从文件句柄 fd 引用的文件中读取数据写出到缓冲区 buffer, 
文件开始偏移为 f_pos, 该参数可以省略.
从缓冲区 b_offset 开始最多写 b_length 个字节.

## int write(fd, buffer, b_offset, b_length[, f_pos])

将缓冲区 buffer 中从 b_offset 开始 b_length 个字节的数据;
写入文件句柄 fd 引用的文件中, 文件从 f_pos 开始写, f_pos 参数可以省略.


# console

调试控制台, 以下方法都可以输出日志到命令行(如果有)
输出格式:  
19:08:53 #10C INF| PlayJS Game Engine.
-------- ---- ---- -------------------
^        ^    ^    ^
|        |    |    |
|        |    |    消息字符串
|        |    日志级别
|        线程 ID
日志输出的时间

## void debug(...)

消息级别: DBG

## void log(...)

消息级别: INF

## void info(...)

消息级别: INF

## void error(...)

消息级别: ERR

## void warn(...)

消息级别: WAN

## void fatal(...)

消息级别: FTL

## void show() *TODO: 未完成

调用后立即显示控制台窗口, 如果控制台已经显示则什么都不做.

## void hide() *TODO: 未完成

调用后立即隐藏控制台窗口, 如果控制太已经隐藏则什么都不做.


# thread

线程库.

## int id()

返回当前线程的 id

## int run(script_file_path)

在新的线程中启动脚本, 没有错误该方法会立即返回线程 id.

## bool running(threadid)

如果线程 id 引用的线程还在运行中返回 true.

## void sleep(ms)

当前线程休眠 ms 毫秒.


# Unicode

字符串编码

## String toUtf8String(TypedArray)

认为二进制缓冲区中的数据是 UTF-8 格式字符串, 并构建字符串对象.
一般与 Uint8Array 配合从 fs 中读取文本文件.

## String toGbkString(TypedArray)

认为二进制缓冲区中的数据是 GBK 格式字符串, 并构建字符串对象.
一般与 Uint8Array 配合从 fs 中读取文本文件.


# events

消息总线, 在多个线程间通信.

PlayJS 并不是按照 EventLoop 来设计的, 如果使用消息, 
每个线程在必须要时需要自行处理 EventLoop 循环.

除了特殊说明的消息, 所有的消息都在多个线程间路由.

`error` 是个特殊的消息, 该消息只在自身线程中传递.
线程应该注册 `error` 消息的处理回调, 否则该消息将被 getMessage() 直接抛出.

`exit` 是个特殊消息, 发出该消息说明程序进入退出进程, 所有线程
都应该妥善处理数据, 任何线程也可以发出该消息.

通常的用法:

```js
events.on('error', function(err) {
	console.error(err.stack);
});
events.emit("opendoor", door);
//
// 必须有消息循环
//
while (events.getMessage()) {
	events.dispatchMessage();
}
```

## on(messagename, callback) *未实现

在消息总线上注册消息监听器, 一旦事件被触发, callback 会被回调, 
callback 第一个参数是消息附带的数据对象; 在 callback 中抛出的
异常将被发送到消息总线的 `error` 事件上

## emit(messagename, object) *未实现

发送一个消息, 这条消息将被所有感兴趣的监听器(所有线程)抓取, 方法返回后,
消息不是立即发出, 而是在 dispatchMessage 中被处理的.

## bool getMessage() *未实现

当前线程必须有一个消息循环来调用该方法, 否则 `on` 注册的监听器
无法获取任何消息. 如果 `exit` 消息被发出, 该方法返回 false.

## void dispatchMessage() *未实现

当前线程必须有一个消息循环来调用该法, 否则当前线程 `emit` 创建
的消息都不会发布.

