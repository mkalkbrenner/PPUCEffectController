/*
  PPUCWS2812FXBlink.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCWS2812FXBlink_h
#define PPUCWS2812FXBlink_h

#include <Arduino.h>
#include <WS2812FX.h>

#include "../PPUCWS2812FXEffect.h"

class PPUCWS2812FXBlink : public PPUCWS2812FXEffect {
public:
    void start(int repeat = 0);

    void stop();
};

#endif
