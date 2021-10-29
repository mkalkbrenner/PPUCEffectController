#include "PPUCWS2812FXDevice.h"

void PPUCWS2812FXDevice::on() {
    reset();
    stopped = false;
}

void PPUCWS2812FXDevice::off() {
    reset();
    stopped = true;
}

void PPUCWS2812FXDevice::reset() {
    ws2812FX->setSegment(firstSegment, firstLED, lastLED, FX_MODE_STATIC, RGBW_BLACK, 1, NO_OPTIONS);
}

WS2812FX* PPUCWS2812FXDevice::getWS2812FX() {
    return ws2812FX;
}

int PPUCWS2812FXDevice::getFirstLED() {
    return firstLED;
}

int PPUCWS2812FXDevice::getlastLED() {
    return lastLED;
}

int PPUCWS2812FXDevice::getNumLEDs() {
    return lastLED - firstLED + 1;
}

int PPUCWS2812FXDevice::getFirstSegment() {
    return firstSegment;
}

int PPUCWS2812FXDevice::getLastSegment() {
    return lastSegment;
}

int PPUCWS2812FXDevice::getNumSegments() {
    return lastSegment - firstSegment + 1;
}

bool PPUCWS2812FXDevice::isStopped() {
    return stopped;
}

void PPUCWS2812FXDevice::setBrightness(byte b) {
    brightness = b;
    ws2812FX->setBrightness(brightness);
}

byte PPUCWS2812FXDevice::getBrightness() {
    return brightness;
}

