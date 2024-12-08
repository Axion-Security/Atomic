#include "Settings.h"

void Settings::DisplayBatteryInformation() {
    print::ClearScreen();
    print::WriteLine("Battery Level", String(M5.Power.getBatteryLevel()), true);

    print::WriteLine("!", "Press any button to go back", true);
    while (buttons::WaitForButtonPress()) { }

    SettingsMenu::ShowMenu();
}

void Settings::PowerOff()
{
    print::ClearScreen();
    print::WriteLine("?", "Turns off the power duh.", true);

    print::WriteLine("!", "Press any button to go back", true);
    while (buttons::WaitForButtonPress()) { }

    M5.Power.powerOff();
}

void Settings::DeepSleep()
{
    print::ClearScreen();
    print::WriteLine("?", "When a port state changes. Upon wake-up, the CPU restarts.", true);

    print::WriteLine("!", "Press any button to go back", true);
    while (buttons::WaitForButtonPress()) { }

    M5.Power.deepSleep();
}

void Settings::LightSpeed()
{
    print::ClearScreen();
    print::WriteLine("?", "It wakes up after a specified time or when a port changes.", true);

    print::WriteLine("!", "Press any button to go back", true);
    while (buttons::WaitForButtonPress()) { }

    M5.Power.lightSleep();
}