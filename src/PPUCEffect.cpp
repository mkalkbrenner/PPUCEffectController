#include "PPUCEffect.h"

PPUCEffect::PPUCEffect() {
}

PPUCEffect::setEventDispatcher(PPUCEventDispatcher* eD) {
    _eventDispatcher = eD;
}

void PPUCEffect::dispatch(PPUCEvent* event) {
    _eventDispatcher->dispatch(event);
}

bool PPUCEffect::isRunning() {
    return running;
}

bool PPUCEffect::start(int r = 0) {
    running = true;
    repeat = r;
    ms= millis();
}

bool PPUCEffect::stop() {
    running = false;
    repeat = 0;
}
