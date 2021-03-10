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
        _wavePWM = new WavePWM();
        _pin = pin;
        pinMode(_pin, OUTPUT);
        off();
    }

    void on();

    void reset();

    void setPWM(uint8_t pwm);

    WavePWM* getWavePWM();

protected:
    WavePWM* _wavePWM;

    int _pin;
};

#endif
