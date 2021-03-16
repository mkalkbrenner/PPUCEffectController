//
// Created by Markus Kalkbrenner on 14.03.21.
//

#include "PPUCGeneralIlluminationWPC.h"

// see https://forum.arduino.cc/index.php?topic=398610.0
PPUCGeneralIlluminationWPC* PPUCGeneralIlluminationWPC::giInstance = NULL;

void PPUCGeneralIlluminationWPC::start() {
    // initialize data
    for (int i = 0; i < NUM_STRINGS; i++) {
        for (int k = 0; k <= NUM_BRIGHTNESS; k++) {
            sBrightnessHist[i][k] = 0;
        }
    }

    attachInterrupt(digitalPinToInterrupt(2), PPUCGeneralIlluminationWPC::_changeD0, CHANGE);
    attachInterrupt(digitalPinToInterrupt(3), PPUCGeneralIlluminationWPC::_changeD1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(4), PPUCGeneralIlluminationWPC::_changeD2, CHANGE);
    attachInterrupt(digitalPinToInterrupt(5), PPUCGeneralIlluminationWPC::_changeD3, CHANGE);
    attachInterrupt(digitalPinToInterrupt(6), PPUCGeneralIlluminationWPC::_changeD4, CHANGE);
    attachInterrupt(digitalPinToInterrupt(12), PPUCGeneralIlluminationWPC::_changeZC, CHANGE);
}

void PPUCGeneralIlluminationWPC::stop() {
    detachInterrupt(digitalPinToInterrupt(2));
    detachInterrupt(digitalPinToInterrupt(3));
    detachInterrupt(digitalPinToInterrupt(4));
    detachInterrupt(digitalPinToInterrupt(5));
    detachInterrupt(digitalPinToInterrupt(6));
    detachInterrupt(digitalPinToInterrupt(12));
}

void PPUCGeneralIlluminationWPC::update() {
    for (int string = 0; string < NUM_STRINGS; string++) {
        if (sBrightness[string] != sBrightnessTarget[string]) {
            eventDispatcher->dispatch(new PPUCEvent(EVENT_SOURCE_GI, word(0, string + 1), sBrightnessTarget[string]));
            sBrightness[string] = sBrightnessTarget[string];
        }
    }
}

void PPUCGeneralIlluminationWPC::newBrightness(uint8_t string, uint8_t b)
{
    // Check whether the brightness has changed
    if (b <= NUM_BRIGHTNESS)
    {
        // Add the current brightness value to the histogram
        if (sBrightnessHist[string][b] < 0xff)
        {
            sBrightnessHist[string][b]++;
        }

        // Only switch when some measurements in the center of the
        // brightness interval have been seen
        if (sBrightnessHist[string][b] > BRIGHTNESS_SWITCH_THRESH)
        {
            if (b != sBrightnessTarget[string])
            {
                // store current brightness
                sBrightness[string] = sBrightnessTarget[string];

                // switch to the new brightness target value
                sBrightnessTarget[string] = b;

                //distpatch
            }

            // clear the histogram
            memset((void*)&(sBrightnessHist[string][0]), 0, NUM_BRIGHTNESS + 1);
        }
    }
}

void PPUCGeneralIlluminationWPC::_changeD0() {
    giInstance->handlePinChange(0);
}

void PPUCGeneralIlluminationWPC::_changeD1() {
    giInstance->handlePinChange(1);
}

void PPUCGeneralIlluminationWPC::_changeD2() {
    giInstance->handlePinChange(2);
}

void PPUCGeneralIlluminationWPC::_changeD3() {
    giInstance->handlePinChange(3);
}

void PPUCGeneralIlluminationWPC::_changeD4() {
    giInstance->handlePinChange(4);
}

void PPUCGeneralIlluminationWPC::handlePinChange(uint8_t giString)
{
    // What time is it?
    uint32_t t = micros();

    // Handle only once
    uint32_t dtLast = (t - sDataIntLast[giString]);
    if (dtLast > 1000)
    {
        uint8_t stringBit = (1 << giString);
        uint32_t dt = (t - sZCIntTime);
        if (dt < 10000)
        {
            // Translate delta time into brightness
            uint8_t b = dtToBrightness(dt);

            // Handle the new brightness value
            newBrightness(giString, b);
        }
        sDataIntLast[giString] = t;
        sInterruptsSeen |= stringBit;
    }
}

void PPUCGeneralIlluminationWPC::_changeZC()
{
    // What time is it?
    uint32_t t = micros();

    // Handle zero crossing interrupts

    // The zero crossing signal should appear at 100Hz. If we're closer to
    // last interrupt then this is the falling edge and we should ignore it.
    if ((t - giInstance->sZCIntTime) > 4000)
    {
        // Just remember the last zero crossing interrupt time
        giInstance->sZCIntTime = t;

        // All strings without interrupt in the past interval are either fully
        // on or off
        for (int i = 0; i < NUM_STRINGS; i++) {
            if ((giInstance->sInterruptsSeen & (1 << i)) == 0) {
                giInstance->newBrightness(i, digitalRead(2 + i) ? 0 : NUM_BRIGHTNESS);
            }
        }
        // Clear the interrupts mask
        giInstance->sInterruptsSeen = 0;
    }
}

uint8_t PPUCGeneralIlluminationWPC::dtToBrightness(uint32_t dt)
{
    // This function leaves some margin at the interval borders to account for
    // the fact the intervals are slightly overlapping and therefore a
    // unambiguous brightness determination is not always possible. In this case
    // the function returns 255.

    uint8_t b;
    if (dt < (1200-BRIGHTNESS_INTERVAL_MARGIN))
    {
        // full power, this shouldn't really happen
        b = NUM_BRIGHTNESS;
    }
    else if ((dt > (1200+BRIGHTNESS_INTERVAL_MARGIN)) &&
             (dt < (2200-BRIGHTNESS_INTERVAL_MARGIN)))
    {
        b = 6;
    }
    else if ((dt > (2200+BRIGHTNESS_INTERVAL_MARGIN)) &&
             (dt < (3200-BRIGHTNESS_INTERVAL_MARGIN)))
    {
        b = 5;
    }
    else if ((dt > (3200+BRIGHTNESS_INTERVAL_MARGIN)) &&
             (dt < (4200-BRIGHTNESS_INTERVAL_MARGIN)))
    {
        b = 4;
    }
    else if ((dt > (4200+BRIGHTNESS_INTERVAL_MARGIN)) &&
             (dt < (5200-BRIGHTNESS_INTERVAL_MARGIN)))
    {
        b = 3;
    }
    else if ((dt > (5200+BRIGHTNESS_INTERVAL_MARGIN)) &&
             (dt < (6200-BRIGHTNESS_INTERVAL_MARGIN)))
    {
        b = 2;
    }
    else if ((dt > (6200+BRIGHTNESS_INTERVAL_MARGIN)) &&
             (dt < (7200-BRIGHTNESS_INTERVAL_MARGIN)))
    {
        b = 1;
    }
    else
    {
        // invalid interval
        b = BRIGHTNESS_UNCERTAIN;
    }
    return b;
}
