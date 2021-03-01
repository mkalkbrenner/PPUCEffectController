/*
  PPUCWS2812FXRainbowCycle.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCWS2812FXRainbowCycle_h
#define PPUCWS2812FXRainbowCycle_h

#include <Arduino.h>
#include <WS2812FX.h>

#include "../PPUCEffect.h"
#include "../PPUCEffectDevice.h"
#include "../PPUCEffectDevices/PPUCWS2812SerialDevice.h"

class PPUCWS2812FXRainbowCycle : public PPUCEffect {
public:
    void setDevice(PPUCEffectDevice* effectDevice);

    void start(int repeat = 0);

    void stop();

    void update();

protected:
    WS2812FX* ws2812fx;
};

#endif
