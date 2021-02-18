#include "PPUCEffectsController.h"

PPUCEffectsController::PPUCEffectsController(String controllerType) {
    _eventDispatcher = new EventDispatcher();
    _eventDispatcher->addListener(this);

    if (controllerType == "Teensy4.1") {
        //UV = new UVStrip(37, _scheduler);
    } else {
        Serial.print("Unsupported Effects Controller: ");
        Serial.println(controllerType);
    }
}

EventDispatcher *PPUCEffectsController::eventDispatcher() {
    return _eventDispatcher;
}

CrossLinkDebugger *PPUCEffectsController::crossLinkDebugger() {
    return _crossLinkDebugger;
}

void PPUCEffectsController::addEffect(PPUCEffect* effect, PPUCEffectDevice* device, PPUCEvent* event, int priority, int repeat, int mode) {
    addEffect(new PPUCEffectContainer(effect, device, event, priority, repeat, mode));
}

void PPUCEffectsController::addEffect(PPUCEffectContainer* container) {
    container->effect->setEventDispatcher(_eventDispatcher);
    container->effect->setDevice(container->device);
    stackEffectContainers[++stackCounter] = container;
}

void PPUCEffectsController::handleEvent(PPUCEvent* event) {
    for (int i = 0; i <= stackCounter; i++) {
        if (
                event == stackEffectContainers[i]->event &&
                (
                    mode == stackEffectContainers[i]->mode ||
                    -1 == stackEffectContainers[i]->mode
                )
            ) {
            for (int k = 0; k <= stackCounter; k++) {
                if (
                        stackEffectContainers[i]->device == stackEffectContainers[k]->device &&
                        !stackEffectContainers[k]->effect->isRunning()
                ) {
                    if (stackEffectContainers[i]->priority > stackEffectContainers[k]->priority) {
                        stackEffectContainers[k]->effect->stop();
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
    for (int i = 0; i <= stackCounter; i++) {
        if (stackEffectContainers[i]->effect->isRunning()) {
            stackEffectContainers[i]->effect->update();
        }
    }
}
