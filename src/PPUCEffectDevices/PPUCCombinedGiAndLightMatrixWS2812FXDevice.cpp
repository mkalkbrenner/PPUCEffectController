#include "PPUCCombinedGiAndLightMatrixWS2812FXDevice.h"

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::on() {
    PPUCWS2812FXDevice::on();
    effectRunning = true;
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::off() {
    effectRunning = false;
    // No stop. Just reset to quit effects and return to standard GI and Light Matrix operation.
    reset();
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToGiString(uint8_t giString, uint8_t led) {
    assignLedToGiString(giString, led, WHITE);
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToGiString(uint8_t giString, uint8_t led, uint32_t color) {
    ledGIPositions[--giString][numLEDsGI[giString]] = led;
    ledGIColors[giString][numLEDsGI[giString]++] = color;
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrix(uint8_t column, uint8_t row, uint8_t led) {
    assignLedToLightMatrix(column, row, led, WHITE);
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrix(uint8_t column, uint8_t row, uint8_t led, uint32_t color) {
    PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrixDE(((column - 1) * 8) + row , led, color);
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrixWPC(uint8_t number, uint8_t led) {
    assignLedToLightMatrixWPC(number, led, WHITE);
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrixWPC(uint8_t number, uint8_t led, uint32_t color) {
    assignLedToLightMatrix(number / 10 % 10, number % 10, led, color);
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrixDE(uint8_t number, uint8_t led) {
    assignLedToLightMatrixDE(number, led, WHITE);
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrixDE(uint8_t number, uint8_t led, uint32_t color) {
    --number;
    for (int i = 0; i < PPUC_MAX_LEDS_PER_LIGHT; i++) {
        if (ledLightMatrixPositions[number][i] == 0) {
            ledLightMatrixPositions[number][i] = led;
            ledLightMatrixColors[number][i] = color;
        }
    }
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::handleEvent(PPUCEvent* event) {
    if (!effectRunning) {
        if (event->sourceId == EVENT_SOURCE_GI) {
            uint8_t giString = event->eventId - 1;
            uint8_t brightness = event->value > 0 ? 1 << event->value : 0; // 2^value
            for (int i = 0; i <= numLEDsGI[giString]; i++) {
                // @todo apply brightness.
                ws2812FX->setPixelColor(ledGIPositions[giString][i], ledGIColors[giString][i]);
            }
        }
        else if (event->sourceId == EVENT_SOURCE_LIGHT) {
            char system = (event->eventId & 0xFF00) >> 8;
            uint8_t number = event->eventId & 0x00FF;

            if (system == 'W') {
                // WPC
                uint8_t column = number / 10 % 10;
                uint8_t row = number % 10;
                number = ((column - 1) * 8) + row;
            }

            --number;
            bool on = (bool) event->value;

            for (int i = 0; i < PPUC_MAX_LEDS_PER_LIGHT; i++) {
                if (ledLightMatrixPositions[number][i]) {
                    ws2812FX->setPixelColor(ledLightMatrixPositions[number][i], on ? ledLightMatrixColors[number][i] : 0);
                }
            }
        }
    }
}