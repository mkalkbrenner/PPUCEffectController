#include "PPUCWS2812FXRainbowCycle.h"

void PPUCWS2812FXRainbowCycle::setDevice(PPUCEffectDevice* effectDevice) {
    PPUCEffect::setDevice(effectDevice);
    ws2812fx = (WS2812FX*) ((PPUCWS2812SerialDevice *) device)->getWS2812Serial();
}

void PPUCWS2812FXRainbowCycle::start(int r) {
    ws2812fx->setBrightness(100);
    ws2812fx->setSpeed(200);
    ws2812fx->setMode(FX_MODE_RAINBOW_CYCLE);
    PPUCEffect::start();
    ws2812fx->start();
}

void PPUCWS2812FXRainbowCycle::stop() {
    ws2812fx->stop();
    PPUCEffect::stop();
}

void PPUCWS2812FXRainbowCycle::update() {
    ws2812fx->service();
}
