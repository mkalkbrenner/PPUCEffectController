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
            event == stackEffectContainers[i]->event &&
            (
                mode == stackEffectContainers[i]->mode ||
                -1 == stackEffectContainers[i]->mode // -1 means any mode
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
