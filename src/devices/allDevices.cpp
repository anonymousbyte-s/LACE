#include "allDevices.h"

virtualDeviceArray::virtualDeviceArray(int64_t deviceTimeout, int64_t (*getSystemMicroseconds)()) {
    this->deviceTimeout = deviceTimeout;
    this->getSystemMicroseconds = getSystemMicroseconds;
}

void virtualDeviceArray::deviceTimeoutReset(uint8_t deviceIndex) {
    if (deviceIndex >= maxLACEDeviceCount) {
        return;
    }
    // reset the timer
    deviceTimeoutArray[deviceIndex] = getSystemMicroseconds();
}

LACEDevice* virtualDeviceArray::getVirtualDevice(uint8_t deviceIndex) {
    if (deviceIndex >= maxLACEDeviceCount) {
        return (nullptr);
    }
    return (deviceArray[deviceIndex]);
}

void virtualDeviceArray::deviceTimeoutCheck() {
    for (int i = 0; i < maxLACEDeviceCount; i++) {
        if (getSystemMicroseconds() - deviceTimeoutArray[i] >= deviceTimeout) {
            removeDevice(i);
        }
    }
}

uint8_t virtualDeviceArray::nextFreeDeviceIndex() {
    for (uint8_t deviceIndex = 0; deviceIndex < maxLACEDeviceCount; deviceIndex++) {
        printf("Device array index %u\n", deviceIndex);
        if (deviceArray[deviceIndex] == nullptr) {
            printf("Found free slot at index %u\n", deviceIndex);
            return (deviceIndex);
        }
    }
    // error, could not find a free device slot
    return (255);
}

uint8_t virtualDeviceArray::addDeviceFromID(deviceType input) {
    uint8_t output = 255;
    switch (input) {
        case (keyboard): {
            output = addKeyboard();
            break;
        }
        case (mouse): {
            // output = addMouse();
            break;
        }
        case (gamepad): {
            // output = addGamepad();
            break;
        }
    }
    return (output);
}

uint8_t virtualDeviceArray::addKeyboard() {
    uint8_t deviceIndex = nextFreeDeviceIndex();
    if (deviceIndex == 255) {
        return (255);
    }
    deviceArray[deviceIndex] = new virtualKeyboard;
    if (deviceArray[deviceIndex] == nullptr) {
        return (255);
    }

    deviceTimeoutReset(deviceIndex);

    return (deviceIndex);
}

/*void virtualDeviceArray::addMouse() {
    uint8_t deviceIndex = nextFreeDeviceIndex();
    deviceArray[deviceIndex] = new virtualMouse;
}

void virtualDeviceArray::addGamepad() {
    uint8_t deviceIndex = nextFreeDeviceIndex();
    deviceArray[deviceIndex] = new virtualGamepad;
}*/

void virtualDeviceArray::removeDevice(uint8_t deviceIndex) {
    if (deviceIndex >= maxLACEDeviceCount) {
        return;
    }
    delete deviceArray[deviceIndex];
    deviceArray[deviceIndex] = nullptr;
}

virtualDeviceArray::~virtualDeviceArray() {
    for (int i = 0; i < maxLACEDeviceCount; i++) {
        delete deviceArray[i];
        deviceArray[i] = nullptr;
    }
}