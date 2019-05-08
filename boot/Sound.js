class Core {
  constructor() {
    this._so = audio.createSoloud();
    this._bind = new Set();
  }

  //
  // 音源关联核心后才可以播放
  //
  bind(source) {
    this._bind.add(source);
  }

  unbind(source) {
    source.stop();
    this._bind.delete(source);
  }

  //
  // 必须明确的释放对象
  //
  free() {
    audio.releaseSoloud(this._so);
  }
}


class Wav {
  constructor(core, copyWav) {
    this._wav = copyWav || audio.createWavSource();
    this._core = core;
    this._so = core._so;
    this._data = null;
  }

  _bind(data) {
    if (!this._handle) {
      // 绑定后才能进行操作(播放等)
      this._handle = audio.play(this._so, this._wav, 1, 0, true);
      this._core.bind(this);
    } else {
      throw new Error("Can't bind again");
    }
    this._data = data;
  }

  //
  // 在读取数据前设置有效
  //
  setFilter(slotID, typeEnum) {
    audio.setFilter(this._wav, slotID, typeEnum);
  }

  //
  // 在读取数据之后设置有效
  //
  setFilterParam(slotID, paramEnum, value) {
    audio.setFilterParameter(this._so, this._handle, slotID, paramEnum, value);
  }

  //
  // 创建一个同样的音频流用于播放, 该方法代价较小.
  // 克隆对象无需释放资源, 当克隆主体被释放, 克隆体上的操作会崩溃.
  //
  clone() {
    const cloned = new Wav(this._core, this._wav);
    cloned._data = this._data;
    cloned._handle = audio.play(this._so, this._wav, 1, 0, true);
    cloned._copy_src_not_free = true;
    return cloned;
  }

  //
  // 解析缓冲区中的波形数据
  //
  fromBuffer(buf) {
    audio.loadMem(this._wav, buf);
    // 防止内存被释放, 核心会一直引用这段 js 缓冲区对象.
    this._bind(buf);
  }

  rawBuffer(buf, rate, channel, _type) {
    if (!_type) {
      if (buf.constructor === Uint8Array) {
        _type = audio.RAW_TYPE_8BIT;
      } 
      else if (buf.constructor == Int16Array) {
        _type = audio.RAW_TYPE_16BIT;
      }
      else if (buf.constructor == Float32Array) {
        _type = audio.RAW_TYPE_32FLOAT;
      } 
      else {
        throw new Error("Unsupport "+ buf.constructor);
      }
    }
    audio.loadRawWave(this._wav, buf, _type, rate, channel);
    this._bind(buf);
  }

  //
  // 秒为单位的浮点, 波形的播放时长, 
  //
  length() {
    return audio.getLength(this._wav);
  }

  //
  // 必须明确的释放对象
  //
  free() {
    if (this._copy_src_not_free) return;
    this._core.unbind(this);
    audio.releaseSource(this._wav);
    delete this._data;
  }

  stop() {
    audio.stop(this._so, this._handle);
  }

  pause() {
    audio.setPause(this._so, this._handle, true);
  }

  play() {
    audio.setPause(this._so, this._handle, false);
  }

  loop(bool) {
    audio.setLooping(this._so, this._handle, bool);
  }

  loopPoint(timeSec) {
    audio.setLoopPoint(this._so, this._handle, timeSec);
  }

  volume(v) {
    audio.setVolume(this._so, this._handle, v);
  }

  pan(p) {
    audio.setPan(this._so, this._handle, p);
  }

  panAbs(l, r) {
    audio.setPanAbsolute(this._so, this._handle, l, r);
  }

  protect(bool) {
    audio.setProtectVoice(this._so, this._handle, bool);
  }

  inaudibleBehavior(timeTick, kill) {
    audio.setInaudibleBehavior(this._so, this._handle, timeTick, kill);
  }

  speed(s) {
    audio.setRelativePlaySpeed(this._so, this._handle, s);
  }

  seek(s) {
    audio.seek(this._so, this._handle, s);
  }

  fadeVolume(v, time) {
    audio.fadeVolume(this._so, this._handle, v, time);
  }

  fadePan(p, time) {
    audio.fadePan(this._so, this._handle, p, time);
  }

  fadeRelativePlaySpeed(toSpeed, time) {
    audio.fadeRelativePlaySpeed(this._so, this._handle, toSpeed, time);
  }

  fadeGlobalVolume(vol, time) {
    audio.fadeGlobalVolume(this._so, vol, time);
  }
}


export default {
  Core,
  Wav,
};