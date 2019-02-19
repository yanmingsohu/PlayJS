export default {}

//
// 启动线程
//
console.log("启动 3 个线程");
thread.run('./demo/pi.js');
thread.run('./demo/pi.js');
thread.run('./demo/pi.js');