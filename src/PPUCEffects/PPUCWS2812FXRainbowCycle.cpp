#include "PPUCWS2812FXRainbowCycle.h"

void PPUCWS2812FXRainbowCycle::start(int r) {
    ws2812FX->setSegment(getFirstSegment(), getFirstLED(), getlastLED(), FX_MODE_RAINBOW_CYCLE, RED, 1, NO_OPTIONS);
    PPUCEffect::start();
    ws2812FX->start();
}

void PPUCWS2812FXRainbowCycle::stop() {
    ws2812FX->stop();
    PPUCEffect::stop();
}
