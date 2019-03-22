# 音频模块

对 SoLoud 引擎的封装, 部分 api 的详细说明可以[参考这里](http://sol.gfxile.net/soloud/basics.html).

脚本空间中创建的对象允许使用句柄在多个线程间引用, 
这些对象需要显示释放, 否则会一直在内存中驻留.

`boot/Sound.js` 对底层音频模块进行了封装方便使用.


# API

时间单位通常是秒, 浮点数; 音量 1 表示原始音量 0.5 表示一半音量, 2 表示倍音量;


## soloudHandle audio.createSoloud(flag, backend, samplerate, buffersize, channels)

在脚本空间创建 SoLoud 引擎对象, 并返回句柄引用.


## audio.releaseSoloud(soloudHandle)

释放脚本空间中的 SoLoud 对象.


## audio.stop(soloudHandle, sourceHandle)

停止播放声音


## wavHandle audio.createWavSource();

创建 wav 音源.


## audio.releaseWavSource(wavHandle);

释放 wav 音源, 如果声音正在播放时执行该方法, 引擎可能崩溃.


## sourceHandle audio.play(soloudHandle, wavHandle [, volume, pan, paused, bus])

播放音源, 返回音源句柄.


## audio.load(wavHandle, filename)

把文件加载到wav音源中, 错误的句柄类型会导致程序崩溃.


## audio.loadMem(wavHandle, TypedArray)

内存中的 RIFF 格式缓冲区, 注意缓冲区必须和 wav 对象有共同的生存期, 否则引擎可能崩溃.


## audio.loadRawWave(wavHandle, TypedArray, type, samplerate, channel)

使用未压缩的二进制缓冲区创建音频.


## audio.getLength(wavHandle)

返回音源播放长度, 单位是秒, 浮点类型, 错误的句柄类型会导致程序崩溃.


## audio.setPause(soloudHandle, sourceHandle, pause)

设置暂停状态.


## audio.setLooping(soloudHandle, sourceHandle, bool)

设置现场声音的循环行为.


## audio.setLoopPoint(soloudHandle, sourceHandle, time)

设置循环开始点(秒,浮点).


## audio.setVolume(soloudHandle, sourceHandle, vol)

设置音量, vol=1 原始音量


## audio.setPan(soloudHandle, sourceHandle, pan)

设置平衡, pan -1 左, 0 中间, 1 右.
SoLoud 计算左/右音量以保持恒定音量; 要直接设置音量，请使用setPanAbsolute.


## audio.setPanAbsolute(soloudHandle, sourceHandle, left, right)

这些功能可用于直接设置左/右音量.


## audio.setProtectVoice(soloudHandle, sourceHandle, protect)

通常情况下，如果您尝试播放的声音多于声音上限，SoLoud将消除最古老的播放声音以腾出空间。这很可能是你的背景音乐。这可以通过保护声音来解决。

如果所有声音都受到保护，则结果将不确定。


## audio.setInaudibleBehavior(soloudHandle, sourceHandle, aMustTick, aKill)

设置现场声音的听不见行为。默认情况下，如果声音听不到，它会暂停，并在声音再次响起时恢复。使用此功能，您可以告诉SoLoud要么在声音听不见时要么杀死声音，要么即使它听不见也要保持声音滴答声。


## audio.setRelativePlaySpeed(soloudHandle, sourceHandle, speed)

将值设置为0将导致未定义的行为，可能是崩溃。

更改样本的相对播放速度。这会改变有效采样率，同时仅保留基本采样率。

请注意，以更高的采样率播放声音将需要SoLoud从声源请求更多样本，这将需要更多内存和更多处理能力。以较慢的采样率播放更便宜。


## audio.fadeVolume(soloudHandle, sourceHandle, vol, time)

在指定时间内平滑地更改频道的音量。


## audio.fadePan(soloudHandle, sourceHandle, pan, time)

在指定时间内平滑地更改通道的平衡设置。

## audio.fadeRelativePlaySpeed(soloudHandle, sourceHandle, to, time)

在指定时间内平滑地改变频道的相对播放速度。


## audio.fadeGlobalVolume(soloudHandle, vol, time)

在指定时间内平滑更改全局音量.