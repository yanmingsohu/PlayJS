#include "vm.h"
#include "js.h"
#include "shared.h"

#include <soloud.h>
#include <soloud_error.h>
#include <soloud_wav.h>


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


JSS_FUNC(releaseSoloud, args, ac) {
  JSS_CHK_ARG(1, releaseSoloud(soLoudHandle));
  int handle = intValue(args[1], 0);
  release_shared_resource<sl::Soloud>(handle);
  return 0;
}


JSS_INIT_MODULE(installAudio) {
  JSS_MOD(audio);
  JSS_BIND(createSoloud);
  JSS_BIND(releaseSoloud);
  JSS_BIND(play);
  JSS_BIND(stop);
  JSS_BIND(setPause);
  JSS_BIND(setLooping);

  JSS_BIND(createWavSource);
  JSS_BIND(releaseSource);
  JSS_BIND(load);
  JSS_BIND(loadMem);
  JSS_BIND(loadRawWave);
  JSS_BIND(getLength);

  JSS_ATTR(FILTERS_PER_STREAM, FILTERS_PER_STREAM);
  JSS_ATTR(SAMPLE_GRANULARITY, SAMPLE_GRANULARITY);
  JSS_ATTR(VOICE_COUNT,        VOICE_COUNT);
  JSS_ATTR(MAX_CHANNELS,       MAX_CHANNELS);
  JSS_ATTR(SOLOUD_VERSION,     SOLOUD_VERSION);
  JSS_ATTR(RAW_TYPE_8BIT,      1);
  JSS_ATTR(RAW_TYPE_16BIT,     2);
  JSS_ATTR(RAW_TYPE_32FLOAT,   3);

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