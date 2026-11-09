#include "errorPacket.h"

errorPacket::errorPacket() {
    this->ID = errorID;
}

errorPacket::errorPacket(uint8_t* input, size_t inputLength) {
    this->ID = errorID;
    encode(input, inputLength);
}

bool errorPacket::encode(uint8_t* input, size_t inputLength) {
    if (inputLength != 1) {
        printf("PACK ERROR INPUT BUFFER IS NOT EXPECTED SIZE ERR\n");
        return (false);
    }
    return (true);
}

size_t errorPacket::decode(uint8_t* output, size_t outputLength) const {
    if (outputLength < 1) {
        printf("PACK ERROR OUTPUT BUFFER TOO SMALL ERR\n");
        return (0);
    }
    output[0] = this->ID;
    return (1);
}