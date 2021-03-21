/*
  PPUCRgbStripDevice.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCRgbStripDevice_h
#define PPUCRgbStripDevice_h

#include <Arduino.h>
#include <WavePWM.h>

#include "PPUCWavePWMDevice.h"

class PPUCRgbStripDevice : public PPUCWavePWMDevice {
public:
    PPUCRgbStripDevice(int pinRed, int pinGreen, int pinBlue) : PPUCWavePWMDevice(pinRed){
        this->wavePWMGreen = new WavePWM();
        this->wavePWMBlue = new WavePWM();
        this->pinGreen = pinGreen;
        this->pinBlue = pinBlue;
        pinMode(pinGreen, OUTPUT);
        pinMode(pinBlue, OUTPUT);
    }

    void setPWM(uint8_t pwm);

    void setPWMRed(uint8_t pwm);
    void setPWMGreen(uint8_t pwm);
    void setPWMBlue(uint8_t pwm);

    WavePWM* getWavePWMRed();
    WavePWM* getWavePWMGreen();
    WavePWM* getWavePWMBlue();

protected:
    WavePWM* wavePWMGreen;
    WavePWM* wavePWMBlue;

    int pinGreen;
    int pinBlue;
};

#endif
