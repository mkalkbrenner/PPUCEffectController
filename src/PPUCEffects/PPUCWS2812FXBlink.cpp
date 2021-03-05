#include "PPUCWS2812FXBlink.h"

void PPUCWS2812FXBlink::start(int r) {
    ws2812FX->setSegment(getFirstSegment(), getFirstLED(), getlastLED(), FX_MODE_BLINK, RED, 300, NO_OPTIONS);
    PPUCEffect::start();
    ws2812FX->start();
}

void PPUCWS2812FXBlink::stop() {
    ws2812FX->stop();
    PPUCEffect::stop();
}
