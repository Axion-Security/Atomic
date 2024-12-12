#ifndef WIFIMENU_H
#define WIFIMENU_H

#include "WiFi.h"
#include "helpers/print.h"
#include "helpers/buttons.h"
#include "modules/menu.h"
#include <modules/functions/WiFi/EvilPortal.h>
#include "modules/functions/WiFi/Networks.h"

class WiFiMenu {
    public:
        static void ShowMenu();
};

#endif //WIFIMENU_H
