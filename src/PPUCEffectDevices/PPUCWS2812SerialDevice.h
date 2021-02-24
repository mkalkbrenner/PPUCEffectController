/*
  PPUCWS2812SerialDevice.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCWS2812SerialDevice_h
#define PPUCWS2812SerialDevice_h

#include <Arduino.h>
#include <WS2812Serial.h>

#include "../PPUCEffectDevice.h"

class PPUCWS2812SerialDevice : public PPUCEffectDevice {
public:
    PPUCWS2812SerialDevice(WS2812Serial* ws2812Serial) {
        leds = ws2812Serial;
        leds->begin();
        off();
    }

    void on();

    void reset();

    void colorWipe(int color);

    void setColor(int rgb);
    void setColor(byte red, byte green, byte blue);
    void setColor(byte red, byte green, byte blue, byte white);

protected:
    WS2812Serial* leds;

};

#endif
