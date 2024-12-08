#ifndef SETTINGS_H
#define SETTINGS_H

// Standard library headers
#include <M5Unified.h>

// Project-specific headers
#include "interface/print.h"
#include "interface/buttons.h"
#include "modules/menus/SettingsMenu.h"

class Settings {
    public:
        static void DisplayBatteryInformation();
        static void PowerOff();
        static void DeepSleep();
        static void LightSpeed();
};

#endif //SETTINGS_H
