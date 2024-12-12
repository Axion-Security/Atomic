#include "boot.h"

void boot::BootScreen()
{
    print::ClearScreen();

    int padding = 10;
    int cornerRadius = 15;

    M5.Display.drawRoundRect(
      padding,
      padding,
      M5.Display.width() - 2 * padding,
      M5.Display.height() - 2 * padding,
      cornerRadius,
      DARKCYAN
    );

    int screenWidth = M5.Display.width();
    int screenHeight = M5.Display.height();

    int topFontWidth = 6;
    int middleFontWidth = 18;
    int bottomFontWidth = 6;

    const char* topText = "Pentesting Solutions.";
    const char* middleText = "< Atomic >";
    const char* bottomText = "Quantum Security Firmware";

    int topTextLength = strlen(topText) * topFontWidth;
    int middleTextLength = strlen(middleText) * middleFontWidth;
    int bottomTextLength = strlen(bottomText) * bottomFontWidth;

    int topY = padding + 10;
    int middleY = (screenHeight / 2) - 12;
    int bottomY = screenHeight - padding - 10;

    M5.Display.setTextSize(1);
    M5.Display.setTextColor(WHITE);
    M5.Display.setCursor((screenWidth - topTextLength) / 2, topY);
    M5.Display.print(topText);

    M5.Display.setTextSize(3);
    M5.Display.setTextColor(CYAN);
    M5.Display.setCursor((screenWidth - middleTextLength) / 2, middleY);
    M5.Display.print(middleText);

    M5.Display.setTextSize(1);
    M5.Display.setTextColor(WHITE);
    M5.Display.setCursor((screenWidth - bottomTextLength) / 2, bottomY);
    M5.Display.print(bottomText);

    delay(3500);
}