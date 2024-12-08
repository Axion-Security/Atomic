#ifndef BUTTONS_H
#define BUTTONS_H

#include <M5Unified.h>

class buttons {
    public:
        static bool isBtnBPressed();
        static bool isBtnAPressed();
        static bool isBtnPWRPressed();
        static bool WaitForButtonPress();
};

#endif //BUTTONS_H
