#include "PPUCRGBColorCycleEffect.h"
#include "../PPUCEffectDevices/PPUCWS2812SerialDevice.h"

void PPUCRGBColorCycleEffect::update() {
    PPUCWS2812SerialDevice* rgbDevice = (PPUCWS2812SerialDevice*) device;
    if (stage == 0) {
        color = 0x0;
        rgbDevice->on();
        ++stage;
    }

    if (ms >= delay) {
        resetMillis();
        if (stage == 1) {
            ++color;
            rgbDevice->setColor(color);
            if (color >= 0xFFFFFF) {
                ++stage;
            }
        }
        else if (stage == 2) {
            --color;
            rgbDevice->setColor(color);
            if (color <= 0) {
                rgbDevice->off();
                stop();
            }
        }
    }
}
