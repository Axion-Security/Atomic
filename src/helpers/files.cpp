#include "files.h"
#include <SD.h>
#include <SPI.h>


// SD Card Module Wiring
// M5Stack    SD Card Module
// 5V         VCC
// GND        GND
// GND        CS
// G0         SCK
// G26        MOSI
// G36        MISO

#define SDCARD_CS    14
#define SDCARD_SCK   0
#define SDCARD_MOSI  26
#define SDCARD_MISO  25

bool files::hasSD = false;

void files::begin() {
    SPI.begin(SDCARD_SCK, SDCARD_MISO, SDCARD_MOSI, SDCARD_CS);
    if (SD.begin(SDCARD_CS)) {
        hasSD = true;
        Serial.println("SD card initialized.");
    } else {
        hasSD = false;
        if (!SPIFFS.begin(true)) {
            Serial.println("SPIFFS initialization failed!");
        } else {
            Serial.println("Using SPIFFS.");
        }
    }
}

// ToDo: Fix: Function is not returning the content of the file.
void files::ls(const String& path, const std::function<void(const String&)>& callback) {
    print::ClearScreen();
    std::vector<std::pair<std::string, std::function<void()>>> options;

    if (hasSD) {
        File root = SD.open(path);
        if (!root || !root.isDirectory()) {
            return;
        }

        File entry = root.openNextFile();
        while (entry) {
            String entryName = entry.name();
            entryName.trim();
            if (entryName.endsWith("/")) {
                entryName = entryName.substring(0, entryName.length() - 1);
            }

            String fullPath;
            if (path == "/") {
                fullPath = "/" + entryName;
            } else {
                fullPath = path + "/" + entryName;
            }

            if (entry.isDirectory()) {
                options.emplace_back(entryName.c_str(), [=] { ls(fullPath, callback); });
            } else {
                options.emplace_back(entryName.c_str(), [=] { callback(readFile(fullPath.c_str())); });
            }

            entry.close();
            entry = root.openNextFile();
        }
        root.close();
    } else {
        File root = SPIFFS.open(path);
        File file = root.openNextFile();
        while (file) {
            if (file.isDirectory()) {
                options.emplace_back(file.name(), [=] { ls(file.name(), callback); });
            } else {
                options.emplace_back(file.name(), [=] { callback(readFile(file.path())); });
            }
            file.close();
            file = root.openNextFile();
        }
    }

    print::LoopOptions(options, std::string("Directory: ") + path.c_str(), 0);
}

String files::readFile(const char* path) {
    String content;
    if (hasSD) {
        File file = SD.open(path);
        if (!file) {
            return "Failed to open file for reading";
        }
        while (file.available()) {
            content += static_cast<char>(file.read());
        }
        file.close();
    } else {
        File file = SPIFFS.open(path);
        if (!file) {
            content = "Failed to open file for reading";
            return content;
        }
        while (file.available()) {
            content += static_cast<char>(file.read());
        }
        file.close();
    }
    return content;
}

void files::writeFile(const char* path, const char* message) {
    if (hasSD) {
        File file = SD.open(path, FILE_WRITE);
        if (!file) {
            Serial.println("Failed to open file for writing");
            return;
        }
        file.println(message);
        file.close();
        Serial.println("File written successfully");
    } else {
        File file = SPIFFS.open(path, FILE_WRITE);
        if (!file) {
            Serial.println("Failed to open file for writing");
            return;
        }
        file.println(message);
        file.close();
        Serial.println("File written successfully");
    }
}

void files::deleteFile(const char* path) {
    if (hasSD) {
        if (SD.remove(path)) {
            Serial.println("File deleted successfully");
        } else {
            Serial.println("Failed to delete file");
        }
    } else {
        if (SPIFFS.remove(path)) {
            Serial.println("File deleted successfully");
        } else {
            Serial.println("Failed to delete file");
        }
    }
}

void files::format() {
    if (!hasSD) {
        SPIFFS.format();
        Serial.println("Filesystem formatted");
    } else {
        Serial.println("Format not supported for SD card");
    }
}