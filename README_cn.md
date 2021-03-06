# PlayJS 

[English](https://github.com/yanmingsohu/PlayJS)

![screen1](https://github.com/yanmingsohu/PlayJS/blob/master/screen/s1.jpg)
![screen2](https://github.com/yanmingsohu/PlayJS/blob/master/screen/s2.jpg)

基于 javascript 的多媒体引擎.

特征:

1. 支持多线程. 
2. 支持线程间消息传递. 
3. 文本使用 UTF-8 编码. 
4. 无复制的线程间数据共享. 
5. 底层函数和高级函数共存. 
6. 不安全的高性能. 


# Demo

* [简单三角形](https://github.com/yanmingsohu/PlayJS-release/blob/master/demo/draw.js)
* [读取模型并播放动画](https://github.com/yanmingsohu/PlayJS-release/blob/master/demo/camera.js)
* [从WAV文件播放声音](https://github.com/yanmingsohu/PlayJS-release/blob/master/demo/audio.js)


# 游戏

[生化危机2 重生](https://github.com/yanmingsohu/Biohazard2)


# 待实现 Pending

* [x] 控制台输出乱码
* [x] 启动新线程
* [ ] 线程数据共享(无复制)
  * [x] 在线程间传递消息
  * [ ] 在线程间共享缓冲区
  * [ ] 在线程间共享对象
  * [ ] js 对象映射到二进制缓冲区(线程间传递)
* [ ] 图形api
  * [x] 集成 3D 一个渲染器, 跨平台 (OpenGL/glfw/glew)
  * [ ] 集成一个视频解码器
  * [ ] 集成一个用户界面库
  * [ ] 骨骼动画
* [ ] 音频api
  * [x] 播放音乐和音效
  * [ ] 3D声场
* [x] 控制api
* [ ] AI 逻辑api
* [ ] 物理引擎api
* [ ] 文档
* [ ] 基础api
  * [ ] 定时器
  * [ ] 启动参数
  * [x] YAML 解析
  * [ ] 当前文件路径 __dirname/__filename
  * [ ] 压缩/解压缩
  

# 外部资源

* [骨骼动画](https://www.khronos.org/opengl/wiki/Skeletal_Animation)
* [资产导入](https://github.com/assimp/assimp)
* [着色器指南](https://github.com/wshxbqq/GLSL-Card)
* [跨平台图形引擎](https://github.com/bkaradzic/bgfx)