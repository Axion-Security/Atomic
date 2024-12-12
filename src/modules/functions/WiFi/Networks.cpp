#include "Networks.h"

void Networks::CheckNetwork(const String& ssid, const String& macAddress, uint8_t channel) {
    print::ClearScreen();
    print::WriteLine("Name", ssid.c_str(), true);
    print::WriteLine("MAC", macAddress.c_str(), true);
    print::WriteLine("Channel", String(channel).c_str(), true);

    const char* frequency = (channel >= 1 && channel <= 13) ? "2.4 GHz" :
                            (channel >= 36) ? "5 GHz" : "Unknown";
    print::WriteLine("Frequency", frequency, true);

    int rssi = WiFi.RSSI(channel);
    const char* signalStrength = (rssi >= -50) ? "Excellent" :
                                 (rssi >= -60) ? "Very Good" :
                                 (rssi >= -70) ? "Good" :
                                 (rssi >= -80) ? "Fair" : "Weak";
    print::WriteLine("Signal Strength", (String(rssi) + " dBm (" + signalStrength + ")").c_str(), true);
    print::WriteLine("Encryption Type", WiFi.encryptionType(channel) == WIFI_AUTH_OPEN ? "Open" : "Secured", true);
    print::WriteLine("!", Messages::anyButton(), true);

    while (buttons::WaitForButtonPress()) {}

    GetAllNetworks();
}

void Networks::GetAllNetworks() {
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
            options.emplace_back(WiFi.SSID(i).c_str(), [=] { CheckNetwork(String(WiFi.SSID(i)), String(WiFi.BSSIDstr(i)), WiFi.channel(i));
        });
        }
    }

    options.emplace_back("Go Back",     [=] { WiFiMenu::ShowMenu(); });
    print::LoopOptions(options, "WiFi Networks", 0);

    WiFi.scanDelete();
}