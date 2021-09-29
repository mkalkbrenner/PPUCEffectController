/*
  PPUCSinePWMEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCSinePWMEffect_h
#define PPUCSinePWMEffect_h

#include <Arduino.h>
#include <WavePWM.h>

#include "PPUCWavePWMEffect.h"
#include "../PPUCEffectDevice.h"
#include "../PPUCEffectDevices/PPUCWavePWMDevice.h"

class PPUCSinePWMEffect : public PPUCWavePWMEffect {
public:

    PPUCSinePWMEffect(unsigned int frequency, unsigned int duration, uint8_t maxIntensity = 255, uint8_t minIntensity = 0) : PPUCWavePWMEffect(frequency, maxIntensity, minIntensity) {
        this->duration = duration;
        this->rampCompression = 255 / maxIntensity;
    }

    virtual void update();

protected:
    unsigned int duration;
    uint8_t rampCompression;
};

#endif
