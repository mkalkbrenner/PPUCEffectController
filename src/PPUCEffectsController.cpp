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

PPUCRgbStripDevice* PPUCEffectsController::rgbStripDevice() {
    return _rgbStripeDevice;
}

PPUCWS2812FXDevice* PPUCEffectsController::ws2812FXDevice(int port) {
    return ws2812FXDevices[--port][0];
}

PPUCCombinedGiAndLightMatrixWS2812FXDevice* PPUCEffectsController::giAndLightMatrix(int port) {
    return (PPUCCombinedGiAndLightMatrixWS2812FXDevice*) ws2812FXDevice(port);
}

PPUCCombinedGiAndLightMatrixWS2812FXDevice* PPUCEffectsController::createCombinedGiAndLightMatrixWs2812FXDevice(int port) {
    PPUCWS2812FXDevice* ws2812FXDevice = ws2812FXDevices[--port][0];

    PPUCCombinedGiAndLightMatrixWS2812FXDevice* giAndLightMatrix = new PPUCCombinedGiAndLightMatrixWS2812FXDevice(
        ws2812FXDevice->getWS2812FX(),
        ws2812FXDevice->getFirstLED(),
        ws2812FXDevice->getlastLED(),
        ws2812FXDevice->getFirstSegment(),
        ws2812FXDevice->getLastSegment()
    );

    giAndLightMatrix->off();

    ws2812FXDevices[port][0] = giAndLightMatrix;
    delete ws2812FXDevice;

    _eventDispatcher->addListener(giAndLightMatrix, EVENT_SOURCE_GI);
    _eventDispatcher->addListener(giAndLightMatrix, EVENT_SOURCE_LIGHT);

    return giAndLightMatrix;
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

        ++ws2812FXDeviceCounters[port];
    }

    return ws2812FXDevices[port][number];
}

PPUCWS2812FXDevice* PPUCEffectsController::ws2812FXDevice(int port, int number) {
    return ws2812FXDevices[--port][number];
}

PPUCGeneralIlluminationWPC* PPUCEffectsController::generalIllumintationWPC() {
    return _generalIllumintationWPC;
}

void PPUCEffectsController::addEffect(PPUCEffect* effect, PPUCEffectDevice* device, PPUCEvent* event, int priority, int repeat, int mode) {
    addEffect(new PPUCEffectContainer(effect, device, event, priority, repeat, mode));
}

void PPUCEffectsController::addEffect(PPUCEffectContainer* container) {
    container->effect->setEventDispatcher(this->eventDispatcher());
    container->effect->setDevice(container->device);
    stackEffectContainers[++stackCounter] = container;
}

void PPUCEffectsController::attachBrightnessControl(byte port, byte poti) {
    brightnessControl[--port] = poti;
}

void PPUCEffectsController::setBrightness(byte port, byte brightness) {
    ws2812FXDevices[--port][0]->setBrightness(brightness);
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
    _generalIllumintationWPC->update();

    _eventDispatcher->update();

    for (int i = 0; i <= stackCounter; i++) {
        if (stackEffectContainers[i]->effect->isRunning()) {
            stackEffectContainers[i]->effect->updateMillis();
            stackEffectContainers[i]->effect->update();
        }
    }

    if (millis() - ws2812UpdateInterval > UPDATE_INTERVAL_WS2812FX_EFFECTS) {
        // Updating the LEDs too fast leads to undefined behavior. Just update effects every 3ms.
        ws2812UpdateInterval = millis();

        for (int i = 0; i <= 6; i++) {
            if (ws2812FXstates[i]) {
                if (ws2812FXrunning[i]) {

                    ws2812FXDevices[i][0]->getWS2812FX()->service();

                    bool stop = true;
                    for (int k = 0; k < ws2812FXDeviceCounters[i]; k++) {
                        stop &= ws2812FXDevices[i][0]->isStopped();
                    }

                    if (stop) {
                        ws2812FXDevices[i][0]->getWS2812FX()->stop();
                        ws2812FXrunning[i] = false;
                    }
                } else {
                    bool stop = true;
                    for (int k = 0; k < ws2812FXDeviceCounters[i]; k++) {
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

    if (millis() - ws2812AfterGlowUpdateInterval > UPDATE_INTERVAL_WS2812FX_AFTERGLOW) {
        // Updating the LEDs too fast leads to undefined behavior. Just update every 3ms.
        ws2812AfterGlowUpdateInterval = millis();
        for (int i = 0; i <= 6; i++) {
            if (ws2812FXstates[i] && ws2812FXDevices[i][0]->hasAfterGlowSupport() && !ws2812FXrunning[i]) {
                // No other effect is running, handle after glow effect.
                ((PPUCCombinedGiAndLightMatrixWS2812FXDevice *) ws2812FXDevices[i][0])->updateAfterGlow();
                ws2812FXDevices[i][0]->getWS2812FX()->show();
            }
        }
    }

    if (millis() - brightnessUpdateInterval > UPDATE_INTERVAL_WS2812FX_BRIGHTNESS) {
        // Don't update the brightness too often.
        brightnessUpdateInterval = millis();
        for (byte i = 0; i < 4; i++) {
            brightnessReads[i] = analogRead(38 + i) / 4;
        }
        for (byte i = 0; i < 7; i++) {
            if (brightnessControl[i] > 0) {
                setBrightness(i + 1, brightnessReads[brightnessControl[i]]);
            }
        }
    }
}

void PPUCEffectsController::start() {
    _eventDispatcher->dispatch(
        new PPUCEvent(EVENT_SOURCE_EFFECT, 1, 255)
    );
}
