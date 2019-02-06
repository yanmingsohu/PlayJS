@echo off
echo 安装依赖


set VS_HOME=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC
set VS_HOME=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build
call "%VS_HOME%\vcvarsall.bat" x64



echo JS 核心 https://github.com/Microsoft/ChakraCore/wiki/Building-ChakraCore
echo ===================================================================
git clone https://github.com/Microsoft/ChakraCore.git
rem /p:RuntimeLib=static_library /p:ChakraICU=static 静态库编译不通过
msbuild /m /p:Platform=x64 /p:Configuration=Release ChakraCore\Build\Chakra.Core.sln
copy ChakraCore\Build\VcBuild\bin\x64_release\ChakraCore.dll ..\



echo 无锁队列 https://github.com/cameron314/concurrentqueue
echo ===================================================================
git clone https://github.com/cameron314/concurrentqueue



echo 无锁线程对象 https://github.com/AlexeyAB/object_threadsafe
echo ===================================================================
git clone https://github.com/AlexeyAB/object_threadsafe
echo safe_ptr 79 行去掉模板动态参数



echo Javascript 对象序列化 https://github.com/dcodeIO/ProtoBuf.js/
echo ===================================================================



echo OpenGL  https://github.com/glfw/glfw(桌面)
echo https://github.com/brackeen/glfm(移动)
echo https://github.com/google/angle(全面)
echo ===================================================================
git clone https://github.com/glfw/glfw
cd glfw
cmake -G "Visual Studio 14 2015 Win64" CMakeLists.txt
msbuild /p:Configuration=Release GLFW.sln
cd ..

