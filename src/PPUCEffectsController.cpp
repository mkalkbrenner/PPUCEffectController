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

PPUCWavePWMDevice* PPUCEffectsController::shakerPWMDevice() {
    return _shakerPWMDevice;
}

PPUCWavePWMDevice* PPUCEffectsController::ledPWMDevice() {
    return _ledPWMDevice;
}

PPUCWS2812FXDevice* PPUCEffectsController::ws2812FXDevice(int port) {
    return ws2812FXDevices[--port][0];
}

PPUCWS2812FXDevice* PPUCEffectsController::createWS2812FXDevice(int port, int number, int segments, int firstLED, int lastLED) {
    --port;

    if (number == 0) {
        ws2812FXDevices[port][0]->_reduceLEDs(lastLED, segments - 1);
    }
    else {
        int firstSegment = ws2812FXDevices[port][number - 1]->getLastSegment() + 1;

        ws2812FXDevices[port][number] = new PPUCWS2812FXDevice(
            ws2812FXDevices[port][0]->getWS2812FX(),
            firstLED,
            lastLED,
            firstSegment,
            firstSegment + segments - 1
        );

        ++ws2812FXdevices[port];
    }

    return ws2812FXDevices[port][number];
}

PPUCWS2812FXDevice* PPUCEffectsController::ws2812FXDevice(int port, int number) {
    return ws2812FXDevices[--port][number];
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
    _testButtons->update();

    _eventDispatcher->update();

    for (int i = 0; i <= stackCounter; i++) {
        if (stackEffectContainers[i]->effect->isRunning()) {
            stackEffectContainers[i]->effect->updateMillis();
            stackEffectContainers[i]->effect->update();
        }
    }

    if (millis() - ws2812UpdateInterval > 10) {
        // Updating the LEDs too fast leads to undefined behavior. Just update every 10ms.
        ws2812UpdateInterval = millis();

        for (int i = 0; i <= 6; i++) {
            if (ws2812FXstates[i]) {
                if (ws2812FXrunning[i]) {

                    ws2812FXDevices[i][0]->getWS2812FX()->service();

                    bool stop = true;
                    for (int k = 0; k < ws2812FXdevices[i]; k++) {
                        stop &= ws2812FXDevices[i][0]->isStopped();
                    }
                    if (stop) {
                        ws2812FXDevices[i][0]->getWS2812FX()->stop();
                        ws2812FXrunning[i] = false;
                    }
                } else {
                    bool stop = true;
                    for (int k = 0; k < ws2812FXdevices[i]; k++) {
                        stop &= ws2812FXDevices[i][0]->isStopped();
                    }
                    if (!stop) {
                        ws2812FXDevices[i][0]->getWS2812FX()->start();
                        ws2812FXrunning[i] = true;
                        ws2812FXDevices[i][0]->getWS2812FX()->service();
                    }
                }
            }
        }
    }
}

void PPUCEffectsController::start() {
    _eventDispatcher->dispatch(
        new PPUCEvent(EVENT_SOURCE_EFFECT, 1, 255)
    );
}
