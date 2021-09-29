#include "PPUCImpulsePWMEffect.h"

void PPUCImpulsePWMEffect::update() {
    if (ms > waveDuration) {
        stop();
        return;
    }

    uint8_t pwm = compression * wavePWM->getQuadraticValue(ms);

    // Safety net.
    if (pwm > 255) {
        pwm = 255;
    }

    ((PPUCWavePWMDevice *) device)->setPWM(pwm);
}
