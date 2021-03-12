/*
  PPUCEffectControllerTestButtons.h
  Created by Markus Kalkbrenner, 2021.

  Play more pinball!
*/

#ifndef PPUCEffectControllerTestButtons_h
#define PPUCEffectControllerTestButtons_h

#include <Arduino.h>
#include <PPUCEvent.h>
#include <PPUCEventDispatcher.h>

class PPUCEffectControllerTestButtons {
public:
    PPUCEffectControllerTestButtons(PPUCEventDispatcher* eD);

    void update();

protected:
    PPUCEventDispatcher* eventDispatcher;
    bool button1;
    bool button2;
};

#endif
