// Standard library headers
#include <WiFi.h>

// Project-specific headers
#include "WiFiMenu.h"
#include "interface/print.h"
#include "interface/buttons.h"
#include "modules/menu.h"

// External module headers
#include "modules/functions/WiFi/Networks.h"

WiFiClass WiFi;

void WiFiMenu::ShowMenu() {
    print::ClearScreen();
    std::vector<std::pair<std::string, std::function<void()>>> options = {
        {"List AP's", [=] { ListAPs(); }},
        {"Main Menu", [] { menu::MainMenu(); }},
    };
    print::LoopOptions(options, "WiFi Menu", 0);
}

void WiFiMenu::ListAPs() {
    std::vector<std::pair<std::string, std::function<void()>>> options;
    print::ClearScreen();

    WiFiClass::mode(WIFI_STA);
    WiFi.disconnect();

    print::WriteLine("?", "Scanning for WiFi networks...",  true);

    const int networks = WiFi.scanNetworks();

    print::ClearScreen();

    if (networks == 0) {
        print::WriteLine("!", "No networks found", true);
    } else {
        for (int i = 0; i < networks; ++i) {
                options.emplace_back(WiFi.SSID(i).c_str(), [=]() {
                Networks::CheckNetwork(String(WiFi.SSID(i)), String(WiFi.BSSIDstr(i)), WiFi.channel(i));
            });
        }
    }

    options.emplace_back("Go Back",     [=]() { ShowMenu(); });
    print::LoopOptions(options, "WiFi Networks", 0);

    WiFi.scanDelete();
}