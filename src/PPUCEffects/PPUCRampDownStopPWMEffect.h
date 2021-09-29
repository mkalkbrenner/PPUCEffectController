/*
  PPUCRampDownStopPWMEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCRampDownStopPWMEffect_h
#define PPUCRampDownStopPWMEffect_h

#include <Arduino.h>
#include <WavePWM.h>

#include "PPUCWavePWMEffect.h"
#include "../PPUCEffectDevice.h"
#include "../PPUCEffectDevices/PPUCWavePWMDevice.h"

class PPUCRampDownStopPWMEffect : public PPUCWavePWMEffect {
public:

    PPUCRampDownStopPWMEffect(unsigned int frequency) : PPUCWavePWMEffect(frequency) {
        // nop
    }

    virtual void updateMillis();

    virtual void update();
};

#endif
