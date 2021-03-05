/*
  PPUCWS2812FXEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCWS2812FXEffect_h
#define PPUCWS2812FXEffect_h

#include <Arduino.h>
#include <WS2812FX.h>

#include "PPUCEffect.h"
#include "PPUCEffectDevice.h"
#include "PPUCEffectDevices/PPUCWS2812FXDevice.h"

class PPUCWS2812FXEffect : public PPUCEffect {
public:
    virtual void setDevice(PPUCEffectDevice* effectDevice);

    virtual void update();

    int getFirstLED();
    int getlastLED();
    int getNumLEDs();

    int getFirstSegment();
    int getLastSegment();
    int getNumSegments();

protected:
    WS2812FX* ws2812FX;
};

#endif
