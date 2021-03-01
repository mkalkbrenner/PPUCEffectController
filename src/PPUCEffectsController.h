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
#include <WS2812FX.h>
#include <WS2812FXOverlay.h>

#include "PPUCEffect.h"
#include "PPUCEffectContainer.h"
#include "PPUCEffectDevices/PPUCLedBuiltInDevice.h"
#include "PPUCEffectDevices/PPUCNullDevice.h"
#include "PPUCEffectDevices/PPUCWS2812SerialDevice.h"
#include "PPUCEffects/PPUCLedBlinkEffect.h"
#include "PPUCEffects/PPUCNullEffect.h"
#include "PPUCEffects/PPUCRGBColorCycleEffect.h"
#include "PPUCEffects/PPUCWS2812FXRainbowCycle.h"

#ifndef EFFECT_STACK_SIZE
#define EFFECT_STACK_SIZE 50

#endif

#if defined(PPUC_NUM_LEDS_1) && defined(PPUC_LED_TYPE_1)
    byte        ws2812DrawingMemory1[PPUC_NUM_LEDS_1 * ((PPUC_LED_TYPE_1 < 6) ? 3 : 4)];     // 3 bytes per LED for RGB, 4 bytes for RGBW
    DMAMEM byte ws2812DisplayMemory1[PPUC_NUM_LEDS_1 * ((PPUC_LED_TYPE_1 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_2) && defined(PPUC_LED_TYPE_2)
    byte        ws2812DrawingMemory2[PPUC_NUM_LEDS_2 * ((PPUC_LED_TYPE_2 < 6) ? 3 : 4)];     // 3 bytes per LED for RGB, 4 bytes for RGBW
    DMAMEM byte ws2812DisplayMemory2[PPUC_NUM_LEDS_2 * ((PPUC_LED_TYPE_2 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_3) && defined(PPUC_LED_TYPE_3)
    byte        ws2812DrawingMemory3[PPUC_NUM_LEDS_3 * ((PPUC_LED_TYPE_3 < 6) ? 3 : 4)];     // 3 bytes per LED for RGB, 4 bytes for RGBW
    DMAMEM byte ws2812DisplayMemory3[PPUC_NUM_LEDS_3 * ((PPUC_LED_TYPE_3 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_4) && defined(PPUC_LED_TYPE_4)
    byte        ws2812DrawingMemory4[PPUC_NUM_LEDS_4 * ((PPUC_LED_TYPE_4 < 6) ? 3 : 4)];     // 3 bytes per LED for RGB, 4 bytes for RGBW
    DMAMEM byte ws2812DisplayMemory4[PPUC_NUM_LEDS_4 * ((PPUC_LED_TYPE_4 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_5) && defined(PPUC_LED_TYPE_5)
    byte        ws2812DrawingMemory5[PPUC_NUM_LEDS_5 * ((PPUC_LED_TYPE_5 < 6) ? 3 : 4)];     // 3 bytes per LED for RGB, 4 bytes for RGBW
    DMAMEM byte ws2812DisplayMemory5[PPUC_NUM_LEDS_5 * ((PPUC_LED_TYPE_5 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_6) && defined(PPUC_LED_TYPE_6)
    byte        ws2812DrawingMemory6[PPUC_NUM_LEDS_6 * ((PPUC_LED_TYPE_6 < 6) ? 3 : 4)];     // 3 bytes per LED for RGB, 4 bytes for RGBW
    DMAMEM byte ws2812DisplayMemory6[PPUC_NUM_LEDS_6 * ((PPUC_LED_TYPE_6 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_7) && defined(PPUC_LED_TYPE_7)
    byte        ws2812DrawingMemory7[PPUC_NUM_LEDS_7 * ((PPUC_LED_TYPE_7 < 6) ? 3 : 4)];     // 3 bytes per LED for RGB, 4 bytes for RGBW
    DMAMEM byte ws2812DisplayMemory7[PPUC_NUM_LEDS_7 * ((PPUC_LED_TYPE_7 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

class PPUCEffectsController : public PPUCEventListener {

public:
    PPUCEffectsController(String controllerType) : PPUCEventListener(){
        _eventDispatcher = new PPUCEventDispatcher();
        _eventDispatcher->addListener(this);

        if (controllerType == "Teensy4.1") {
            _ledBuiltInDevice = new PPUCLedBuiltInDevice();
            _ledBuiltInDevice->on();
            _nullDevice = new PPUCNullDevice();
            #if defined(PPUC_NUM_LEDS_1) && defined(PPUC_LED_TYPE_1)
                _ws2812SerialDevices[0] = new PPUCWS2812SerialDevice(new WS2812FX(PPUC_NUM_LEDS_1, ws2812DisplayMemory1, ws2812DrawingMemory1, 1, PPUC_LED_TYPE_1));
                ((WS2812FX*) _ws2812SerialDevices[0]->getWS2812Serial())->init();
            #endif
            #if defined(PPUC_NUM_LEDS_2) && defined(PPUC_LED_TYPE_2)
                _ws2812SerialDevices[1] = new PPUCWS2812SerialDevice(new WS2812FX(PPUC_NUM_LEDS_2, ws2812DisplayMemory2, ws2812DrawingMemory2, 8, PPUC_LED_TYPE_2));
                ((WS2812FX*) _ws2812SerialDevices[1]->getWS2812Serial())->init();
            #endif
            #if defined(PPUC_NUM_LEDS_3) && defined(PPUC_LED_TYPE_3)
                _ws2812SerialDevices[2] = new PPUCWS2812SerialDevice(new WS2812FX(PPUC_NUM_LEDS_3, ws2812DisplayMemory3, ws2812DrawingMemory3, 14, PPUC_LED_TYPE_3));
                ((WS2812FX*) _ws2812SerialDevices[2]->getWS2812Serial())->init();
            #endif
            #if defined(PPUC_NUM_LEDS_4) && defined(PPUC_LED_TYPE_4)
                _ws2812SerialDevices[3] = new PPUCWS2812SerialDevice(new WS2812FX(PPUC_NUM_LEDS_4, ws2812DisplayMemory4, ws2812DrawingMemory4, 17, PPUC_LED_TYPE_4));
                ((WS2812FX*) _ws2812SerialDevices[3]->getWS2812Serial())->init();
            #endif
            #if defined(PPUC_NUM_LEDS_5) && defined(PPUC_LED_TYPE_5)
                _ws2812SerialDevices[4] = new PPUCWS2812SerialDevice(new WS2812FX(PPUC_NUM_LEDS_5, ws2812DisplayMemory5, ws2812DrawingMemory5, 20, PPUC_LED_TYPE_5));
                ((WS2812FX*) _ws2812SerialDevices[4]->getWS2812Serial())->init();
            #endif
            #if defined(PPUC_NUM_LEDS_6) && defined(PPUC_LED_TYPE_6)
                _ws2812SerialDevices[5] = new PPUCWS2812SerialDevice(new WS2812FX(PPUC_NUM_LEDS_6, ws2812DisplayMemory6, ws2812DrawingMemory6, 24, PPUC_LED_TYPE_6));
                ((WS2812FX*) _ws2812SerialDevices[5]->getWS2812Serial())->init();
            #endif
            #if defined(PPUC_NUM_LEDS_7) && defined(PPUC_LED_TYPE_7)
                _ws2812SerialDevices[6] = new PPUCWS2812SerialDevice(new WS2812FX(PPUC_NUM_LEDS_7, ws2812DisplayMemory7, ws2812DrawingMemory7, 29, PPUC_LED_TYPE_7));
                ((WS2812FX*) _ws2812SerialDevices[6]->getWS2812Serial())->init();
            #endif
        } else {
            Serial.print("Unsupported Effects Controller: ");
            Serial.println(controllerType);
        }
    }

    PPUCEventDispatcher* eventDispatcher();

    PPUCLedBuiltInDevice* ledBuiltInDevice();

    PPUCNullDevice* nullDevice();

    PPUCWS2812SerialDevice* ws2812SerialDevice(int port);

    PPUCWS2812SerialDevice* ws2812SerialOverlayDevice(int port, int number, int firstLED, int numLEDs);

    PPUCWS2812SerialDevice* ws2812SerialOverlayDevice(int port, int number);

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
    PPUCWS2812SerialDevice* _ws2812SerialDevices[7];
    PPUCWS2812SerialDevice* _ws2812SerialOverlayDevices[7][10];

    PPUCEffectContainer* stackEffectContainers[EFFECT_STACK_SIZE];
    int stackCounter = -1;

    int mode = 0;
};

#endif
