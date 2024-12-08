#include "Networks.h"

void Networks::CheckNetwork(const String& ssid, const String& macAddress, uint8_t channel) {
    print::ClearScreen();
    print::WriteLine("Name", ssid.c_str(), true);
    print::WriteLine("MAC", macAddress.c_str(), true);
    print::WriteLine("Channel", String(channel).c_str(), true);
    print::WriteLine(
        "Frequency",
        (channel >= 1 && channel <= 13) ? "2.4 GHz" :
        (channel == 14) ? "2.4 GHz (Japan only)" :
        (channel >= 36) ? "5 GHz" : "Unknown",
        true
    );
    const int rssi = WiFi.RSSI(channel);
    std::string signalStrength;
    if (rssi >= -50) {
        signalStrength = "Excellent";
    } else if (rssi >= -60) {
        signalStrength = "Very Good";
    } else if (rssi >= -70) {
        signalStrength = "Good";
    } else if (rssi >= -80) {
        signalStrength = "Fair";
    } else {
        signalStrength = "Weak";
    }
    print::WriteLine("Signal Strength", (String(rssi) + " dBm (" + signalStrength.c_str() + ")").c_str(), true);
    print::WriteLine("Encryption Type", WiFi.encryptionType(channel) == WIFI_AUTH_OPEN ? "Open" : "Secured", true);
    print::WriteLine("!", "Press any button to go back", true);

    while (buttons::WaitForButtonPress()) {
    }

    WiFiMenu::ListAPs();
}