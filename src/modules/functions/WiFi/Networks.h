#ifndef NETWORKS_H
#define NETWORKS_H

#include <WiFi.h>
#include "modules/menus/WiFiMenu.h"
#include "modules/resources/Messages.h"
#include "helpers/print.h"
#include "helpers/buttons.h"

class Networks {
    public:
        static void CheckNetwork(const String& ssid, const String& macAddress, uint8_t channel);
        static void GetAllNetworks();
};

#endif // NETWORKS_H