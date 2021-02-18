/*
  PPUCEffectsController.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCEFFECTSCONTROLLER_h
#define PPUCEFFECTSCONTROLLER_h

#include <Arduino.h>
#include <PPUCEventDispatcher.h>
#include <PPUCEventListener.h>
#include <PPUCEvent.h>
#include <PPUCCrossLinkDebugger.h>

#include "PPUCEffect.h"
#include "PPUCEffectContainer.h"

#ifndef EFFECT_STACK_SIZE
#define EFFECT_STACK_SIZE 50

#endif

class PPUCEffectsController : public PPUCEventListener {

public:
    EffectsController(String controllerType);

    EventDispatcher *eventDispatcher();

    CrossLinkDebugger *crossLinkDebugger();

    void addEffect(PPUCEffect* effect, PPUCEffectDevice* device, PPUCEvent* event, int priority, int repeat, int mode);

    //void addEffect(PPUCEffect* effect, PPUCEffectDevice* device, PPUCEventSequence* sequence, int priority, int repeat);

    void addEffect(PPUCEffectContainer* container);

    void update();

private:
    EventDispatcher *_eventDispatcher;
    CrossLinkDebugger *_crossLinkDebugger;

    PPUCEffectContainer* stackEffectContainers[EFFECT_STACK_SIZE];
    int stackCounter = -1;

    int mode = 0;
};

#endif
