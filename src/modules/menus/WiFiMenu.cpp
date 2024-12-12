#include "WiFiMenu.h"

void WiFiMenu::ShowMenu() {
    print::ClearScreen();
    std::vector<std::pair<std::string, std::function<void()>>> options = {
        {"WiFi Networks", [=] { Networks::GetAllNetworks(); }},
        {"Evil Portal" , [=] { EvilPortal::Start(); }},
        {"Main Menu", [] { menu::MainMenu(); }},
    };
    print::LoopOptions(options, "WiFi Menu", 0);
}