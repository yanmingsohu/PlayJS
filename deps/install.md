# 安装依赖


# windows

设置环境

```cmd
set VS_HOME=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC
set VS_HOME=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build
call "%VS_HOME%\vcvarsall.bat" x64
```


## JS 核心

* /p:RuntimeLib=static_library /p:ChakraICU=static 静态库编译不通过


```cmd
git clone https://github.com/Microsoft/ChakraCore.git
msbuild /m /p:Platform=x64 /p:Configuration=Release ChakraCore\Build\Chakra.Core.sln
copy ChakraCore\Build\VcBuild\bin\x64_release\ChakraCore.dll ..\
```


## 无锁队列 

```cmd
git clone https://github.com/cameron314/concurrentqueue
```


## 无锁线程对象 

echo safe_ptr 79 行去掉模板动态参数

```cmd
git clone https://github.com/AlexeyAB/object_threadsafe
```


## TODO: Javascript 对象序列化 

https://github.com/dcodeIO/ProtoBuf.js/


## OpenGL

* OpenGL  https://github.com/glfw/glfw(桌面)
* https://github.com/brackeen/glfm(移动)
* https://github.com/google/angle(全面)


### GLFW

```cmd
git clone https://github.com/glfw/glfw
cd glfw
cmake -G "Visual Studio 14 2015 Win64" CMakeLists.txt
msbuild /p:Configuration=Release GLFW.sln
cd ..
```


### GLEW

```cmd
git clone https://github.com/nigels-com/glew
```

单独下载源代码, 合并到 git.

```cmd
cd glew/build/vc15
msbuild /p:Platform=x64 /p:Configuration=Release glew.sln
```


### 图像加载

> 必要时导入 echo http://freeimage.sourceforge.net/download.html

https://github.com/nothings/stb

`git clone https://github.com/nothings/stb`



### JavaScript 矩阵运算

`git clone https://github.com/toji/gl-matrix`

进入目录构建单文件库 `npm install`,
复制文件到 `boot` 中



### JavaScript YAML 解析器

`git clone https://github.com/nodeca/js-yaml`



### 音频文件解析

`git clone https://github.com/ddiakopoulos/libnyquist`



### 声音引擎

`git clone https://github.com/jarikomppa/soloud`

* windows安装步骤
  * 下载 genie 到 build 目录 (https://github.com/bkaradzic/genie)
  * 执行 `genie --with-native-only --platform=x64 vs2017`
  
  
### 声音变调

`git clone  git clone https://gitlab.com/soundtouch/soundtouch.git`
  


### TODO: 虚拟文件系统

http://icculus.org/physfs/