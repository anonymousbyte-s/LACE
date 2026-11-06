#include "descriptorPacket.h"

descriptorPacket::descriptorPacket() {
    this->ID = descriptorID;
}

descriptorPacket::descriptorPacket(uint8_t* input, size_t inputLength) {
    this->ID = descriptorID;
    if (!this->encode(input, inputLength)) {
        this->ID = errorID;
    }
}

void descriptorPacket::setMACAddress(uint8_t* input) {
    memcpy(MACAddress, input, 6);
}

void descriptorPacket::getMACAddress(uint8_t* output) const {
    memcpy(output, MACAddress, 6);
}

void descriptorPacket::setPacketLACEVersion(uint8_t packetLACEVersion) {
    this->packetLACEVersion = packetLACEVersion;
}

uint8_t descriptorPacket::getPacketLACEVersion() const {
    return (packetLACEVersion);
}

void descriptorPacket::addDevice(uint8_t byteMask) {
    this->deviceByteMask |= byteMask;
}

void descriptorPacket::setDeviceByteMask(uint8_t byteMask) {
    this->deviceByteMask = byteMask;
}

uint8_t descriptorPacket::getDeviceByteMask() const {
    return (deviceByteMask);
}

void descriptorPacket::removeDevice(uint8_t byteMask) {
    this->deviceByteMask &= ~byteMask;
}

bool descriptorPacket::encode(uint8_t* input, size_t inputLength) {
    if (inputLength != 9) {
        printf("PACK ERROR INPUT BUFFER IS NOT EXPECTED SIZE, DESC %zu", inputLength);
        return (false);
    }
    setMACAddress(&input[1]);
    setPacketLACEVersion(input[7]);
    setDeviceByteMask(input[8]);
    return (true);
}

size_t descriptorPacket::decode(uint8_t* output, size_t outputLength) const {
    if (outputLength < 9) {
        printf("PACK ERROR OUTPUT BUFFER TOO SMALL");
        return (0);
    }
    output[0] = this->ID;
    memcpy(&output[1], MACAddress, 6);
    output[7] = packetLACEVersion;
    output[8] = deviceByteMask;
    return (9);
}