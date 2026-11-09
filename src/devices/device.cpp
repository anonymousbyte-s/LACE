#include "device.h"

LACEDevice::LACEDevice(uint8_t buttonArrayLength, deviceType type) : type(type) {
    buttonArray = (uint8_t*)calloc(buttonArrayLength, sizeof(uint8_t));

    // check for sucessfull memory allocation
    if (buttonArray != nullptr) {
        this->buttonArrayLength = buttonArrayLength;
    } else {
        this->buttonArrayLength = 0;
    }
}

uint8_t LACEDevice::getID() {
    return (deviceID);
}

deviceType LACEDevice::getDeviceType() {
    return (type);
}

void LACEDevice::setID(uint8_t deviceID) {
    this->deviceID = deviceID;
}

bool LACEDevice::getButton(const deviceButton button) {
    bool output = 0;
    if (button.byteMaskOffset >= buttonArrayLength) {
        ESP_LOGE("DEVI", "ERROR PROVIDED BYTE MASK OUT OF RANGE");
        return (0);
    }
    // enter a critical section so that reading and writing of the array don't happen simultaneously
    portMUX_TYPE keyboardMux = portMUX_INITIALIZER_UNLOCKED;
    taskENTER_CRITICAL(&keyboardMux);
    output = (buttonArray[button.byteMaskOffset] & button.byteMask) != 0;
    // exit the critical section and return the output
    taskEXIT_CRITICAL(&keyboardMux);
    return (output);
}

bool LACEDevice::setButton(const deviceButton button, const bool state) {
    if (button.byteMaskOffset >= buttonArrayLength) {
        return (0);
    }
    portMUX_TYPE keyboardMux = portMUX_INITIALIZER_UNLOCKED;
    if (state) {
        // enter a critical section so that reading and writing of the array don't happen simultaneously
        taskENTER_CRITICAL(&keyboardMux);
        buttonArray[button.byteMaskOffset] |= button.byteMask;
        taskEXIT_CRITICAL(&keyboardMux);
    } else {
        // enter a critical section so that reading and writing of the array don't happen simultaneously
        taskENTER_CRITICAL(&keyboardMux);
        buttonArray[button.byteMaskOffset] &= ~button.byteMask;
        taskEXIT_CRITICAL(&keyboardMux);
    }
    return (1);
}

LACEDevice::~LACEDevice() {
    free(buttonArray);
    buttonArray = nullptr;
}