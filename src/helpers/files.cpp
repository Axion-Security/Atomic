#include "files.h"

String files::ls(const String& path = "/") {
    print::ClearScreen();
    std::vector<std::pair<std::string, std::function<void()>>> options;

    File root = SPIFFS.open(path);
    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            options.emplace_back(file.name(), [=] { ls(file.name()); });
        } else {
            options.emplace_back(file.name(), [=] { return readFile(file.path()); });
        }
        file.close();
        file = root.openNextFile();
    }

    print::LoopOptions(options, std::string("Directory: ") + path.c_str(), 0);
    return "";
}

String files::readFile(const char* path) {
    File file = SPIFFS.open(path);
    String content = "";

    if (!file) {
        content = "Failed to open file for reading";
        return content;
    }

    while (file.available()) {
        content += static_cast<char>(file.read());
    }
    return content;
}

void files::writeFile(const char* path, const char* message) {
    File file = SPIFFS.open(path, FILE_WRITE);

    if (!file) {
        Serial.println("Failed to open file for writing");
        return;
    }

    file.println(message);
    file.close();
    Serial.println("File written successfully");
}

void files::deleteFile(const char* path) {
    if (SPIFFS.remove(path)) {
        Serial.println("File deleted successfully");
    } else {
        Serial.println("Failed to delete file");
    }
}

void files::format() {
    SPIFFS.format();
}