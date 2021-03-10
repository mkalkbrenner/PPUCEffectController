/*
  PPUCSinePWMEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCSinePWMEffect_h
#define PPUCSinePWMEffect_h

#include <Arduino.h>
#include <WavePWM.h>

#include "../PPUCEffect.h"
#include "../PPUCEffectDevice.h"
#include "../PPUCEffectDevices/PPUCWavePWMDevice.h"

class PPUCSinePWMEffect : public PPUCEffect {
public:

    PPUCSinePWMEffect(unsigned int frequency, unsigned int duration, uint8_t maxIntensity = 255, uint8_t minIntensity = 0) {
        this->waveDuration = 1000 / frequency;
        this->duration = duration;
        this->maxIntensity = maxIntensity;
        this->minIntensity = minIntensity;
        this->rampCompression = maxIntensity / 255;
        this->compression = (maxIntensity - minIntensity) / 255;
    }

    virtual void setDevice(PPUCEffectDevice* effectDevice);

    virtual void start(int repeat = 0);

    virtual void stop();

    virtual void update();

protected:
    WavePWM* wavePWM;
    unsigned int waveDuration;
    unsigned int duration;
    uint8_t minIntensity;
    uint8_t maxIntensity;
    uint8_t rampCompression;
    uint8_t compression;
};

#endif
