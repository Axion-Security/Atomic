#include "Settings.h"

void Settings::DisplayBatteryInformation() {
    print::ClearScreen();
    print::WriteLine("Battery Level", String(M5.Power.getBatteryLevel()) + "%", true);
    print::WriteLine("Charging", M5.Power.isCharging() ? "Yes" : "No", true);
    print::WriteLine("Voltage", String(M5.Power.getBatteryVoltage() / 1000.0) + "V", true);

    print::WriteLine("!", Messages::anyButton(), true);

    while (buttons::WaitForButtonPress()) {}

    SettingsMenu::ShowMenu();
}

void Settings::PowerOff()
{
    M5.Power.powerOff();
}

void Settings::DeepSleep()
{
    M5.Power.deepSleep();
}

void Settings::LightSpeed()
{
    M5.Power.lightSleep();
}

void Settings::Reboot()
{
    ESP.restart();
}