/*
  PPUCLedBlinkEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCLedBlinkEffect_h
#define PPUCLedBlinkEffect_h

#include <Arduino.h>

#include "../PPUCEffect.h"

class PPUCLedBlinkEffect : public PPUCEffect {
public:
    void update();

};

#endif
