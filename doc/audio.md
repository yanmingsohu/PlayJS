# 音频模块

对 SoLoud 引擎的封装, 部分 api 的详细说明可以[参考这里](http://sol.gfxile.net/soloud/basics.html).

脚本空间中创建的对象允许使用句柄在多个线程间引用, 
这些对象需要显示释放, 否则会一直在内存中驻留.


# API

## soloudHandle audio.createSoloud(flag, backend, samplerate, buffersize, channels)

在脚本空间创建 SoLoud 引擎对象, 并返回句柄引用.


## audio.releaseSoloud(soloudHandle)

释放脚本空间中的 SoLoud 对象.


## audio.stop(soloudHandle, sourceHandle)


## wavHandle audio.createWavSource();


## audio.releaseWavSource(wavHandle);


## sourceHandle audio.play(soloudHandle, wavHandle [, volume, pan, paused, bus])


## audio.load(wavHandle, filename)

把文件加载到wav音源中, 错误的句柄类型会导致程序崩溃.


## audio.getLength(wavHandle)

返回音源播放长度, 单位是秒, 浮点类型, 错误的句柄类型会导致程序崩溃.