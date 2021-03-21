#include "PPUCRgbStripDevice.h"

void PPUCRgbStripDevice::setPWM(uint8_t pwm) {
    setPWMRed(pwm);
    setPWMGreen(pwm);
    setPWMBlue(pwm);
}

void PPUCRgbStripDevice::setPWMRed(uint8_t pwm) {
    analogWrite(pin, pwm);
}

void PPUCRgbStripDevice::setPWMGreen(uint8_t pwm) {
    analogWrite(pinGreen, pwm);
}

void PPUCRgbStripDevice::setPWMBlue(uint8_t pwm) {
    analogWrite(pinBlue, pwm);
}

WavePWM* PPUCRgbStripDevice::getWavePWMRed() {
    return wavePWM;
}

WavePWM* PPUCRgbStripDevice::getWavePWMGreen() {
    return wavePWMGreen;
}

WavePWM* PPUCRgbStripDevice::getWavePWMBlue() {
    return wavePWMBlue;
}
