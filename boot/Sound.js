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
  }

  _bind() {
    if (!this._handle) {
      // 绑定后才能进行操作(播放等)
      this._handle = audio.play(this._so, this._wav, 1, 0, true);
      this._core.bind(this);
    }
  }

  //
  // 解析缓冲区中的波形数据
  //
  fromBuffer(buf) {
    audio.loadMem(this._wav, buf);
    // 防止内存被释放, 核心会一直引用这段 js 缓冲区对象.
    this.buf = buf; 
    this._bind();
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
    delete this.buf;
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