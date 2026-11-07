#include "declinePacket.h"

declinePacket::declinePacket() {
    this->ID = declineID;
}

declinePacket::declinePacket(uint8_t* input, size_t inputLength) {
    this->ID = declineID;
    if (!this->encode(input, inputLength)) {
        this->ID = errorID;
    }
}

void declinePacket::setMACAddress(uint8_t* input) {
    memcpy(MACAddress, input, 6);
}

void declinePacket::getMACAddress(uint8_t* output) const {
    memcpy(output, MACAddress, 6);
}

void declinePacket::setDeclineReason(declineReason reason) {
    this->reason = reason;
}

bool declinePacket::encode(uint8_t* input, size_t inputLength) {
    if (inputLength != 8) {
        printf("PACK ERROR INPUT BUFFER IS NOT EXPECTED SIZE\n");
        return (false);
    }
    setMACAddress(&input[1]);
    setDeclineReason((declineReason)input[7]);
    return (true);
}

size_t declinePacket::decode(uint8_t* output, size_t outputLength) const {
    if (outputLength < 8) {
        printf("PACK ERROR OUTPUT BUFFER TOO SMALL DEC\n");
        return (0);
    }
    output[0] = this->ID;
    memcpy(&output[1], MACAddress, 6);
    output[7] = reason;
    return (8);
}