#include "announcePacket.h"

announcePacket::announcePacket() {
    this->ID = announceID;
}

announcePacket::announcePacket(uint8_t* input, size_t inputLength) {
    this->ID = announceID;
    this->encode(input, inputLength);
}

bool announcePacket::encode(uint8_t* input, size_t inputLength) {
    if (inputLength != 1) {
        printf("PACK ERROR INPUT BUFFER IS NOT EXPECTED SIZE");
        return (false);
    }
    return (true);
}

/// @brief decodes the current packet struct into raw data
/// @param output the output array
/// @param outputLength the length of the output array
/// @return the size of the written packet, or 0 if there was an error
size_t announcePacket::decode(uint8_t* output, size_t outputLength) const {
    if (outputLength < 1) {
        printf("PACK ERROR OUTPUT BUFFER TOO SMALL");
        return (0);
    }
    output[0] = this->ID;
    return (1);
}