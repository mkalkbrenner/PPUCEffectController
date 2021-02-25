#include "PPUCWS2812SerialDevice.h"

void PPUCWS2812SerialDevice::on() {
    leds->clear();
    leds->setBrightness(128);
}

void PPUCWS2812SerialDevice::reset() {
    leds->setBrightness(0); // 0=off, 255=brightest
    leds->clear();
}

void PPUCWS2812SerialDevice::setBrightness(uint8_t n) {
    leds->setBrightness(n);
}

uint8_t PPUCWS2812SerialDevice::getBrightness() {
    return leds->getBrightness();
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

uint32_t PPUCWS2812SerialDevice::color(uint8_t red, uint8_t green, uint8_t blue) {
    return leds->Color(red, green, blue);
}

uint32_t PPUCWS2812SerialDevice::color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
    return leds->Color(red, green, blue, white);
}
