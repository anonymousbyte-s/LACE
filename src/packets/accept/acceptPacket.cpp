#include "acceptPacket.h"

acceptPacket::acceptPacket() {
    this->ID = acceptID;
}

acceptPacket::acceptPacket(uint8_t* input, size_t inputLength) {
    this->ID = acceptID;
    if (!this->encode(input, inputLength)) {
        this->ID = errorID;
    }
}

bool acceptPacket::addDeviceID(uint8_t input) {
    if (deviceIDCount >= 8) {
        return (false);
    }
    deviceIDs[deviceIDCount] = input;
    deviceIDCount++;
    return (true);
}

bool acceptPacket::setDeviceIDs(uint8_t* input, size_t inputLength) {
    if (inputLength > 8 || inputLength <= 0) {
        return (false);
    }
    memcpy(deviceIDs, input, inputLength);
    deviceIDCount = inputLength;
    return (true);
}

uint8_t acceptPacket::getDeviceID(uint8_t index) {
    // out of bounds
    if (index >= deviceIDCount) {
        return (255);
    }
    return (deviceIDs[index]);
}

bool acceptPacket::encode(uint8_t* input, size_t inputLength) {
    if (inputLength < 9) {
        printf("PACK ERROR INPUT BUFFER IS NOT BIG ENOUGH ACPT\n");
        return (false);
    }
    // calculate the expected data length and check if it matches
    size_t expectedLength = 9 + __builtin_popcount(input[8]);
    if (inputLength != expectedLength) {
        printf("PACK ERROR INPUT BUFFER IS NOT EXPECTED SIZE ACPT\n");
        return (false);
    }

    setMACAddress(&input[1]);
    setPacketLACEVersion(input[7]);
    setDeviceByteMask(input[8]);
    setDeviceIDs(&input[9], __builtin_popcount(input[8]));
    return (true);
}

size_t acceptPacket::decode(uint8_t* output, size_t outputLength) const {
    if (outputLength < 9 + __builtin_popcount(deviceByteMask)) {
        printf("PACK ERROR OUTPUT BUFFER TOO SMALL\n");
        return (0);
    }

    output[0] = this->ID;
    memcpy(&output[1], MACAddress, 6);
    output[7] = packetLACEVersion;
    output[8] = deviceByteMask;
    memcpy(&output[9], deviceIDs, __builtin_popcount(deviceByteMask));
    return (9 + __builtin_popcount(deviceByteMask));
}