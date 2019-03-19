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
  constructor(core) {
    this._wav = audio.createWavSource();
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
  // 解析缓冲区中的波形数据
  //
  fromBuffer(buf) {
    audio.loadMem(this._wav, buf);
    // 防止内存被释放, 核心会一直引用这段 js 缓冲区对象.
    this._bind(buf);
  }

  rawBuffer(buf, rate, channel) {
    let type;
    if (buf.constructor === Uint8Array) {
      type = audio.RAW_TYPE_8BIT;
    } 
    else if (buf.constructor == Int16Array) {
      type = audio.RAW_TYPE_16BIT;
    }
    else if (buf.constructor == Float32Array) {
      type = audio.RAW_TYPE_32FLOAT;
    } 
    else {
      throw new Error("Unsupport "+ buf.constructor);
    }
    audio.loadRawWave(this._wav, buf, type, rate, channel);
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
}


export default {
  Core,
  Wav,
};