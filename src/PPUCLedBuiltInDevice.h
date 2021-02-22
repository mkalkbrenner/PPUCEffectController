/*
  PPUCLedBuiltInDevice.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCLedBuiltInDevice_h
#define PPUCLedBuiltInDevice_h

#include <Arduino.h>

#include "PPUCEffectDevice.h"

class PPUCLedBuiltInDevice : public PPUCEffectDevice {
public:
    PPUCLedBuiltInDevice() {
        pinMode(LED_BUILTIN, OUTPUT);
    }

    void on();

    void reset();

};

#endif
