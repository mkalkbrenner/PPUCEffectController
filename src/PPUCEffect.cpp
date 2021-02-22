#include "PPUCEffect.h"

PPUCEffect::PPUCEffect() {
}

void PPUCEffect::setEventDispatcher(PPUCEventDispatcher* eD) {
    _eventDispatcher = eD;
}

void PPUCEffect::setDevice(PPUCEffectDevice* effectDevice) {
    device = effectDevice;
}

void PPUCEffect::dispatch(PPUCEvent* event) {
    _eventDispatcher->dispatch(event);
}

bool PPUCEffect::isRunning() {
    return running;
}

void PPUCEffect::start(int r) {
    running = true;
    repeat = r;
    stage = 0;
    ms= millis();
}

void PPUCEffect::stop() {
    running = false;
    repeat = 0;
    stage = 0;
}
