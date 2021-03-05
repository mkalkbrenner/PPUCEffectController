/*
  PPUCWS2812FXDevice.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCWS2812FXDevice_h
#define PPUCWS2812FXDevice_h

#include <Arduino.h>
#include <WS2812FX.h>

#include "PPUCEffectDevice.h"

#define RGBW_BLACK     (uint32_t)0x00000000
#define RGBW_PUREWHITE (uint32_t)0xFF000000

class PPUCWS2812FXDevice : public PPUCEffectDevice {
public:
    PPUCWS2812FXDevice(WS2812FX* ws2812FX, int firstLED, int lastLED, int firstSegment, int lastSegment) {
        _ws2812FX = ws2812FX;
        _firstLED = firstLED;
        _lastLED = lastLED;
        _firstSegment = firstSegment;
        _lastSegment = lastSegment;

        off();
    }

    void on();

    void reset();

    WS2812FX* getWS2812FX();

    int getFirstLED();
    int getlastLED();
    int getNumLEDs();

    int getFirstSegment();
    int getLastSegment();
    int getNumSegments();

protected:
    WS2812FX* _ws2812FX;

    int _firstLED;
    int _lastLED;
    int _firstSegment;
    int _lastSegment;
};

#endif
