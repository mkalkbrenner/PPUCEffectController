/*
  PPUCNullEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCNULLEFFECT_h
#define PPUCNULLEFFECT_h

#include <Arduino.h>

#include "PPUCEffect.h"

class PPUCNullEffect : public PPUCEffect {
public:
    void update();

};

#endif
