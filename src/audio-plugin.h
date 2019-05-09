#pragma once

#include <soloud_filter.h>
#include "vm.h"



enum AUDIO_RAW_TYPE {
  RAW_TYPE_8BIT = 1,
  // 2 字节整形精度
  RAW_TYPE_16BIT,
  // 4 字节浮点精度
  RAW_TYPE_32FLOAT,
};


class SoundPitchFilterFact : public SoLoud::Filter {
public:
  enum PARM {
    RATE,
    TEMPO,
    PITCH,
    PITCH_OCT,
    PITCH_SEMI,
    CHANNELS,
    SAMPLERATE,
  };

  virtual SoLoud::FilterInstance* createInstance();
};


void installAudioPlugin(LocalVal& mod, VM* vm);