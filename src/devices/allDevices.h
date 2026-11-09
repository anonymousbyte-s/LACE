#pragma once

#include "../packets/packetIDs.h"
#include "device.h"
#include "keyboard/keyboard.h"
#include "mouse/mouse.h"

#define maxLACEDeviceCount 32

/// @brief used to store multiple devices and manage their memory
class virtualDeviceArray {
    /// @brief used to store all of the devices
    LACEDevice* deviceArray[maxLACEDeviceCount] = {nullptr};

    /// @brief function pointer to the micros function, must return a uint64_t
    /// that represents the systems microsecond timer
    int64_t (*getSystemMicroseconds)();

    /// @brief when this many microseconds have passed between now and when
    /// deviceTimeoutReset was called the device will be removed, deviceTimeoutCheck
    /// must be called for this to work
    int64_t deviceTimeout = 0;

    /// @brief keeps track of each devices timer
    int64_t deviceTimeoutArray[maxLACEDeviceCount] = {0};

   public:
    /// @brief default constructor
    virtualDeviceArray() = default;

    /// @brief constructor that also sets the device timeout value
    /// @param deviceTimeout the value to set the device timeout to
    /// when deviceTimeout microseconds have passed between now and when
    /// deviceTimeoutReset was called the device will be removed, deviceTimeoutCheck
    /// must be called for this to work
    /// @param getSystemMicroseconds pointer to the systems microseconds function
    /// must return a uint64_t that represents the systems microsecond timer
    virtualDeviceArray(int64_t deviceTimeout, int64_t (*getSystemMicroseconds)());

    /// @brief returns a pointer to the lace device at deviceIndex, or returns nullptr if no device exists there
    /// @param deviceIndex the index of the device to return
    /// @return the pointer to the device
    LACEDevice* getVirtualDevice(uint8_t deviceIndex);

    /// @brief resets a devices timeout timer
    /// @param deviceIndex the index of the device timer to reset
    void deviceTimeoutReset(uint8_t deviceIndex);

    /// @brief checks every devices timeout and removes them if the timer has expired
    void deviceTimeoutCheck();

    /// @brief finds the next free device index, or returns 255 if there is no free index
    /// @return the next free device index, or 255 if none are free
    uint8_t nextFreeDeviceIndex();

    /// @brief adds a device to the device array based on its deviceType
    /// @param input the type of device to add
    /// @return returns the index that the device was assigned, or returns 255 if
    /// no spot could be found for the new device
    uint8_t addDeviceFromID(deviceType input);

    /// @brief adds a keyboard device to the devices array
    /// @return returns the index that the device was assigned, or returns 255 if
    /// no spot could be found for the new device
    uint8_t addKeyboard();

    // void addMouse();

    // void addGamepad();

    void removeDevice(uint8_t deviceIndex);

    /// @brief deconstructor
    ~virtualDeviceArray();
};