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

    virtual void start(int repeat = 0);

    virtual void stop();

    virtual void terminate();

    virtual void update() = 0;

    void updateMillis();

    void resetMillis();

    void setEventDispatcher(PPUCEventDispatcher* eD);

    virtual void setDevice(PPUCEffectDevice* effectDevice);

protected:
    void dispatch(PPUCEvent* event);

    PPUCEventDispatcher* eventDispatcher;
    PPUCEffectDevice* device;

    bool running = false;
    int repeat = 0; // -1 is endless, 0 means play once, 3 means repeat three times, ...
    unsigned int ms;
    unsigned long _ms;
    int stage = 0;
};

#endif
