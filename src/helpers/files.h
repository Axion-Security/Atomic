#ifndef FILES_H
#define FILES_H

#include <SPIFFS.h>
#include "print.h"

class files {
    public:
        static bool begin() {
            return SPIFFS.begin(true);
        }

        static String ls(const String& path);
        static String readFile(const char* path);
        static void writeFile(const char* path, const char* message);
        static void deleteFile(const char* path);
        static void format();
};

#endif //FILES_H
