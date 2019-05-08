#pragma once

#include <soloud_filter.h>
#include "vm.h"


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