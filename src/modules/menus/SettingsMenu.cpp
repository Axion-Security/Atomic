#include "SettingsMenu.h"

void SettingsMenu::ShowMenu() {
    print::ClearScreen();
    std::vector<std::pair<std::string, std::function<void()>>> options = {
        {"Battery Information", [=] { Settings::DisplayBatteryInformation(); }},
        {"Power Off", [=] { Settings::PowerOff(); }},
        {"Deep Sleep", [=] { Settings::DeepSleep(); }},
        {"Light Sleep", [=] { Settings::LightSpeed(); }},
        {"Reboot", [=] { Settings::Reboot(); }},
        {"Main Menu", [] { menu::MainMenu(); }},
    };
    print::LoopOptions(options, "WiFi Menu", 0);
}
