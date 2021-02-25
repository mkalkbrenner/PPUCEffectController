#include "PPUCRGBColorCycleEffect.h"
#include "../PPUCEffectDevices/PPUCWS2812SerialDevice.h"

void PPUCRGBColorCycleEffect::update() {
    PPUCWS2812SerialDevice* rgbDevice = (PPUCWS2812SerialDevice*) device;
    if (stage == 0) {
        color = 0xFF0000;
        rgbDevice->on();
        rgbDevice->setBrightness(255);
        ++stage;
    }

    int blue  = color & 255;
    int green = (color >> 8) & 255;
    int red   = (color >> 16) & 255;

    if (ms >= delay) {
        resetMillis();
        if (stage == 1) {
            color = rgbDevice->color(red, ++green, blue);
            rgbDevice->setColor(color);
            if (color >= 0xFFFF00) {
                ++stage;
            }
        }
        else if (stage == 2) {
            color = rgbDevice->color(red, green, ++blue);
            rgbDevice->setColor(color);
            if (color >= 0xFFFFFF) {
                ++stage;
            }
        }
        else if (stage == 3) {
            color = rgbDevice->color(--red, green, blue);
            rgbDevice->setColor(color);
            if (color <= 0x00FFFF) {
                ++stage;
            }
        }
        else if (stage == 4) {
            color = rgbDevice->color(red, --green, blue);
            rgbDevice->setColor(color);
            if (color <= 0x0000FF) {
                ++stage;
            }
        }
        else if (stage == 5) {
            color = rgbDevice->color(++red, green, blue);
            rgbDevice->setColor(color);
            if (color >= 0xFF00FF) {
                ++stage;
            }
        }
        else if (stage == 6) {
            color = rgbDevice->color(red, green, --blue);
            rgbDevice->setColor(color);
            if (color <= 0xFF0000) {
                rgbDevice->off();
                stop();
            }
        }
    }
}
