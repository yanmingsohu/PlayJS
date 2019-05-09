#include <soloud.h>
#include <soloud_filter.h>
#include <SoundTouch.h>

#include "audio-plugin.h"
#include "js.h"

//
// 下载并编译依赖 SoundTouch 在 `/deps` 目录中
//
#ifdef WIN32
#pragma comment(lib, "SoundTouch_x64.lib")
#endif


//
// !! 有问题, SoLoud是同步的, soundtouch是异步的
//
class SoundPitchInstance : public SoLoud::FilterInstance {
private:
  soundtouch::SoundTouch st;

public:
  SoundPitchInstance() {
    initParams(7);
    mParam[SoundPitchFilterFact::RATE] = 1;
    mParam[SoundPitchFilterFact::TEMPO] = 1;
    mParam[SoundPitchFilterFact::PITCH] = 1;
    mParam[SoundPitchFilterFact::PITCH_OCT] = 0;
    mParam[SoundPitchFilterFact::PITCH_SEMI] = 0;
    mParam[SoundPitchFilterFact::CHANNELS] = 1;
    mParam[SoundPitchFilterFact::SAMPLERATE] = 44100;
  }

  void filterChannel(float* aBuffer, unsigned int aSamples, 
                     float aSamplerate, double aTime, 
                     unsigned int ch, unsigned int ch_count) 
  {
    updateParams(aTime);

    st.setChannels(mParam[SoundPitchFilterFact::CHANNELS]);
    st.setSampleRate(mParam[SoundPitchFilterFact::SAMPLERATE]);
    st.setRate(mParam[SoundPitchFilterFact::RATE]);
    st.setTempo(mParam[SoundPitchFilterFact::TEMPO]);
    st.setPitch(mParam[SoundPitchFilterFact::PITCH]);
    st.setPitchOctaves(mParam[SoundPitchFilterFact::PITCH_OCT]);
    st.setPitchSemiTones(mParam[SoundPitchFilterFact::PITCH_SEMI]);

    st.putSamples(aBuffer, aSamples);
    auto r = st.receiveSamples(aBuffer, aSamples);
    printf("%d %d\n", aSamples, r);
  }
};


SoLoud::FilterInstance* SoundPitchFilterFact::createInstance() {
  return new SoundPitchInstance();
}


void outputSamplesBufferFinalizeCallback(_In_opt_ void* data) {
  delete [] ((float*)data);
}


template<class T>
void toFloatSample(const T* in, float* out, const int count) {
  const auto x = 1.0/((1 << (sizeof(T) * 8)) - 1);
  for (int i = 0; i < count; ++i) {
    out[i] = in[i] * x;
  }
}


template<class T>
void toIntSample(const float* in, T* out, const int count) {
  const auto c = (1 << (sizeof(T)*8)) - 1;
  for (int i = 0; i < count; ++i) {
    out[i] = in[i] * c;
  }
}


// pitch, pitchOct, pitchSemi 只有一个按顺序生效
JSS_FUNC(pitchSound, args, ac) {
  JSS_CHK_ARG(10, pitchSound(raw, channel, sampleRate, rate, tempo, \
      pitch, pitchOct, pitchSemi, inputType, outputType));
  LocalTypedArray raw(args[1]);
  const int channel = intValue(args[2]);
  const int sampleRate = intValue(args[3]);
  const double rate = doubleValue(args[4]);
  const double tempo = doubleValue(args[5]);
  const double pitch = doubleValue(args[6]);
  const double oct = doubleValue(args[7]);
  const double semi = doubleValue(args[8]);
  const int itype = intValue(args[9]);
  const int otype = intValue(args[10]);

  soundtouch::SoundTouch st;
  st.setChannels(channel);
  st.setSampleRate(sampleRate);
  st.setRate(rate);
  st.setTempo(tempo);
  
  if (pitch != 1) st.setPitch(pitch);
  else if (oct != 0) st.setPitchOctaves(oct);
  else if (semi != 0) st.setPitchSemiTones(semi);

  int samplesCont = 0;
  float* srcData = 0;
  std::unique_ptr<float[]> _src_del;

  switch (itype) {
  case AUDIO_RAW_TYPE::RAW_TYPE_8BIT:
    samplesCont = raw.length();
    srcData = new float[samplesCont];
    _src_del.reset(srcData);
    toFloatSample(raw.bytes(), srcData, samplesCont);
    break;

  case AUDIO_RAW_TYPE::RAW_TYPE_16BIT:
    samplesCont = raw.length() / 2;
    srcData = new float[samplesCont];
    _src_del.reset(srcData);
    toFloatSample((short*)raw.bytes(), srcData, samplesCont);
    break;

  case AUDIO_RAW_TYPE::RAW_TYPE_32FLOAT:
    samplesCont = raw.length() / 4;
    srcData = (float*) raw.bytes();
    break;
  }

  st.putSamples(srcData, samplesCont);
  st.flush();

  int dst_size = st.getInputOutputSampleRatio() * samplesCont;
  float* output = new float[dst_size];
  std::unique_ptr<float[]> _out_del;
  st.receiveSamples(output, dst_size);

  void* ext_arr = 0;
  int ext_size = 0;

  switch (otype) {
  case AUDIO_RAW_TYPE::RAW_TYPE_8BIT:
    _out_del.reset(output);
    ext_size = dst_size;
    ext_arr = new byte[ext_size];
    toIntSample(output, (byte*)ext_arr, dst_size);
    break;

  case AUDIO_RAW_TYPE::RAW_TYPE_16BIT:
    _out_del.reset(output);
    ext_size = dst_size * 2;
    ext_arr = new short[dst_size];
    toIntSample(output, (short*) ext_arr, dst_size);
    break;

  case AUDIO_RAW_TYPE::RAW_TYPE_32FLOAT:
    ext_size = dst_size * 4;
    ext_arr = output;
    break;
  }

  JsValueRef ret;
  JsCreateExternalArrayBuffer(ext_arr, ext_size,
      outputSamplesBufferFinalizeCallback, 0, &ret);
  return ret;
}


void installAudioPlugin(LocalVal& mod, VM* vm) {
  JSS_BIND(pitchSound);
}