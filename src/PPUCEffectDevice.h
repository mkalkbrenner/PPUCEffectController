/*
  PPUCEffectDevice.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCEFFECTDEVICE_h
#define PPUCEFFECTDEVICE_h

class PPUCEffectDevice {
public:
    virtual void reset() = 0;

    virtual void on() = 0;

    void off();
};

#endif
