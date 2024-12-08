#include <main.h>
#include <modules/menu.h>

bool showMenu = true;

void setup() {
  auto cfg = M5.config();
  cfg.internal_imu = true;
  cfg.serial_baudrate = 115200;
  cfg.led_brightness  = 100;
  M5.begin(cfg);

  M5.Display.setRotation(3);

  boot::BootScreen();
  delay(3000);
}

void loop() {
  menu::MainMenu();
}
