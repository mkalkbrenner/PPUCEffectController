#include "PPUCWS2812FXEffect.h"

void PPUCWS2812FXEffect::setDevice(PPUCEffectDevice* effectDevice) {
    PPUCEffect::setDevice(effectDevice);
    ws2812FX = (WS2812FX*) ((PPUCWS2812FXDevice *) device)->getWS2812FX();
}

void PPUCWS2812FXEffect::start(int r) {
    PPUCEffect::start();
    device->on();
    ws2812FX->setSegment(getFirstSegment(), getFirstLED(), getlastLED(), mode, colors, speed, options);
    ws2812FX->resetSegmentRuntime(getFirstSegment());
}

void PPUCWS2812FXEffect::stop() {
    device->off();
    PPUCEffect::stop();
}

void PPUCWS2812FXEffect::update() {
    // Don't call service() here!

    if (duration && duration < ms) {
        stop();
    }
}

int PPUCWS2812FXEffect::getFirstLED() {
    return ((PPUCWS2812FXDevice *) device)->getFirstLED();
}

int PPUCWS2812FXEffect::getlastLED() {
    return ((PPUCWS2812FXDevice *) device)->getlastLED();
}

int PPUCWS2812FXEffect::getNumLEDs() {
    return ((PPUCWS2812FXDevice *) device)->getNumLEDs();
}

int PPUCWS2812FXEffect::getFirstSegment() {
    return ((PPUCWS2812FXDevice *) device)->getFirstSegment();
}

int PPUCWS2812FXEffect::getLastSegment() {
    return ((PPUCWS2812FXDevice *) device)->getLastSegment();
}

int PPUCWS2812FXEffect::getNumSegments() {
    return ((PPUCWS2812FXDevice *) device)->getNumSegments();
}
