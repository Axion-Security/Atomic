#include "menu.h"

#include <interface/print.h>
#include <modules/menus/WiFiMenu.h>

#include "menus/SettingsMenu.h"

void menu::MainMenu() {
    print::ClearScreen();
    std::vector<std::pair<std::string, std::function<void()>>> options = {
        {"WiFi", [=] { WiFiMenu::ShowMenu(); }},
        {"Settings", [=] { SettingsMenu::ShowMenu(); }},
        {"Deep Sleep", [=] { M5.Power.deepSleep(); }},
    };
    print::LoopOptions(options, "Main Menu", 0);
}
