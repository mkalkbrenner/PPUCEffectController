/*
  PPUCWS2812FXRainbowCycle.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCWS2812FXRainbowCycle_h
#define PPUCWS2812FXRainbowCycle_h

#include <Arduino.h>
#include <WS2812FX.h>

#include "../PPUCWS2812FXEffect.h"

class PPUCWS2812FXRainbowCycle : public PPUCWS2812FXEffect {
public:
    void start(int repeat = 0);

    void stop();
};

#endif
