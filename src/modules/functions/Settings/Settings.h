#ifndef SETTINGS_H
#define SETTINGS_H

#include <M5Unified.h>
#include "helpers/print.h"
#include "helpers/buttons.h"
#include "modules/menus/SettingsMenu.h"
#include "modules/resources/Messages.h"

class Settings {
    public:
        static void DisplayBatteryInformation();
        static void PowerOff();
        static void DeepSleep();
        static void LightSpeed();
        static void Reboot();
};

#endif //SETTINGS_H
