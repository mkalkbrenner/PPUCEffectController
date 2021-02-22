#include "PPUCLedBlinkEffect.h"

void PPUCLedBlinkEffect::update() {
    if (stage == 0) {
        device->on();
        ++stage;
    }
    else if (stage == 1 && ms >= 200) {
        device->off();
        ++stage;
    }
    else if (stage == 2 && ms >= 400) {
        device->on();
        ++stage;
    }
    else if (stage == 3 && ms >= 600) {
        device->off();
        ++stage;
    }
    else if (stage == 4 && ms >= 800) {
        device->on();
        ++stage;
    }
    else if (ms >= 1000) {
        device->off();
        stop();
    }
}
