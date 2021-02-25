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

    void setBrightness(uint8_t n);
    uint8_t getBrightness();

    void colorWipe(uint32_t color);

    void setColor(uint32_t color);
    void setColor(byte red, byte green, byte blue);
    void setColor(byte red, byte green, byte blue, byte white);

    uint32_t color(uint8_t red, uint8_t green, uint8_t blue);
    uint32_t color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white);

protected:
    WS2812Serial* leds;

};

#endif
