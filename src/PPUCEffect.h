/*
  PPUCEffect.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCEFFECT_h
#define PPUCEFFECT_h

#include <Arduino.h>
#include <PPUCEventDispatcher.h>
#include <PPUCEvent.h>

#include "PPUCEffectDevice.h"

class PPUCEffect {
public:
    PPUCEffect();

    bool isRunning();

    void start(int repeat = 0);
    void stop();

    virtual void update() = 0;

    void setEventDispatcher(PPUCEventDispatcher* eD);

    void setDevice(PPUCEffectDevice* effectDevice);

protected:
    void dispatch(PPUCEvent* event);

    PPUCEventDispatcher* _eventDispatcher;
    PPUCEffectDevice* device;

    bool running = false;
    int repeat = 0; // -1 is endless, 0 means play once, 3 means three times, ...
    unsigned long ms;
    int stage = 0;
};

#endif
