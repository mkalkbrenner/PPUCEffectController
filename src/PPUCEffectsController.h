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
#include "PPUCEffectDevices/PPUCLedBuiltInDevice.h"
#include "PPUCEffectDevices/PPUCNullDevice.h"
#include "PPUCEffectDevices/PPUCWS2812SerialDevice.h"

#ifndef EFFECT_STACK_SIZE
#define EFFECT_STACK_SIZE 50

#endif

extern const int ws2812NumLeds1;
extern const int ws2812Type1;
extern byte      ws2812DrawingMemory1[];
extern byte      ws2812DisplayMemory1[];

extern const int ws2812NumLeds2;
extern const int ws2812Type2;
extern byte      ws2812DrawingMemory2[];
extern byte      ws2812DisplayMemory2[];

extern const int ws2812NumLeds3;
extern const int ws2812Type3;
extern byte      ws2812DrawingMemory3[];
extern byte      ws2812DisplayMemory3[];

extern const int ws2812NumLeds4;
extern const int ws2812Type4;
extern byte      ws2812DrawingMemory4[];
extern byte      ws2812DisplayMemory4[];

extern const int ws2812NumLeds5;
extern const int ws2812Type5;
extern byte      ws2812DrawingMemory5[];
extern byte      ws2812DisplayMemory5[];

extern const int ws2812NumLeds6;
extern const int ws2812Type6;
extern byte      ws2812DrawingMemory6[];
extern byte      ws2812DisplayMemory6[];

extern const int ws2812NumLeds7;
extern const int ws2812Type7;
extern byte      ws2812DrawingMemory7[];
extern byte      ws2812DisplayMemory7[];

class PPUCEffectsController : public PPUCEventListener {

public:
    PPUCEffectsController(String controllerType) : PPUCEventListener(){
        _eventDispatcher = new PPUCEventDispatcher();
        _eventDispatcher->addListener(this);

        if (controllerType == "Teensy4.1") {
            _ledBuiltInDevice = new PPUCLedBuiltInDevice();
            _ledBuiltInDevice->on();
            _nullDevice = new PPUCNullDevice();
            _ws2812Serial[0] = new PPUCWS2812SerialDevice(new WS2812Serial(ws2812NumLeds1, ws2812DisplayMemory1, ws2812DrawingMemory1, 1, ws2812Type1));
            _ws2812Serial[1] = new PPUCWS2812SerialDevice(new WS2812Serial(ws2812NumLeds2, ws2812DisplayMemory2, ws2812DrawingMemory2, 8, ws2812Type2));
            _ws2812Serial[2] = new PPUCWS2812SerialDevice(new WS2812Serial(ws2812NumLeds3, ws2812DisplayMemory3, ws2812DrawingMemory3, 14, ws2812Type3));
            _ws2812Serial[3] = new PPUCWS2812SerialDevice(new WS2812Serial(ws2812NumLeds4, ws2812DisplayMemory4, ws2812DrawingMemory4, 17, ws2812Type4));
            _ws2812Serial[4] = new PPUCWS2812SerialDevice(new WS2812Serial(ws2812NumLeds5, ws2812DisplayMemory5, ws2812DrawingMemory5, 20, ws2812Type5));
            _ws2812Serial[5] = new PPUCWS2812SerialDevice(new WS2812Serial(ws2812NumLeds6, ws2812DisplayMemory6, ws2812DrawingMemory6, 24, ws2812Type6));
            _ws2812Serial[6] = new PPUCWS2812SerialDevice(new WS2812Serial(ws2812NumLeds7, ws2812DisplayMemory7, ws2812DrawingMemory7, 29, ws2812Type7));
        } else {
            Serial.print("Unsupported Effects Controller: ");
            Serial.println(controllerType);
        }
    }

    PPUCEventDispatcher* eventDispatcher();

    PPUCLedBuiltInDevice* ledBuiltInDevice();

    PPUCNullDevice* nullDevice();

    PPUCWS2812SerialDevice* ws2812Serial(int port);

    void addEffect(PPUCEffect* effect, PPUCEffectDevice* device, PPUCEvent* event, int priority, int repeat, int mode);

    //void addEffect(PPUCEffect* effect, PPUCEffectDevice* device, PPUCEventSequence* sequence, int priority, int repeat);

    void addEffect(PPUCEffectContainer* container);

    void start();

    void update();

    void handleEvent(PPUCEvent* event);

private:
    PPUCEventDispatcher* _eventDispatcher;
    PPUCLedBuiltInDevice* _ledBuiltInDevice;
    PPUCNullDevice* _nullDevice;
    PPUCWS2812SerialDevice* _ws2812Serial[7];

    PPUCEffectContainer* stackEffectContainers[EFFECT_STACK_SIZE];
    int stackCounter = -1;

    int mode = 0;
};

#endif
