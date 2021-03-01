/*
  PPUCWS2812SerialDevice.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCWS2812SerialDevice_h
#define PPUCWS2812SerialDevice_h

#include <Arduino.h>
#include <WS2812Serial.h>

#include "PPUCEffectDevice.h"

#define SK6812_RGBW WS2812_RGBW
#define SK6812_RBGW WS2812_RBGW
#define SK6812_GRBW WS2812_GRBW
#define SK6812_GBRW WS2812_GBRW
#define SK6812_BRGW WS2812_BRGW
#define SK6812_BGRW WS2812_BGRW
#define SK6812_WRGB WS2812_WRGB
#define SK6812_WRBG WS2812_WRBG
#define SK6812_WGRB WS2812_WGRB
#define SK6812_WGBR WS2812_WGBR
#define SK6812_WBRG WS2812_WBRG
#define SK6812_WBGR WS2812_WBGR
#define SK6812_RWGB WS2812_RWGB
#define SK6812_RWBG WS2812_RWBG
#define SK6812_GWRB WS2812_GWRB
#define SK6812_GWBR WS2812_GWBR
#define SK6812_BWRG WS2812_BWRG
#define SK6812_BWGR WS2812_BWGR
#define SK6812_RGWB WS2812_RGWB
#define SK6812_RBWG WS2812_RBWG
#define SK6812_GRWB WS2812_GRWB
#define SK6812_GBWR WS2812_GBWR
#define SK6812_BRWG WS2812_BRWG
#define SK6812_BGWR WS2812_BGWR

class PPUCWS2812SerialDevice : public PPUCEffectDevice {
public:
    PPUCWS2812SerialDevice(WS2812Serial* ws2812Serial) {
        leds = ws2812Serial;
        leds->begin();
        off();
    }

    void on();

    void reset();

    WS2812Serial* getWS2812Serial();

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
