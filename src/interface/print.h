#ifndef PRINT_H
#define PRINT_H

#include <M5Unified.h>
#include <map>

class print {
    public:
        static void ClearScreen();
        static void Write(const char* message);
        static void WriteLine(const String& option, const String& value, bool newLine);
        static bool isNumber(const String& str);
        static void CenteredPrint(const char* message, int textSize = 2);
        static void LoopOptions(std::vector<std::pair<std::string, std::function<void()>>>& options, const std::string& title, int maxVisibleOptions);

    private:
        static void parseAndPrint(const char* message, bool newLine);
        static void WriteLineWithManualColoring();
        static void defaultPrintSettings();
        static int getColorFromTag(const String& tag);
};

#endif // PRINT_H
