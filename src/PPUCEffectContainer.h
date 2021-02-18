/*
  PPUCEffectContainer.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCEFFECTCONTAINER_h
#define PPUCEFFECTCONTAINER_h

#include <PPUCEvent.h>
#include <PPUCEffect.h>
#include <PPUCEffectDevice.h>

struct PPUCEffectContainer {

    PPUCEffect* effect;
    PPUCEffectDevice* device;
    PPUCEvent* event;
    int priority; // 0 = default, higher value means higher priority
    int repeat; // 0 = no repeat, >=1 times repeat
    int mode; // -1 = always, 0 = normal play, >=1 multiball, mode, scene, ball save ...

    PPUCEffectContainer(PPUCEffect* ef, PPUCEffectDevice* d, PPUCEvent* ev, int p) {
        effect = ef;
        device = d;
        event = ev;
        priority = p;
        repeat = 1;
        mode = 0;
    }

    PPUCEffectContainer(PPUCEffect* ef, PPUCEffectDevice* d, PPUCEvent* ev, int p, int r) {
        effect = ef;
        device = d;
        event = ev;
        priority = p;
        repeat = r;
        mode = 0;
    }

    PPUCEffectContainer(PPUCEffect* ef, PPUCEffectDevice* d, PPUCEvent* ev, int p, int r, int m) {
        effect = ef;
        device = d;
        event = ev;
        priority = p;
        repeat = r;
        mode = m;
    }
};

#endif
