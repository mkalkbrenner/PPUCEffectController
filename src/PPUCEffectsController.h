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
#include "PPUCLedBuiltInDevice.h"
#include "PPUCNullDevice.h"

#ifndef EFFECT_STACK_SIZE
#define EFFECT_STACK_SIZE 50

#endif

class PPUCEffectsController : public PPUCEventListener {

public:
    PPUCEffectsController(String controllerType) : PPUCEventListener(){
        _eventDispatcher = new PPUCEventDispatcher();
        _eventDispatcher->addListener(this);

        if (controllerType == "Teensy4.1") {
            _ledBuiltInDevice = new PPUCLedBuiltInDevice();
            _nullDevice = new PPUCNullDevice();
        } else {
            Serial.print("Unsupported Effects Controller: ");
            Serial.println(controllerType);
        }
    }

    PPUCEventDispatcher* eventDispatcher();

    PPUCLedBuiltInDevice* ledBuiltInDevice();

    PPUCNullDevice* nullDevice();

    void addEffect(PPUCEffect* effect, PPUCEffectDevice* device, PPUCEvent* event, int priority, int repeat, int mode);

    //void addEffect(PPUCEffect* effect, PPUCEffectDevice* device, PPUCEventSequence* sequence, int priority, int repeat);

    void addEffect(PPUCEffectContainer* container);

    void update();

    void handleEvent(PPUCEvent* event);

private:
    PPUCEventDispatcher* _eventDispatcher;
    PPUCLedBuiltInDevice* _ledBuiltInDevice;
    PPUCNullDevice* _nullDevice;

    PPUCEffectContainer* stackEffectContainers[EFFECT_STACK_SIZE];
    int stackCounter = -1;

    int mode = 0;
};

#endif
