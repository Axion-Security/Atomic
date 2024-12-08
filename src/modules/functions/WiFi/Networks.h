#ifndef NETWORKS_H
#define NETWORKS_H

// Standard library headers
#include <WiFi.h>

// Project-specific headers
#include "modules/menus/WiFiMenu.h"
#include "interface/print.h"
#include "interface/buttons.h"

class Networks {
    public:
        static void CheckNetwork(const String& ssid, const String& macAddress, uint8_t channel);
};

#endif // NETWORKS_H