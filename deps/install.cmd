@echo off
echo 安装依赖


echo https://github.com/Microsoft/ChakraCore/wiki/Building-ChakraCore

git clone https://github.com/Microsoft/ChakraCore.git
set VS_HOME=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC
set VS_HOME=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build
call "%VS_HOME%\vcvarsall.bat" x64
msbuild /m /p:Platform=x64 /p:Configuration=Release /p:RuntimeLib=static_library /p:ChakraICU=static ChakraCore\Build\Chakra.Core.sln