#include "PPUCWavePWMDevice.h"

void PPUCWavePWMDevice::on() {
    reset();
}

void PPUCWavePWMDevice::reset() {
    setPWM(0);
}

void PPUCWavePWMDevice::setPWM(uint8_t pwm) {
    analogWrite(_pin, pwm);
}

WavePWM* PPUCWavePWMDevice::getWavePWM() {
    return _wavePWM;
}
