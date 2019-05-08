#include "vm.h"
#include "js.h"
#include "shared.h"

#include <soloud.h>
#include <soloud_wav.h>
#include <soloud_filter.h>
#include <soloud_error.h>
#include "audio-plugin.h"

#include <soloud_bassboostfilter.h>
#include <soloud_biquadresonantfilter.h>
#include <soloud_dcremovalfilter.h>
#include <soloud_echofilter.h>
#include <soloud_fftfilter.h>
#include <soloud_flangerfilter.h>
#include <soloud_lofifilter.h>
#include <soloud_robotizefilter.h>
#include <soloud_waveshaperfilter.h>


//
// 下载并编译依赖 soloud 在 `/deps` 目录中
//
#ifdef WIN32
#pragma comment(lib, "soloud_static_x64.lib")
#endif


//
// Soloud 常量定义转换为 js 常量定义
//
#define SL_DEF(_name) \
   JSS_ATTR(_name, sl::Soloud::_name)

//
// 枚举定义
//
#define SO_ENUM(_prefix, _namespace, _name) \
  JSS_ATTR(_prefix##_##_name, _namespace##::##_name)


enum SOL_FILTER_TYPE {
  BiquadResonantFilter = 1,
  EchoFilter,
  LofiFilter,
  FlangerFilter,
  DCRemovalFilter,
  FFTFilter,
  BassboostFilter,
  WaveShaperFilter,
  SoundPitchFilter,
  RobotizeFilter,
};


namespace sl = SoLoud;


template<> struct SharedResourceDeleter<sl::Soloud> {
  virtual void operator()(sl::Soloud* s) {
    s->deinit();
    delete s;
  }
};


template<> struct SharedResourceDeleter<sl::AudioSource> {
  virtual void operator()(sl::AudioSource* w) {
    w->stop();
    delete w;
  }
};


static char* so_error(sl::result aErrorCode) {
  switch (aErrorCode) {
    case sl::SO_NO_ERROR: return "No error";
    case sl::INVALID_PARAMETER: return "Some parameter is invalid";
    case sl::FILE_NOT_FOUND: return "File not found";
    case sl::FILE_LOAD_FAILED: return "File found, but could not be loaded";
    case sl::DLL_NOT_FOUND: return "DLL not found, or wrong DLL";
    case sl::OUT_OF_MEMORY: return "Out of memory";
    case sl::NOT_IMPLEMENTED: return "Feature not implemented";
    /*case UNKNOWN_ERROR: return "Other error";*/
  }
  return "Other error";
}


static SoLoud::Filter* getFilterFactory(const int type) {
  switch (type) {
    case SOL_FILTER_TYPE::BiquadResonantFilter: {
      static SoLoud::BiquadResonantFilter _biq;
      return &_biq;
    }

    case SOL_FILTER_TYPE::BassboostFilter: {
      static SoLoud::BassboostFilter _bass;
      return &_bass;
    }

    case SOL_FILTER_TYPE::DCRemovalFilter: {
      static SoLoud::DCRemovalFilter _dc;
      return &_dc;
    }

    case SOL_FILTER_TYPE::EchoFilter: {
      static SoLoud::EchoFilter _echo;
      return &_echo;
    }

    case SOL_FILTER_TYPE::FFTFilter: {
      static SoLoud::FFTFilter _fft;
      return &_fft;
    }

    case SOL_FILTER_TYPE::FlangerFilter: {
      static SoLoud::FlangerFilter _fla;
      return &_fla;
    }

    case SOL_FILTER_TYPE::LofiFilter: {
      static SoLoud::LofiFilter _lofi;
      return &_lofi;
    }

    case SOL_FILTER_TYPE::SoundPitchFilter: {
      static SoundPitchFilterFact _pitch;
      return &_pitch;
    }

    case SOL_FILTER_TYPE::WaveShaperFilter: {
      static SoLoud::WaveShaperFilter _wave;
      return &_wave;
    }

    case SOL_FILTER_TYPE::RobotizeFilter: {
      static SoLoud::RobotizeFilter _rob;
      return &_rob;
    }

    default:
      return NULL;
  }
}


JSS_FUNC(createWavSource, args, ac) {
  return make_shared_js_handle<sl::AudioSource>(new sl::Wav());
}


JSS_FUNC(releaseSource, args, ac) {
  JSS_CHK_ARG(1, releaseWavSource(wavHandle));
  int handle = intValue(args[1], 0);
  release_shared_resource<sl::AudioSource>(handle);
  return 0;
}


JSS_FUNC(load, args, ac) {
  JSS_CHK_ARG(2, load(wavHandle, filename));
  JS_HANDLE(src, args[1], sl::AudioSource);
  sl::Wav* wav = (sl::Wav*) src.get();
  auto filename = stringValue(args[2]);
  auto ret = wav->load(filename.c_str());
  if (ret != sl::SO_NO_ERROR) {
    pushException(so_error(ret), ret);
  }
  return 0;
}


JSS_FUNC(loadMem, args, ac) {
  JSS_CHK_ARG(2, load(wavHandle, buffer));
  JS_HANDLE(src, args[1], sl::AudioSource);
  sl::Wav* wav = (sl::Wav*) src.get();
  LocalTypedArray buffer(args[2]);
  auto ret = wav->loadMem(buffer.bytes(), buffer.length(), false, false);
  if (ret != sl::SO_NO_ERROR) {
    pushException(so_error(ret), ret);
  }
  return 0;
}


JSS_FUNC(loadRawWave, args, ac) {
  JSS_CHK_ARG(5, loadRawWave(wavHandle, buffer, type, samplerate, channel));
  JS_HANDLE(src, args[1], sl::AudioSource);
  sl::Wav* wav = (sl::Wav*) src.get();
  LocalTypedArray buffer(args[2]);

  int type = intValue(args[3], 1);
  float sr = floatValue(args[4], 44100.0f);
  int ch = intValue(args[5], 1);
  sl::result ret = sl::SO_NO_ERROR;

  switch (type) {
    case 1:
      ret = wav->loadRawWave8(buffer.bytes(), buffer.length(), sr, ch);
      break;

    case 2:
      ret = wav->loadRawWave16((short*) buffer.bytes(), buffer.length()>>1, sr, ch);
      break;

    case 3:
      ret = wav->loadRawWave((float*) buffer.bytes(), buffer.length()>>2, sr, ch, false);
      break;

    default:
      pushException("invaild type value");
      break;
  }

  if (ret != sl::SO_NO_ERROR) {
    pushException(so_error(ret), ret);
  }
  return 0;
}


JSS_FUNC(getLength, args, ac) {
  JSS_CHK_ARG(1, getLength(wavHandle));
  JS_HANDLE(src, args[1], sl::AudioSource);
  sl::Wav* wav = (sl::Wav*) src.get();
  return wrapJs(wav->getLength());
}


JSS_FUNC(createSoloud, args, ac) {
  unsigned int flag = ac > 1
    ? intValue(args[1], sl::Soloud::CLIP_ROUNDOFF)
    : sl::Soloud::CLIP_ROUNDOFF;

  unsigned int backend = ac > 2
    ? intValue(args[2], sl::Soloud::AUTO) : sl::Soloud::AUTO;

  unsigned int samplerate = ac > 3
    ? intValue(args[3], sl::Soloud::AUTO) : sl::Soloud::AUTO;

  unsigned int buffersize = ac > 4
    ? intValue(args[4], sl::Soloud::AUTO) : sl::Soloud::AUTO;

  unsigned int channels = ac > 5 ? intValue(args[5], 2) : 2;

  sl::Soloud *core = new sl::Soloud();
  sl::result ret = core->init(flag, backend, samplerate, buffersize, channels);

  if (ret != sl::SO_NO_ERROR) {
    pushException(so_error(ret), ret);
    core->deinit();
    delete core;
    return 0;
  }
  return make_shared_js_handle(core);
}


JSS_FUNC(play, args, ac) {
  JSS_CHK_ARG(2, play(soloudHandle, wavHandle, volume, pan, paused, bus));
  JS_HANDLE(sol, args[1], sl::Soloud);
  JS_HANDLE(src, args[2], sl::AudioSource);
  float volume = ac > 3 ? floatValue(args[3], 1.0f) : 1.0f;
  float    pan = ac > 4 ? floatValue(args[4], 0) : 0;
  bool  paused = ac > 5 ? boolValue(args[5], false) : false;
  int      bus = ac > 6 ? intValue(args[6], 0) : 0;
  return wrapJs(sol->play(*src, volume, pan, paused, bus));
}


JSS_FUNC(stop, args, ac) {
  JSS_CHK_ARG(2, stop(soloudHandle, sourceHandle));
  JS_HANDLE(sol, args[1], sl::Soloud);
  unsigned int source = intValue(args[2]);
  sol->stop(source);
  return 0;
}


JSS_FUNC(setPause, args, ac) {
  JSS_CHK_ARG(3, setPause(soloudHandle, sourceHandle, pause));
  JS_HANDLE(sol, args[1], sl::Soloud);
  auto handle = intValue(args[2]);
  bool pause = boolValue(args[3]);
  sol->setPause(handle, pause);
  return 0;
}


JSS_FUNC(setLooping, args, ac) {
  JSS_CHK_ARG(3, setLooping(soloudHandle, sourceHandle, loop));
  JS_HANDLE(sol, args[1], sl::Soloud);
  auto handle = intValue(args[2]);
  bool loop = boolValue(args[3]);
  sol->setLooping(handle, loop);
  return 0;
}


JSS_FUNC(setLoopPoint, args, ac) {
  JSS_CHK_ARG(3, setLoopPoint(soloudHandle, sourceHandle, secondAbs));
  JS_HANDLE(sol, args[1], sl::Soloud);
  auto handle = intValue(args[2]);
  sl::time point = doubleValue(args[3]);
  sol->setLoopPoint(handle, point);
  return 0;
}


JSS_FUNC(setVolume, args, ac) {
  JSS_CHK_ARG(3, setVolume(soloudHandle, sourceHandle, vol));
  JS_HANDLE(sol, args[1], sl::Soloud);
  auto src = intValue(args[2]);
  float vol = floatValue(args[3]);
  sol->setVolume(src, vol);
  return 0;
}


JSS_FUNC(setPan, args, ac) {
  JSS_CHK_ARG(3, setPan(soloudHandle, sourceHandle, pan));
  JS_HANDLE(sol, args[1], sl::Soloud);
  auto src = intValue(args[2]);
  float pan = floatValue(args[3]);
  sol->setPan(src, pan);
  return 0;
}


JSS_FUNC(setPanAbsolute, args, ac) {
  JSS_CHK_ARG(4, setPanAbsolute(soloudHandle, sourceHandle, left, right));
  JS_HANDLE(sol, args[1], sl::Soloud);
  auto src = intValue(args[2]);
  float left = floatValue(args[3]);
  float right = floatValue(args[4]);
  sol->setPanAbsolute(src, left, right);
  return 0;
}


JSS_FUNC(setProtectVoice, args, ac) {
  JSS_CHK_ARG(3, setProtectVoice(soloudHandle, sourceHandle, protect));
  JS_HANDLE(sol, args[1], sl::Soloud);
  auto src = intValue(args[2]);
  float isprotect = boolValue(args[3]);
  sol->setProtectVoice(src, isprotect);
  return 0;
}


JSS_FUNC(setInaudibleBehavior, args, ac) {
  JSS_CHK_ARG(4, setInaudibleBehavior(soloudHandle, sourceHandle, aMustTick, aKill));
  JS_HANDLE(sol, args[1], sl::Soloud);
  auto src = intValue(args[2]);
  bool tick = boolValue(args[3]);
  bool kill = boolValue(args[4]);
  sol->setInaudibleBehavior(src, tick, kill);
  return 0;
}


JSS_FUNC(setRelativePlaySpeed, args, ac) {
  JSS_CHK_ARG(3, setInaudibleBehavior(soloudHandle, sourceHandle, speed));
  JS_HANDLE(sol, args[1], sl::Soloud);
  auto src = intValue(args[2]);
  float speed = floatValue(args[3]);
  sol->setRelativePlaySpeed(src, speed);
  return 0;
}


JSS_FUNC(seek, args, ac) {
  JSS_CHK_ARG(3, setInaudibleBehavior(soloudHandle, sourceHandle, time));
  JS_HANDLE(sol, args[1], sl::Soloud);
  auto src = intValue(args[2]);
  float time = floatValue(args[3]);
  sol->seek(src, time);
  return 0;
}


JSS_FUNC(releaseSoloud, args, ac) {
  JSS_CHK_ARG(1, releaseSoloud(soLoudHandle));
  int handle = intValue(args[1], 0);
  release_shared_resource<sl::Soloud>(handle);
  return 0;
}


JSS_FUNC(fadeVolume, args, ac) {
  JSS_CHK_ARG(4, fadeVolume(soloudHandle, sourceHandle, vol, time));
  JS_HANDLE(sol, args[1], sl::Soloud);
  auto src = intValue(args[2]);
  double vol = doubleValue(args[3]);
  double time = doubleValue(args[4]);
  sol->fadeVolume(src, vol, time);
  return 0;
}


JSS_FUNC(fadePan, args, ac) {
  JSS_CHK_ARG(4, fadePan(soloudHandle, sourceHandle, pan, time));
  JS_HANDLE(sol, args[1], sl::Soloud);
  auto src = intValue(args[2]);
  double pan = doubleValue(args[3]);
  double time = doubleValue(args[4]);
  sol->fadePan(src, pan, time);
  return 0;
}


JSS_FUNC(fadeRelativePlaySpeed, args, ac) {
  JSS_CHK_ARG(4, fadeRelativePlaySpeed(soloudHandle, sourceHandle, to, time));
  JS_HANDLE(sol, args[1], sl::Soloud);
  auto src = intValue(args[2]);
  double to = doubleValue(args[3]);
  double time = doubleValue(args[4]);
  sol->fadeRelativePlaySpeed(src, to, time);
  return 0;
}


JSS_FUNC(fadeGlobalVolume, args, ac) {
  JSS_CHK_ARG(3, fadeGlobalVolume(soloudHandle, vol, time));
  JS_HANDLE(sol, args[1], sl::Soloud);
  double vol = doubleValue(args[2]);
  double time = doubleValue(args[3]);
  sol->fadeGlobalVolume(vol, time);
  return 0;
}


JSS_FUNC(setFilterParameter, args, ac) {
  JSS_CHK_ARG(5, setFilterParameter(soloudHandle, sourceHandle, aFilterId, aAttributeId, aValue));
  JS_HANDLE(sol, args[1], sl::Soloud);
  auto src = intValue(args[2]);
  unsigned int filterid = intValue(args[3]);
  unsigned int attributeid = intValue(args[4]);
  float value = floatValue(args[5]);
  sol->setFilterParameter(src, filterid, attributeid, value);
  return 0;
}


JSS_FUNC(setFilter, args, ac) {
  JSS_CHK_ARG(3, setFilter(wavHandle, aFilterId, FilterType));
  JS_HANDLE(src, args[1], sl::AudioSource);
  int filterId = intValue(args[2]);
  int type = intValue(args[3]);
  auto ff = getFilterFactory(type);
  if (ff == NULL) {
    pushException("bad filter id");
    return 0;
  }
  src->setFilter(filterId, ff);
  return 0;
}


JSS_FUNC(clearFilter, args, ac) {
  JSS_CHK_ARG(2, clearFilter(wavHandle, aFilterId));
  JS_HANDLE(src, args[1], sl::AudioSource);
  int filterId = intValue(args[2]);
  src->setFilter(filterId, NULL);
  return 0;
}


JSS_INIT_MODULE(installAudio) {
  JSS_MOD(audio);
  installAudioPlugin(mod, vm);

  JSS_BIND(createSoloud);
  JSS_BIND(releaseSoloud);
  JSS_BIND(play);
  JSS_BIND(stop);
  JSS_BIND(setPause);
  JSS_BIND(setLooping);
  JSS_BIND(setLoopPoint);
  JSS_BIND(setVolume);
  JSS_BIND(setPan);
  JSS_BIND(setPanAbsolute);
  JSS_BIND(setProtectVoice);
  JSS_BIND(setInaudibleBehavior);
  JSS_BIND(setRelativePlaySpeed);
  JSS_BIND(seek);
  JSS_BIND(setFilterParameter);
  JSS_BIND(setFilter);
  JSS_BIND(clearFilter);

  JSS_BIND(fadeVolume);
  JSS_BIND(fadePan);
  JSS_BIND(fadeRelativePlaySpeed);
  JSS_BIND(fadeGlobalVolume);

  JSS_BIND(createWavSource);
  JSS_BIND(releaseSource);
  JSS_BIND(load);
  JSS_BIND(loadMem);
  JSS_BIND(loadRawWave);
  JSS_BIND(getLength);

  // 常量枚举
  JSS_ATTR(FILTERS_PER_STREAM, FILTERS_PER_STREAM);
  JSS_ATTR(SAMPLE_GRANULARITY, SAMPLE_GRANULARITY);
  JSS_ATTR(VOICE_COUNT,        VOICE_COUNT);
  JSS_ATTR(MAX_CHANNELS,       MAX_CHANNELS);
  JSS_ATTR(SOLOUD_VERSION,     SOLOUD_VERSION);
  JSS_ATTR(RAW_TYPE_8BIT,      1);
  JSS_ATTR(RAW_TYPE_16BIT,     2);
  JSS_ATTR(RAW_TYPE_32FLOAT,   3);

  // 过滤器类型枚举
  SO_ENUM(F, SOL_FILTER_TYPE, BassboostFilter);
  SO_ENUM(F, SOL_FILTER_TYPE, BiquadResonantFilter);
  SO_ENUM(F, SOL_FILTER_TYPE, DCRemovalFilter);
  SO_ENUM(F, SOL_FILTER_TYPE, EchoFilter);
  SO_ENUM(F, SOL_FILTER_TYPE, FFTFilter);
  SO_ENUM(F, SOL_FILTER_TYPE, FlangerFilter);
  SO_ENUM(F, SOL_FILTER_TYPE, LofiFilter);
  SO_ENUM(F, SOL_FILTER_TYPE, RobotizeFilter);
  SO_ENUM(F, SOL_FILTER_TYPE, SoundPitchFilter);
  SO_ENUM(F, SOL_FILTER_TYPE, WaveShaperFilter);

  // 各个过滤器参数枚举
  SO_ENUM(PITCH, SoundPitchFilterFact, RATE);
  SO_ENUM(PITCH, SoundPitchFilterFact, TEMPO);
  SO_ENUM(PITCH, SoundPitchFilterFact, PITCH);
  SO_ENUM(PITCH, SoundPitchFilterFact, PITCH_OCT);
  SO_ENUM(PITCH, SoundPitchFilterFact, PITCH_SEMI);
  SO_ENUM(PITCH, SoundPitchFilterFact, CHANNELS);
  SO_ENUM(PITCH, SoundPitchFilterFact, SAMPLERATE);

  SO_ENUM(BIQUAD, SoLoud::BiquadResonantFilter, NONE);
  SO_ENUM(BIQUAD, SoLoud::BiquadResonantFilter, LOWPASS);
  SO_ENUM(BIQUAD, SoLoud::BiquadResonantFilter, HIGHPASS);
  SO_ENUM(BIQUAD, SoLoud::BiquadResonantFilter, BANDPASS);
  SO_ENUM(BIQUAD, SoLoud::BiquadResonantFilter, WET);
  SO_ENUM(BIQUAD, SoLoud::BiquadResonantFilter, SAMPLERATE);
  SO_ENUM(BIQUAD, SoLoud::BiquadResonantFilter, FREQUENCY);
  SO_ENUM(BIQUAD, SoLoud::BiquadResonantFilter, RESONANCE);

  SO_ENUM(BIQUAD, SoLoud::BassboostFilter, WET);
  SO_ENUM(BIQUAD, SoLoud::BassboostFilter, BOOST);

  SO_ENUM(BIQUAD, SoLoud::FlangerFilter, WET);
  SO_ENUM(BIQUAD, SoLoud::FlangerFilter, DELAY);
  SO_ENUM(BIQUAD, SoLoud::FlangerFilter, FREQ);

  SO_ENUM(BIQUAD, SoLoud::LofiFilter, WET);
  SO_ENUM(BIQUAD, SoLoud::LofiFilter, SAMPLERATE);
  SO_ENUM(BIQUAD, SoLoud::LofiFilter, BITDEPTH);

  SO_ENUM(BIQUAD, SoLoud::RobotizeFilter, WET);

  SL_DEF(CLIP_ROUNDOFF);
  SL_DEF(ENABLE_VISUALIZATION);
  SL_DEF(LEFT_HANDED_3D);

  SL_DEF(AUTO);
  SL_DEF(SDL1);
  SL_DEF(SDL2);
  SL_DEF(PORTAUDIO);
  SL_DEF(WINMM);
  SL_DEF(XAUDIO2);
  SL_DEF(WASAPI);
  SL_DEF(ALSA);
  SL_DEF(OSS);
  SL_DEF(OPENAL);
  SL_DEF(COREAUDIO);
  SL_DEF(OPENSLES);
  SL_DEF(VITA_HOMEBREW);
  SL_DEF(NULLDRIVER);
  SL_DEF(BACKEND_MAX);
}


JSS_UNINIT_MODULE(uninstallAudio) {
}