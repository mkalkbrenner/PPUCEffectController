/*
  PPUCNullDevice.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCNULLDEVICE_h
#define PPUCNULLDEVICE_h

#include <Arduino.h>

#include "../PPUCEffectDevice.h"

class PPUCNullDevice : public PPUCEffectDevice {
public:

    void on();

    void reset();

};

#endif
