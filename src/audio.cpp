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


template<> struct SharedResourceDeleter<sl::Wav> {
  virtual void operator()(sl::Wav* w) {
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
  sl::Wav *wav = new sl::Wav();
  return make_shared_js_handle(wav);
}


JSS_FUNC(releaseWavSource, args, ac) {
  JSS_CHK_ARG(1, releaseWavSource(wavHandle));
  int handle = intValue(args[1], 0);
  release_shared_resource<sl::Wav>(handle);
  return 0;
}


JSS_FUNC(load, args, ac) {
  JSS_CHK_ARG(2, load(wavHandle, filename));
  JS_HANDLE(wav, args[1], sl::Wav);
  auto filename = stringValue(args[2]);
  auto ret = wav->load(filename.c_str());
  if (ret != sl::SO_NO_ERROR) {
    pushException(so_error(ret), ret);
  }
  return 0;
}


JSS_FUNC(getLength, args, ac) {
  JSS_CHK_ARG(1, getLength(wavHandle));
  JS_HANDLE(wav, args[1], sl::Wav);
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


JSS_FUNC(playWav, args, ac) {
  // TODO: 完整参数
  JSS_CHK_ARG(2, play(soloudHandle, wavHandle));
  JS_HANDLE(sol, args[1], sl::Soloud);
  JS_HANDLE(wav, args[2], sl::Wav);
  auto playhandle = sol->play(*wav);
  return wrapJs(playhandle);
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
  JSS_BIND(playWav);

  JSS_BIND(createWavSource);
  JSS_BIND(releaseWavSource);
  JSS_BIND(load);
  JSS_BIND(getLength);

  JSS_ATTR(FILTERS_PER_STREAM, FILTERS_PER_STREAM);
  JSS_ATTR(SAMPLE_GRANULARITY, SAMPLE_GRANULARITY);
  JSS_ATTR(VOICE_COUNT,        VOICE_COUNT);
  JSS_ATTR(MAX_CHANNELS,       MAX_CHANNELS);
  JSS_ATTR(SOLOUD_VERSION,     SOLOUD_VERSION);

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