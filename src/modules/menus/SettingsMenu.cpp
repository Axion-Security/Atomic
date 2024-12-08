#include "SettingsMenu.h"

#include <interface/print.h>
#include <modules/menu.h>
#include "modules/functions/Settings/Settings.h"

void SettingsMenu::ShowMenu() {
    print::ClearScreen();
    std::vector<std::pair<std::string, std::function<void()>>> options = {
        {"Battery Information", [=] { Settings::DisplayBatteryInformation(); }},
        {"Power Off", [=] { Settings::PowerOff(); }},
        {"Deep Sleep", [=] { Settings::DeepSleep(); }},
        {"Light Sleep", [=] { Settings::LightSpeed(); }},
        {"Main Menu", [] { menu::MainMenu(); }},
    };
    print::LoopOptions(options, "WiFi Menu", 0);
}
