/*
  PPUCWavePWMDevice.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCWavePWMDevice_h
#define PPUCWavePWMDevice_h

#include <Arduino.h>
#include <WavePWM.h>

#include "../PPUCEffectDevice.h"

class PPUCWavePWMDevice : public PPUCEffectDevice {
public:
    PPUCWavePWMDevice(int pin) {
        this->wavePWM = new WavePWM();
        this->pin = pin;
        pinMode(pin, OUTPUT);
        off();
    }

    void on();

    void reset();

    void setPWM(uint8_t pwm);

    WavePWM* getWavePWM();

protected:
    WavePWM* wavePWM;

    int pin;
};

#endif
