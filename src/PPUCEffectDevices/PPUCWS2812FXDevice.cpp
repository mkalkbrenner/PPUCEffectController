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
    _ws2812FX->setSegment(_firstSegment, _firstLED, _lastLED, FX_MODE_STATIC, RGBW_BLACK, 1, NO_OPTIONS);
}

WS2812FX* PPUCWS2812FXDevice::getWS2812FX() {
    return _ws2812FX;
}

int PPUCWS2812FXDevice::getFirstLED() {
    return _firstLED;
}

int PPUCWS2812FXDevice::getlastLED() {
    return _lastLED;
}

int PPUCWS2812FXDevice::getNumLEDs() {
    return _lastLED - _firstLED + 1;
}

int PPUCWS2812FXDevice::getFirstSegment() {
    return _firstSegment;
}

int PPUCWS2812FXDevice::getLastSegment() {
    return _lastSegment;
}

int PPUCWS2812FXDevice::getNumSegments() {
    return _lastSegment - _firstSegment + 1;
}

bool PPUCWS2812FXDevice::isStopped() {
    return stopped;
}
