# events

消息总线, 在多个线程间通信, 可以在任意模块之间调用.  
PlayJS 并不是按照 EventLoop 来设计的, 如果使用消息, 
每个线程在必要时需要自行处理 EventLoop 循环.  
除了特殊说明的消息, 所有的消息都在多个线程间路由.

通常的用法:

```js
events.on('error', function(err) {
	console.error(err.stack);
});
events.emit("opendoor", door);
//
// 必须有消息循环
//
do {
  events.dispatchMessage();
  events.getMessage();
} while (events.waitMessage());
```


## 特殊消息定义

`error` 该消息只在自身线程中传递.
线程应该注册 `error` 消息的处理回调, 否则该消息将被 getMessage() 直接抛出.

`exit` 发出该消息说明程序进入退出进程, 所有线程
都应该妥善处理数据, 任何线程也可以发出该消息. *TODO未实现*


## void on(messagename, callback) 

在消息总线上注册消息监听器, 一旦事件被触发, callback 会被回调, 
callback 第一个参数是消息附带的数据对象; 在 callback 中抛出的
异常将被发送到消息总线的 `error` 事件上

`Function callback(value)`


## int off(messagename[, callback) 

删除监听器, 如果 callback 为空则删除当前线程上的所有 name 指定的
消息监听器, 否则只删除对应监听器的函数, 返回删除监听器函数的数量.

`Function callback(value)`


## void emit(messagename, value) 

发送一个消息, 这条消息将被所有感兴趣的监听器(所有线程)抓取, 方法返回后,
消息不是立即发出, 而是在 dispatchMessage 中被处理的.


## void getMessage()

当前线程必须有一个消息循环来调用该方法, 否则 `on` 注册的监听器
无法获取任何消息. 


## void dispatchMessage() 

当前线程必须有一个消息循环来调用该法, 否则当前线程 `emit` 创建
的消息都不会发布.


## bool waitMessage([millisecond])

休眠并等待新的消息, 或到达 millisecond 指定的毫秒后唤醒, 默认为 20 毫秒.
如果 `exit` 消息被发出, 该方法立即返回 false.
