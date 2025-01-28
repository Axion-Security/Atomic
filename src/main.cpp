#include <main.h>
#include <Arduino.h>
#include <helpers/files.h>

void setup()
{
    auto cfg = m5::M5Unified::config();
    cfg.internal_imu = true;
    cfg.serial_baudrate = 115200;

    M5.begin(cfg);

    M5.Display.setRotation(3);

    files::begin();
    boot::BootScreen();
}

void loop()
{
    menu::MainMenu();
}