/*
  PPUCWS2812FXEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCWS2812FXEffect_h
#define PPUCWS2812FXEffect_h

#include <Arduino.h>
#include <WS2812FX.h>

#include "../PPUCEffect.h"
#include "../PPUCEffectDevice.h"
#include "../PPUCEffectDevices/PPUCWS2812FXDevice.h"

class PPUCWS2812FXEffect : public PPUCEffect {
public:

    PPUCWS2812FXEffect(uint8_t mode, uint32_t color, uint16_t speed, uint8_t options, int duration = 0) {
        _mode = mode;
        _colors[0] = color;
        _speed = speed;
        _options = options;
        _duration = duration;
    }

    PPUCWS2812FXEffect(uint8_t mode, const uint32_t colors[], uint16_t speed, uint8_t options, int duration = 0) {
        _mode = mode;
        _colors[0] = colors[0];
        _colors[1] = colors[1];
        _colors[2] = colors[2];
        _speed = speed;
        _options = options;
        _duration = duration;
    }

    virtual void setDevice(PPUCEffectDevice* effectDevice);

    virtual void start(int repeat = 0);

    virtual void stop();

    virtual void update();

    int getFirstLED();
    int getlastLED();
    int getNumLEDs();

    int getFirstSegment();
    int getLastSegment();
    int getNumSegments();

protected:
    WS2812FX* ws2812FX;
    uint8_t _mode;
    uint32_t _colors[3] = {0, 0, 0};
    uint16_t _speed;
    uint8_t _options;
    int _duration; // 0 means unlimited
};

#endif
