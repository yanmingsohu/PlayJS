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


void toFloatSample(const short* in, float* out, const int count) {
  const float x = 1.0/32768.0;
  for (int i = 0; i < count; ++i) {
    out[i] = in[i] * x;
  }
}


void toIntSample(const float* in, short* out, const int count) {
  for (int i = 0; i < count; ++i) {
    out[i] = in[i] * 32768.0;
  }
}


JSS_FUNC(pitchSound, args, ac) {
  JSS_CHK_ARG(8, pitchSound(raw, channel, sampleRate, rate, tempo, pitch, pitchOct, pitchSemi));
  LocalTypedArray raw(args[1]);
  int channel = intValue(args[2]);
  int sampleRate = intValue(args[3]);
  double rate = doubleValue(args[4]);
  double tempo = doubleValue(args[5]);
  double pitch = doubleValue(args[6]);
  double oct = doubleValue(args[7]);
  double semi = doubleValue(args[8]);

  soundtouch::SoundTouch st;
  st.setChannels(channel);
  st.setSampleRate(sampleRate);
  st.setRate(rate);
  st.setTempo(tempo);
  st.setPitch(pitch);
  st.setPitchOctaves(oct);
  st.setPitchSemiTones(semi);

  const int samplesCont = raw.length() / 2;
  int size = st.getInputOutputSampleRatio() * samplesCont;
  float* input = new float[samplesCont];
  toFloatSample((short*)raw.bytes(), input, samplesCont);

  st.putSamples(input, samplesCont);
  st.flush();
  float* output = new float[size];
  st.receiveSamples(output, size);

  short* quan = new short[size];
  toIntSample(output, quan, size);
  delete [] output;
  delete [] input;

  JsValueRef ret;
  JsCreateExternalArrayBuffer(quan, size * sizeof(short),
      outputSamplesBufferFinalizeCallback, 0, &ret);
  return ret;
}


void installAudioPlugin(LocalVal& mod, VM* vm) {
  JSS_BIND(pitchSound);
}