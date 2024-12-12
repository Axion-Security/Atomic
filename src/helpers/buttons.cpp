#include "buttons.h"

bool buttons::isBtnBPressed() {
    M5.update();
    return M5.BtnB.wasPressed();
}

bool buttons::isBtnAPressed() {
    M5.update();
    return M5.BtnA.wasPressed();
}

bool buttons::isBtnPWRPressed() {
    M5.update();
    return M5.BtnPWR.wasPressed();
}

bool buttons::WaitForButtonPress() {
    return !isBtnBPressed() && !isBtnAPressed() && !isBtnPWRPressed();
}
