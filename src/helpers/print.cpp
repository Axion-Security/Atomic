#include "print.h"

constexpr int DefaultTextSize = 1;
constexpr int DefaultCursorX = 7;
constexpr uint16_t DefaultTextColor = WHITE;

void print::defaultPrintSettings() {
    M5.Display.setCursor(DefaultCursorX, M5.Display.getCursorY() + 7);
    M5.Display.setTextColor(DefaultTextColor);
    M5.Display.setTextSize(DefaultTextSize);
}

void print::ClearScreen() {
    defaultPrintSettings();
    M5.Display.setCursor(0, 0);
    M5.Display.fillScreen(BLACK);
}

void print::WriteLine(const String& option, const String& value, bool newLine = true) {
    defaultPrintSettings();
    std::map<String, uint16_t> colorOptions = {
        {"!", RED},
        {"?", CYAN},
        {"~", YELLOW},
        {">", MAGENTA}
    };

    M5.Display.setTextColor(DARKGREY);
    M5.Display.print("[");

    uint16_t optionColor = colorOptions.count(option) > 0 ? colorOptions[option] : (isNumber(option) ? GREEN : CYAN);
    M5.Display.setTextColor(optionColor);
    M5.Display.print(option);

    M5.Display.setTextColor(DARKGREY);
    M5.Display.print("] ");

    M5.Display.setTextColor(WHITE);

    if (newLine) {
        M5.Display.println(value);
    } else {
        M5.Display.print(value);
    }
}

bool print::isNumber(const String& str) {
    for (unsigned int i = 0; i < str.length(); ++i) {
        if (!isDigit(str[i])) {
            return false;
        }
    }
    return true;
}

void print::CenteredPrint(const char* message, int textSize) {
    defaultPrintSettings();

    M5.Display.setTextSize(textSize);

    int16_t textWidth = M5.Display.textWidth(message);

    int x = (M5.Display.width() - textWidth) / 2;
    int y = M5.Display.getCursorY() + 2;

    M5.Display.setCursor(x, y);
    M5.Display.println(message);
}

void print::LoopOptions(std::vector<std::pair<std::string, std::function<void()>>>& options, const std::string& title = "", const int maxVisibleOptions = 0) {
    defaultPrintSettings();
    static int currentOption = 0;
    int scrollOffset = 0;

    currentOption = 0;
    scrollOffset = 0;

    auto displayOptions = [&]() {
        ClearScreen();
        if (!title.empty()) {
            WriteLine("~", title.c_str(), true);
        }

        int visibleOptions = std::min(maxVisibleOptions, static_cast<int>(options.size()) - scrollOffset);
        if (visibleOptions == 0) // unlimited options
        {
            for (int i = 0; i < options.size(); ++i) {
                if (i == currentOption) {
                    WriteLine(">", options[i].first.c_str());
                } else {
                    WriteLine(String(i), options[i].first.c_str());
                }
            }
        } else
        {
            for (int i = 0; i < visibleOptions; ++i) {
                if (i + scrollOffset == currentOption) {
                    WriteLine(">", options[i + scrollOffset].first.c_str());

                } else {
                    WriteLine(String(i), options[i + scrollOffset].first.c_str());
                }
            }
        }
    };

    displayOptions();

    while (true) {
        M5.update();

        if (M5.BtnPWR.wasPressed()) {
            M5.Display.fillScreen(BLACK);
            if (currentOption > 0) {
                currentOption--;
            } else {
                currentOption = options.size() - 1;
            }

            if (currentOption < scrollOffset) {
                scrollOffset = currentOption;
            } else if (currentOption >= scrollOffset + maxVisibleOptions) {
                scrollOffset = currentOption - maxVisibleOptions + 1;
            }

            displayOptions();
        }

        if (M5.BtnB.wasPressed()) {
            M5.Display.fillScreen(BLACK);
            currentOption = (currentOption + 1) % options.size();

            if (currentOption < scrollOffset) {
                scrollOffset = currentOption;
            } else if (currentOption >= scrollOffset + maxVisibleOptions) {
                scrollOffset = currentOption - maxVisibleOptions + 1;
            }

            displayOptions();
        }

        if (M5.BtnA.wasPressed()) {
            options[currentOption].second();
        }

        if (M5.BtnPWR.isHolding())
        {

        }

        delay(100);
    }
}
