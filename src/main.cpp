#include <main.h>
#include <Arduino.h>
#include <helpers/files.h>

void setup()
{
    auto cfg = m5::M5Unified::config();
    cfg.internal_imu = true;
    cfg.serial_baudrate = 115200;
    cfg.led_brightness = 100 * 1.55;
    cfg.clear_display = true;
    M5.begin(cfg);

    M5.Display.setRotation(3);

    if (!files::begin())
    {
        print::ClearScreen();
        print::WriteLine("!", "Unable to initialize file system.", true);
        delay(5000);
        M5.Power.powerOff();
    }

    delay(3500);

    boot::BootScreen();
}

void loop()
{
    menu::MainMenu();
}