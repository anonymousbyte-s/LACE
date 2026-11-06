#pragma once
#include "cstdint"

/// @brief type of device that is connected
enum deviceType : uint8_t { keyboard = 1,
                            mouse = 1 << 1,
                            gamepad = 1 << 2 };

/// @brief these are used to identify the kind of packet
enum packetID : uint8_t {
    announceID,
    pingID,
    descriptorID,
    acceptID,
    declineID,
    dataID,
    errorID = 255
};

inline uint8_t getDataPacketSize(deviceType input) {
    uint8_t output = 0;
    switch (input) {
        case (keyboard):
            output = 32;
            break;
        case (mouse):
            output = 8;
            break;
        case (gamepad):
            output = 12;
            break;
    };
    return (output);
}