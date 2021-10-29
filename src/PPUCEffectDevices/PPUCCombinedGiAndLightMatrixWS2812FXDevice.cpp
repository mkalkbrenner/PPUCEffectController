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

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToGiString(uint8_t giString, int8_t led) {
    assignLedToGiString(giString, led, ULTRAWHITE);
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToGiString(uint8_t giString, int8_t led, uint32_t color) {
    ledGIPositions[--giString][numLEDsGI[giString]] = led;
    ledGIColors[giString][numLEDsGI[giString]++] = color;
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrix(uint8_t column, uint8_t row, int8_t led) {
    assignLedToLightMatrix(column, row, led, ULTRAWHITE);
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrix(uint8_t column, uint8_t row, int8_t led, uint32_t color) {
    assignLedToLightMatrixDE(((column - 1) * 8) + row , led, color);
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrixWPC(uint8_t number, int8_t led) {
    assignLedToLightMatrixWPC(number, led, ULTRAWHITE);
    wpc = true;
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrixWPC(uint8_t number, int8_t led, uint32_t color) {
    assignLedToLightMatrix(number / 10 % 10, number % 10, led, color);
    wpc = true;
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrixDE(uint8_t number, int8_t led) {
    assignLedToLightMatrixDE(number, led, WHITE);
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::assignLedToLightMatrixDE(uint8_t number, int8_t led, uint32_t color) {
    --number;
    for (int i = 0; i < PPUC_MAX_LEDS_PER_LIGHT; i++) {
        if (ledLightMatrixPositions[number][i] == -1) {
            ledLightMatrixPositions[number][i] = led;
            ledLightMatrixColors[number][i] = color;
            break;
        }
    }
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::handleEvent(PPUCEvent* event) {
    if (!effectRunning) {
        if (event->sourceId == EVENT_SOURCE_GI) {
            uint8_t giString = event->eventId - 1;
            uint8_t giBrightness = event->value > 0 ? 1 << event->value : 0; // 2^value
            for (int i = 0; i <= numLEDsGI[giString]; i++) {
                // @todo apply WPC GI brightness.
                ws2812FX->setPixelColor(ledGIPositions[giString][i], ledGIColors[giString][i]);
            }
        }
        else if (event->sourceId == EVENT_SOURCE_LIGHT) {
            //char system = (event->eventId & 0xFF00) >> 8;
            //uint8_t number = event->eventId & 0x00FF;

            uint8_t number = event->eventId;

            if (wpc) {
                // WPC
                uint8_t column = number / 10 % 10;
                uint8_t row = number % 10;
                number = ((column - 1) * 8) + row;
            }

            --number;
            bool on = (bool) event->value;

            for (int i = 0; i < PPUC_MAX_LEDS_PER_LIGHT; i++) {
                if (ledLightMatrixPositions[number][i] >= 0) {
                    if (on && msHeatUp == 0) {
                        ws2812FX->setPixelColor(ledLightMatrixPositions[number][i], ledLightMatrixColors[number][i]);
                    }
                    else if (!on && msAfterGlow == 0) {
                        ws2812FX->setPixelColor(ledLightMatrixPositions[number][i], RGBW_BLACK);
                    }
                    else if (i == 0) {
                        if (on) {
                            if (heatUp[number] == 0 && afterGlow[number] == 0) {
                                heatUp[number] = millis();
                            } else if (afterGlow[number] > 0) {
                                // There's still an after glow effect running. Start heat up from current value.
                                byte value = wavePWMAfterGlow->getExponentialValue(millis() - afterGlow[number] + msAfterGlow);
                                afterGlow[number] = 0;
                                for (int ms = 1; ms <= msHeatUp; ms++) {
                                    if (wavePWMHeatUp->getExponentialValue(ms) >= value) {
                                        heatUp[number] = millis() - ms;
                                        break;
                                    }
                                }
                                // safety net
                                if (heatUp[number] == 0) {
                                    heatUp[number] = millis() - msHeatUp + 1;
                                }
                            }
                        } else {
                            if (afterGlow[number] == 0 && heatUp[number] == 0) {
                                afterGlow[number] = millis();
                            } else if (heatUp[number] > 0) {
                                // There's still a heat up effect running. Start after glow from current value.
                                byte value = wavePWMHeatUp->getExponentialValue(millis() - heatUp[number]);
                                heatUp[number] = 0;
                                for (int ms = msAfterGlow; ms <= (msAfterGlow * 2); ms++) {
                                    if (wavePWMAfterGlow->getExponentialValue(ms) <= value) {
                                        afterGlow[number] = millis() - ms;
                                        break;
                                    }
                                }
                                // safety net
                                if (afterGlow[number] == 0) {
                                    afterGlow[number] = millis() - (2 * msAfterGlow) + 1;
                                }
                            }
                        }

                        // terminate the loop
                        return;
                    }
                }
            }
        }
    }
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::updateAfterGlow() {
    for (int number = 0; number < PPUC_LIGHT_MATRIX_SIZE; number++) {
        byte glowBrightness;
        if (heatUp[number] > 0) {
            if ((millis() - heatUp[number]) >= msHeatUp) {
                heatUp[number] = 0;
                for (int i = 0; i < PPUC_MAX_LEDS_PER_LIGHT; i++) {
                    if (ledLightMatrixPositions[number][i] != -1) {
                        ws2812FX->setPixelColor(ledLightMatrixPositions[number][i], ledLightMatrixColors[number][i]);
                    }
                }
            }
            else {
                glowBrightness = wavePWMHeatUp->getExponentialValue(millis() - heatUp[number]);
            }
        }
        else if (afterGlow[number] > 0) {
            if ((millis() - afterGlow[number]) >= msAfterGlow) {
                afterGlow[number] = 0;
                for (int i = 0; i < PPUC_MAX_LEDS_PER_LIGHT; i++) {
                    if (ledLightMatrixPositions[number][i] != -1) {
                        ws2812FX->setPixelColor(ledLightMatrixPositions[number][i], RGBW_BLACK);
                    }
                }
            }
            else {
                glowBrightness = wavePWMAfterGlow->getExponentialValue(millis() - afterGlow[number] + msAfterGlow);
            }
        }

        if (heatUp[number] > 0 || afterGlow[number] > 0) {
            for (int i = 0; i < PPUC_MAX_LEDS_PER_LIGHT; i++) {
                if (ledLightMatrixPositions[number][i] != -1) {
                    uint8_t w = (ledLightMatrixColors[number][i] >> 24) & 0xFF;
                    uint8_t r = (ledLightMatrixColors[number][i] >> 16) & 0xFF;
                    uint8_t g = (ledLightMatrixColors[number][i] >> 8) & 0xFF;
                    uint8_t b = ledLightMatrixColors[number][i] & 0xFF;

                    // uint32_t for more space during the operation
                    uint32_t mult = (glowBrightness * getBrightness() / 255) + 1;
                    b = (b * mult) >> 8;
                    g = (g * mult) >> 8;
                    r = (r * mult) >> 8;
                    w = (w * mult) >> 8;

                    ws2812FX->setPixelColor(ledLightMatrixPositions[number][i], r, g, b, w);
                }
            }
        }
    }
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::setHeatUp() {
    setHeatUp(30);
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::setAfterGlow() {
    setAfterGlow(400);
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::setHeatUp(int ms) {
    wavePWMHeatUp->setup(ms * 2);
    msHeatUp = ms;
}

void PPUCCombinedGiAndLightMatrixWS2812FXDevice::setAfterGlow(int ms) {
    wavePWMAfterGlow->setup(ms * 2);
    msAfterGlow = ms;
}
