#include "PPUCEffectControllerTestButtons.h"

PPUCEffectControllerTestButtons::PPUCEffectControllerTestButtons(PPUCEventDispatcher* eD) {
    eventDispatcher = eD;

    pinMode(22, INPUT_PULLUP);
    pinMode(23, INPUT_PULLUP);
}

void PPUCEffectControllerTestButtons::update() {
    bool state = !digitalRead(22);
    if (state && button1 != state) {
        eventDispatcher->dispatch(new PPUCEvent(EVENT_SOURCE_SWITCH, word(0, 201)));
        // Switch debouncing, delay() should be avoided but it is ok for the test buttons.
        delay(10);
    }
    button1 = state;

    state = !digitalRead(23);
    if (state && button2 != state) {
        eventDispatcher->dispatch(new PPUCEvent(EVENT_SOURCE_SWITCH, word(0, 202)));
        // Switch debouncing, delay() should be avoided but it is ok for the test buttons.
        delay(10);
    }
    button2 = state;
}
