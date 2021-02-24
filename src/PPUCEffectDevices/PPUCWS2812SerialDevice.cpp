#include "PPUCWS2812SerialDevice.h"

void PPUCWS2812SerialDevice::on() {
    leds->clear();
    leds->setBrightness(128);
}

void PPUCWS2812SerialDevice::reset() {
    leds->setBrightness(0); // 0=off, 255=brightest
    leds->clear();
}

void PPUCWS2812SerialDevice::colorWipe(uint32_t color) {
    for (int i = 0; i < leds->numPixels(); i++) {
        leds->setPixel(i, color);
        leds->show();
    }
}

void PPUCWS2812SerialDevice::setColor(uint32_t color) {
    for (int i = 0; i < leds->numPixels(); i++) {
        leds->setPixel(i, color);
    }
    leds->show();
}

void PPUCWS2812SerialDevice::setColor(byte red, byte green, byte blue) {
    for (int i = 0; i < leds->numPixels(); i++) {
        leds->setPixel(i, red, green, blue);
    }
    leds->show();
}

void PPUCWS2812SerialDevice::setColor(byte red, byte green, byte blue, byte white) {
    for (int i = 0; i < leds->numPixels(); i++) {
        leds->setPixel(i, red, green, blue, white);
    }
    leds->show();
}
