#include "buttons.h"

/*
 *  BtnB = Bottom Right
 *  BtnA = Middle
 *  BtnPWR = Top Left
*/

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
    return !buttons::isBtnBPressed() && !buttons::isBtnAPressed() && !buttons::isBtnPWRPressed();
}
