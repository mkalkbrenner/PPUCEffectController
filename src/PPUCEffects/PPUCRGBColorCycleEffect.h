/*
  PPUCRGBColorCycleEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCRGBColorCycleEffect_h
#define PPUCRGBColorCycleEffect_h

#include <Arduino.h>

#include "../PPUCEffect.h"
#include "../PPUCEffectDevices/PPUCWS2812FXDevice.h"

class PPUCRGBColorCycleEffect : public PPUCEffect {
public:
    PPUCRGBColorCycleEffect(unsigned int delayMs) {
        delay = delayMs;
    }

    void update();

protected:
    unsigned int delay;
    uint32_t color;
};

#endif
