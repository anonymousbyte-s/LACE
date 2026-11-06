#include "dataPacket.h"

dataPacket::dataPacket() {
    this->ID = dataID;
}

dataPacket::dataPacket(uint8_t* input, size_t inputLength) {
    this->ID = dataID;
    if (!this->encode(input, inputLength)) {
        this->ID = errorID;
    }
}

deviceType dataPacket::getPacketDeviceType() const {
    return (packetDeviceType);
}

void dataPacket::setDeviceID(uint8_t deviceID) {
    this->deviceID = deviceID;
}

uint8_t dataPacket::getDeviceID() const {
    return (deviceID);
}

bool dataPacket::setData(uint8_t* input, size_t dataLength) {
    if (dataLength > maxPacketDataLength) {
        return (0);
    }
    memcpy(data, input, dataLength);
    this->dataLength = dataLength;
    return (1);
}

size_t dataPacket::getDataLength() const {
    return (dataLength);
}

bool dataPacket::addData(uint8_t* input, size_t dataLength) {
    if (this->dataLength + dataLength > maxPacketDataLength) {
        return (0);
    }
    memcpy(&data[this->dataLength], input, dataLength);
    this->dataLength += dataLength;
    return (1);
}

size_t dataPacket::getData(uint8_t* output, size_t outptuLength) const {
    if (outptuLength < dataLength) {
        printf("PACK ERROR OUTPUT BUFFER TOO SMALL");
        return (0);
    }

    memcpy(output, data, dataLength);
    return (dataLength);
}

bool dataPacket::encode(uint8_t* input, size_t inputLength) {
    if (inputLength < 3) {
        printf("PACK ERROR INPUT BUFFER IS NOT EXPECTED SIZE");
        return (false);
    }
    if (inputLength != 3 + getDataPacketSize((deviceType)input[2])) {
        printf("PACK ERROR INPUT BUFFER IS NOT EXPECTED SIZE");
        return (false);
    }

    this->packetDeviceType = (deviceType)input[1];
    this->deviceID = input[2];
    setData(&input[3], getDataPacketSize((deviceType)input[2]));
    return (true);
}

size_t dataPacket::decode(uint8_t* output, size_t outputLength) const {
    if (outputLength < 3 + getDataPacketSize(this->packetDeviceType)) {
        printf("PACK ERROR OUTPUT BUFFER TOO SMALL");
        return (0);
    }
    output[0] = this->ID;
    output[1] = this->packetDeviceType;
    output[2] = this->deviceID;
    memcpy(&output[3], data, dataLength);

    return (3 + getDataPacketSize(this->packetDeviceType));
}