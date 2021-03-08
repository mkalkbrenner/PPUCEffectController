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

#include "PPUCEffect.h"
#include "PPUCEffectContainer.h"
#include "PPUCEffectDevices/PPUCLedBuiltInDevice.h"
#include "PPUCEffectDevices/PPUCNullDevice.h"
#include "PPUCEffectDevices/PPUCWS2812FXDevice.h"
#include "PPUCEffects/PPUCLedBlinkEffect.h"
#include "PPUCEffects/PPUCNullEffect.h"
#include "PPUCEffects/PPUCRGBColorCycleEffect.h"
#include "PPUCEffects/PPUCWS2812FXEffect.h"

#ifndef EFFECT_STACK_SIZE
#define EFFECT_STACK_SIZE 50

#endif

#if defined(PPUC_NUM_LEDS_1) && defined(PPUC_LED_TYPE_1)
    DMAMEM byte frameBuffer1[PPUC_NUM_LEDS_1 * ((PPUC_LED_TYPE_1 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_2) && defined(PPUC_LED_TYPE_2)
    DMAMEM byte frameBuffer2[PPUC_NUM_LEDS_2 * ((PPUC_LED_TYPE_2 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_3) && defined(PPUC_LED_TYPE_3)
    DMAMEM byte frameBuffer3[PPUC_NUM_LEDS_3 * ((PPUC_LED_TYPE_3 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_4) && defined(PPUC_LED_TYPE_4)
    DMAMEM byte frameBuffer4[PPUC_NUM_LEDS_4 * ((PPUC_LED_TYPE_4 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_5) && defined(PPUC_LED_TYPE_5)
    DMAMEM byte frameBuffer5[PPUC_NUM_LEDS_5 * ((PPUC_LED_TYPE_5 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_6) && defined(PPUC_LED_TYPE_6)
    DMAMEM byte frameBuffer6[PPUC_NUM_LEDS_6 * ((PPUC_LED_TYPE_6 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
#endif

#if defined(PPUC_NUM_LEDS_7) && defined(PPUC_LED_TYPE_7)
    DMAMEM byte frameBuffer7[PPUC_NUM_LEDS_7 * ((PPUC_LED_TYPE_7 < 6) ? 3 : 4) * 4]; // 12 bytes per LED for RGB, 16 bytes for RGBW
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
                _ws2812FXDevices[0][0] = new PPUCWS2812FXDevice(
                    new WS2812FX(PPUC_NUM_LEDS_1, frameBuffer1, malloc(PPUC_NUM_LEDS_1 * ((PPUC_LED_TYPE_1 < 6) ? 3 : 4)), 1, PPUC_LED_TYPE_1),
                    0,
                    PPUC_NUM_LEDS_1 - 1,
                    0,
                    0
                );
                _ws2812FXDevices[0][0]->getWS2812FX()->init();
                _ws2812FXDevices[0][0]->reset();
                ws2812FXstates[0] = true;
            #endif
            #if defined(PPUC_NUM_LEDS_2) && defined(PPUC_LED_TYPE_2)
               _ws2812FXDevices[1][0] = new PPUCWS2812FXDevice(
                    new WS2812FX(PPUC_NUM_LEDS_2, frameBuffer2, malloc(PPUC_NUM_LEDS_2 * ((PPUC_LED_TYPE_2 < 6) ? 3 : 4)), 8, PPUC_LED_TYPE_2),
                    0,
                    PPUC_NUM_LEDS_2 - 1,
                    0,
                    0
                );
                _ws2812FXDevices[1][0]->getWS2812FX()->init();
                ws2812FXstates[1] = 1;
            #endif
            #if defined(PPUC_NUM_LEDS_3) && defined(PPUC_LED_TYPE_3)
            _ws2812FXDevices[2][0] = new PPUCWS2812FXDevice(
                    new WS2812FX(PPUC_NUM_LEDS_3, frameBuffer3, malloc(PPUC_NUM_LEDS_3 * ((PPUC_LED_TYPE_3 < 6) ? 3 : 4)), 14, PPUC_LED_TYPE_3),
                    0,
                    PPUC_NUM_LEDS_3 - 1,
                    0,
                    0
                );
                _ws2812FXDevices[2][0]->getWS2812FX()->init();
                ws2812FXstates[2] = true;
            #endif
            #if defined(PPUC_NUM_LEDS_4) && defined(PPUC_LED_TYPE_4)
            _ws2812FXDevices[3][0] = new PPUCWS2812FXDevice(
                    new WS2812FX(PPUC_NUM_LEDS_4, frameBuffer4, malloc(PPUC_NUM_LEDS_4 * ((PPUC_LED_TYPE_4 < 6) ? 3 : 4)), 17, PPUC_LED_TYPE_4),
                    0,
                    PPUC_NUM_LEDS_4 - 1,
                    0,
                    0
                );
                _ws2812FXDevices[3][0]->getWS2812FX()->init();
                ws2812FXstates[3] = true;
            #endif
            #if defined(PPUC_NUM_LEDS_5) && defined(PPUC_LED_TYPE_5)
            _ws2812FXDevices[4][0] = new PPUCWS2812FXDevice(
                    new WS2812FX(PPUC_NUM_LEDS_5, frameBuffer5, malloc(PPUC_NUM_LEDS_5 * ((PPUC_LED_TYPE_5 < 6) ? 3 : 4)), 20, PPUC_LED_TYPE_5),
                    0,
                    PPUC_NUM_LEDS_5 - 1,
                    0,
                    0
                );
                _ws2812FXDevices[4][0]->getWS2812FX()->init();
                ws2812FXstates[4] = true;
            #endif
            #if defined(PPUC_NUM_LEDS_6) && defined(PPUC_LED_TYPE_6)
            _ws2812FXDevices[5][0] = new PPUCWS2812FXDevice(
                    new WS2812FX(PPUC_NUM_LEDS_6, frameBuffer6, malloc(PPUC_NUM_LEDS_6 * ((PPUC_LED_TYPE_6 < 6) ? 3 : 4)), 24, PPUC_LED_TYPE_6),
                    0,
                    PPUC_NUM_LEDS_6 - 1,
                    0,
                    0
                );
                _ws2812FXDevices[5][0]->getWS2812FX()->init();
                ws2812FXstates[5] = true;
            #endif
            #if defined(PPUC_NUM_LEDS_7) && defined(PPUC_LED_TYPE_7)
            _ws2812FXDevices[6][0] = new PPUCWS2812FXDevice(
                    new WS2812FX(PPUC_NUM_LEDS_7, frameBuffer7, malloc(PPUC_NUM_LEDS_7 * ((PPUC_LED_TYPE_7 < 6) ? 3 : 4)), 29, PPUC_LED_TYPE_7),
                    0,
                    PPUC_NUM_LEDS_7 - 1,
                    0,
                    0
                );
                _ws2812FXDevices[6][0]->getWS2812FX()->init();
                ws2812FXstates[6] = true;
            #endif
        } else {
            Serial.print("Unsupported Effects Controller: ");
            Serial.println(controllerType);
        }
    }

    PPUCEventDispatcher* eventDispatcher();

    PPUCLedBuiltInDevice* ledBuiltInDevice();

    PPUCNullDevice* nullDevice();

    PPUCWS2812FXDevice* ws2812FXDevice(int port);

    PPUCWS2812FXDevice* createWS2812FXDevice(int port, int number, int segments, int firstLED, int lastLED);

    PPUCWS2812FXDevice* ws2812FXDevice(int port, int number);

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
    PPUCWS2812FXDevice* _ws2812FXDevices[7][10];
    int ws2812FXdevices[7] = {1, 1, 1, 1, 1, 1, 1};
    bool ws2812FXstates[7] = {false, false, false, false, false, false, false};
    bool ws2812FXrunning[7] = {false, false, false, false, false, false, false};
    PPUCEffectContainer* stackEffectContainers[EFFECT_STACK_SIZE];
    int stackCounter = -1;

    int mode = 0;
};

#endif
