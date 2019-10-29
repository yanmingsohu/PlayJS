# PlayJS 

[中文版说明](https://github.com/yanmingsohu/PlayJS/blob/master/README_cn.md)

![screen1](https://github.com/yanmingsohu/PlayJS/blob/master/screen/s1.jpg)
![screen2](https://github.com/yanmingsohu/PlayJS/blob/master/screen/s2.jpg)

The Javascript Game/Multimedia engine.


# feature

1. Support for multi-threading.
2. Support inter-thread messaging.
3. The text uses UTF-8 encoding.
4. Data sharing between threads without replication.
5. The underlying function and the advanced function coexist.
6. Unsafe high performance.


# Demo

* [Triangle](https://github.com/yanmingsohu/PlayJS-release/blob/master/demo/draw.js)
* [Loading model](https://github.com/yanmingsohu/PlayJS-release/blob/master/demo/camera.js)
* [Play sound from wav](https://github.com/yanmingsohu/PlayJS-release/blob/master/demo/audio.js)


# Games

[Resident Evil 2 Rebirth](https://github.com/yanmingsohu/PlayJS-BIO2)


# TODO list:

* [x] Console output garbled
* [x] Start a new thread
* [ ] Thread data sharing (no replication)
  * [x] Passing messages between threads
  * [ ] Share buffers between threads
  * [ ] Sharing objects between threads
  * [ ] Js objects are mapped to binary buffers (passed between threads)
* [ ] Graphics API
  * [x] Integrated 3D a renderer, cross-platform (OpenGL/glfw/glew)
  * [ ] Integrate a video decoder
  * [ ] Integrate a user interface library
  * [ ] skeletal animation
* [ ] Audio API
  * [x] Play music and sound effects
  * [ ] 3D sound
* [x] control/input api
* [ ] AI logic lib
* [ ] physics engine
* [ ] document
* [ ] Basic api
  * [ ] timer
  * [ ] Startup parameters
  * [x] YAML parsing
  * [ ] current file path __dirname/__filename
  * [ ] compression/decompression
  

# Resource reference

* [Skeletal animation](https://www.khronos.org/opengl/wiki/Skeletal_Animation)
* [Asset introduction](https://github.com/assimp/assimp)
* [Shader guide](https://github.com/wshxbqq/GLSL-Card)
* [Cross-platform graphics engine](https://github.com/bkaradzic/bgfx)