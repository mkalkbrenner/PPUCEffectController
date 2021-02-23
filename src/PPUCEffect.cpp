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
    //Serial.println("effect started");
    running = true;
    repeat = r;
    stage = 0;
    ms = 0;
    _ms = millis();
}

void PPUCEffect::updateMillis() {
    ms = millis() - _ms;
}

void PPUCEffect::stop() {
    running = false;
    stage = 0;
    if (repeat > 0) {
        start(--repeat);
    }
    else if (repeat == -1) {
        start(-1);
    }
}
