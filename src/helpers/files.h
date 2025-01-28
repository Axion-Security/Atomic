#ifndef FILES_H
#define FILES_H

#include <SPIFFS.h>
#include "print.h"

class files {
    public:

        static bool hasSD;
        static String currentContent;
        static void begin();
        static void ls(const String& path, const std::function<void(const String&)>& callback);
        static String readFile(const char* path);
        static void writeFile(const char* path, const char* message);
        static void deleteFile(const char* path);
        static void format();
};

#endif //FILES_H
