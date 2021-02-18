#include "PPUCNullEffect.h"

void PPUCNullEffect::update() {
    device->reset();
    stop();
}
