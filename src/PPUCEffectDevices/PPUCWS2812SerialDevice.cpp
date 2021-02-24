#include "PPUCWS2812SerialDevice.h"

void PPUCWS2812SerialDevice::on() {
    reset();
}

void PPUCWS2812SerialDevice::reset() {
    leds->setBrightness(0); // 0=off, 255=brightest
    leds->clear();
}

void PPUCWS2812SerialDevice::colorWipe(int color) {
    for (int i = 0; i < leds->numPixels(); i++) {
        leds->setPixel(i, color);
    }
    leds->show();
}

void PPUCWS2812SerialDevice::setColor(int rgb) {
    for (int i = 0; i < leds->numPixels(); i++) {
        leds->setPixel(i, rgb);
    }
    leds->show();
}

void PPUCWS2812SerialDevice::setColor(byte red, byte green, byte blue) {
    uint32_t color = leds->Color(red, green, blue);
    for (int i = 0; i < leds->numPixels(); i++) {
        leds->setPixel(i, color);
    }
    leds->show();
}

void PPUCWS2812SerialDevice::setColor(byte red, byte green, byte blue, byte white) {
    uint32_t color = leds->Color(red, green, blue, white);
    for (int i = 0; i < leds->numPixels(); i++) {
        leds->setPixel(i, color);
    }
    leds->show();
}
