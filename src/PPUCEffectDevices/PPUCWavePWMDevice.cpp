#include "PPUCWavePWMDevice.h"

void PPUCWavePWMDevice::on() {
    reset();
}

void PPUCWavePWMDevice::reset() {
    setPWM(0);
}

void PPUCWavePWMDevice::setPWM(uint8_t pwm) {
    analogWrite(pin, pwm);
    currentPWM = pwm;
}

uint8_t PPUCWavePWMDevice::getPWM() {
    return currentPWM;
}

WavePWM* PPUCWavePWMDevice::getWavePWM() {
    return wavePWM;
}
