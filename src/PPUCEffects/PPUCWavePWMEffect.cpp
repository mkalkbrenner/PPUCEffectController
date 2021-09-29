#include "PPUCWavePWMEffect.h"

void PPUCWavePWMEffect::setDevice(PPUCEffectDevice* effectDevice) {
    PPUCEffect::setDevice(effectDevice);
    wavePWM = (WavePWM*) ((PPUCWavePWMDevice *) device)->getWavePWM();
}

void PPUCWavePWMEffect::start(int r) {
    PPUCEffect::start(r);
    device->on();
    wavePWM->setup(waveDuration);
}

void PPUCWavePWMEffect::stop() {
    device->off();
    PPUCEffect::stop();
}
