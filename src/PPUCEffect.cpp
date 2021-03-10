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
    //Serial.print("effect started, repeat ");
    //Serial.println(r);

    running = true;
    repeat = r;
    stage = 0;
    ms = 0;
    _ms = millis();
}

void PPUCEffect::updateMillis() {
    ms = millis() - _ms;
}

void PPUCEffect::resetMillis() {
    ms = 0;
    _ms = millis();
}

void PPUCEffect::stop() {
    if (repeat > 0) {
        start(--repeat);
    }
    else if (repeat == -1) {
        start(-1);
    }
    else {
       terminate();
    }
}

void PPUCEffect::terminate() {
    running = false;
    stage = 0;
    repeat = 0;
}
