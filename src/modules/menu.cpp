#include "menu.h"

void menu::MainMenu() {
    print::ClearScreen();
    std::vector<std::pair<std::string, std::function<void()>>> options = {
        {"WiFi", [=] { WiFiMenu::ShowMenu(); }},
        {"Settings", [=] { SettingsMenu::ShowMenu(); }},
    };
    print::LoopOptions(options, "Main Menu", 0);
}