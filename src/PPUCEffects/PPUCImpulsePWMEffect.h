/*
  PPUCImpulsePWMEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCImpulsePWMEffect_h
#define PPUCImpulsePWMEffect_h

#include <Arduino.h>
#include <WavePWM.h>

#include "PPUCWavePWMEffect.h"
#include "../PPUCEffectDevice.h"
#include "../PPUCEffectDevices/PPUCWavePWMDevice.h"

class PPUCImpulsePWMEffect : public PPUCWavePWMEffect {
public:

    PPUCImpulsePWMEffect(unsigned int frequency, uint8_t maxIntensity = 255) : PPUCWavePWMEffect(frequency, maxIntensity) {
        // nop
    }

    virtual void update();
};

#endif
