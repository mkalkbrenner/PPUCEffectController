/*
  PPUCRGBColorCycleEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCRGBColorCycleEffect_h
#define PPUCRGBColorCycleEffect_h

#include <Arduino.h>

#include "../PPUCEffect.h"

class PPUCRGBColorCycleEffect : public PPUCEffect {
public:
    PPUCRGBColorCycleEffect(unsigned int delayMs) {
        delay = delayMs;
    }

    void update();

protected:
    unsigned int delay;
    unsigned int color;
};

#endif
