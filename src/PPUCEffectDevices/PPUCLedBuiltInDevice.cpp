#include "PPUCLedBuiltInDevice.h"

void PPUCLedBuiltInDevice::on() {
    digitalWrite(LED_BUILTIN, HIGH);
}

void PPUCLedBuiltInDevice::reset() {
    digitalWrite(LED_BUILTIN, LOW);
}
