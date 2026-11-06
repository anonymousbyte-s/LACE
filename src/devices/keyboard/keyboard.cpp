#include "keyboard.h"

const deviceButton KEY_A{1 << 0, 0};
const deviceButton KEY_B{1 << 1, 0};
const deviceButton KEY_C{1 << 2, 0};
const deviceButton KEY_D{1 << 3, 0};
const deviceButton KEY_E{1 << 4, 0};
const deviceButton KEY_F{1 << 5, 0};
const deviceButton KEY_G{1 << 6, 0};
const deviceButton KEY_H{1 << 7, 0};
const deviceButton KEY_I{1 << 0, 1};
const deviceButton KEY_J{1 << 1, 1};
const deviceButton KEY_K{1 << 2, 1};
const deviceButton KEY_L{1 << 3, 1};
const deviceButton KEY_M{1 << 4, 1};
const deviceButton KEY_N{1 << 5, 1};
const deviceButton KEY_O{1 << 6, 1};
const deviceButton KEY_P{1 << 7, 1};
const deviceButton KEY_Q{1 << 0, 2};
const deviceButton KEY_R{1 << 1, 2};
const deviceButton KEY_S{1 << 2, 2};
const deviceButton KEY_T{1 << 3, 2};
const deviceButton KEY_U{1 << 4, 2};
const deviceButton KEY_V{1 << 5, 2};
const deviceButton KEY_W{1 << 6, 2};
const deviceButton KEY_X{1 << 7, 2};
const deviceButton KEY_Y{1 << 0, 3};
const deviceButton KEY_Z{1 << 1, 3};

virtualKeyboard::virtualKeyboard() : LACEDevice(32) {
    // keyboard devices need 32 bytes for all of the buttons
}

bool virtualKeyboard::processLACEPacket(const dataPacket input) {
    if (input.getPacketID() != dataID) {
        ESP_LOGE("KBD", "ERROR PACKET TYPE IS NOT DATA");
        return (0);
    }
    if (input.getPacketDeviceType() != keyboard) {
        ESP_LOGE("KBD", "ERROR PACKET STATE DEVICE TYPE IS NOT A KEYBOARD");
        return (0);
    }

    // enter a critical section so that reading and writing of the array don't happen simultaneously
    portMUX_TYPE keyboardMux = portMUX_INITIALIZER_UNLOCKED;
    taskENTER_CRITICAL(&keyboardMux);
    // copy the array to the keyboards key array
    input.getData(buttonArray, getDataPacketSize(keyboard));
    taskEXIT_CRITICAL(&keyboardMux);
    return (1);
}

dataPacket virtualKeyboard::encodeLACEPacket() {
    dataPacket output;
    output.setData(buttonArray, buttonArrayLength);
    output.setDeviceID(deviceID);
    return (output);
}