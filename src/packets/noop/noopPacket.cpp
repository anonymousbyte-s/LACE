#include "noopPacket.h"

noopPacket::noopPacket() {
    this->ID = noopID;
}

noopPacket::noopPacket(uint8_t* input, size_t inputLength) {
    this->ID = noopID;
    encode(input, inputLength);
}

bool noopPacket::encode(uint8_t* input, size_t inputLength) {
    if (inputLength != 1) {
        printf("PACK ERROR INPUT BUFFER IS NOT EXPECTED SIZE NOOP\n");
        return (false);
    }
    return (true);
}

size_t noopPacket::decode(uint8_t* output, size_t outputLength) const {
    if (outputLength < 1) {
        printf("PACK ERROR OUTPUT BUFFER TOO SMALL NOOP\n");
        return (0);
    }
    output[0] = this->ID;
    return (1);
}