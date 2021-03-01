#include "PPUCEffectsController.h"

PPUCEventDispatcher* PPUCEffectsController::eventDispatcher() {
    return _eventDispatcher;
}

PPUCLedBuiltInDevice* PPUCEffectsController::ledBuiltInDevice() {
    return _ledBuiltInDevice;
}

PPUCNullDevice* PPUCEffectsController::nullDevice() {
    return _nullDevice;
}

PPUCWS2812SerialDevice* PPUCEffectsController::ws2812SerialDevice(int port) {
    return _ws2812SerialDevices[--port];
}

PPUCWS2812SerialDevice* PPUCEffectsController::ws2812SerialOverlayDevice(int port, int number, int firstLED, int numLEDs) {
    WS2812FX* ws2812FX = (WS2812FX*) _ws2812SerialDevices[port]->getWS2812Serial();
    WS2812FX* ws2812FXOverlay = (WS2812FX*) new WS2812FXOverlay(ws2812FX, firstLED, numLEDs);

    _ws2812SerialOverlayDevices[--port][number] = new PPUCWS2812SerialDevice(ws2812FXOverlay);

    return _ws2812SerialOverlayDevices[port][number];
}

void PPUCEffectsController::addEffect(PPUCEffect* effect, PPUCEffectDevice* device, PPUCEvent* event, int priority, int repeat, int mode) {
    addEffect(new PPUCEffectContainer(effect, device, event, priority, repeat, mode));
}

void PPUCEffectsController::addEffect(PPUCEffectContainer* container) {
    container->effect->setEventDispatcher(this->eventDispatcher());
    container->effect->setDevice(container->device);
    stackEffectContainers[++stackCounter] = container;
}

void PPUCEffectsController::handleEvent(PPUCEvent* event) {
    for (int i = 0; i <= stackCounter; i++) {
        if (
            event->sourceId == stackEffectContainers[i]->event->sourceId &&
            event->eventId == stackEffectContainers[i]->event->eventId &&
            event->value == stackEffectContainers[i]->event->value &&
            (
                mode == stackEffectContainers[i]->mode ||
                -1 == stackEffectContainers[i]->mode // -1 means any mode
            )
        ) {
            for (int k = 0; k <= stackCounter; k++) {
                if (
                    stackEffectContainers[i]->device == stackEffectContainers[k]->device &&
                    stackEffectContainers[k]->effect->isRunning()
                ) {
                    if (stackEffectContainers[i]->priority > stackEffectContainers[k]->priority) {
                        stackEffectContainers[k]->effect->terminate();
                        stackEffectContainers[i]->effect->start(stackEffectContainers[i]->repeat);
                    }
                    break;
                }
                if (k == stackCounter) {
                    stackEffectContainers[i]->effect->start(stackEffectContainers[i]->repeat);
                }
            }
        }
    }
}

void PPUCEffectsController::update() {
    _eventDispatcher->update();

    for (int i = 0; i <= stackCounter; i++) {
        if (stackEffectContainers[i]->effect->isRunning()) {
            stackEffectContainers[i]->effect->updateMillis();
            stackEffectContainers[i]->effect->update();
        }
    }
}

void PPUCEffectsController::start() {
    _eventDispatcher->dispatch(
        new PPUCEvent(EVENT_SOURCE_EFFECT, 1, 255)
    );
}
