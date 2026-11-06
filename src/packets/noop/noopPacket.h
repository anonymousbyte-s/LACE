#pragma once
#include "../packet.h"

/// @brief packet used to indicate that no reply is needed
struct noopPacket : public packet {
   public:
    /// @brief constructs an error packet
    noopPacket();

    /// @brief constructs a packet using the encode function
    /// @param input the data to encode
    /// @param inputLength the length of the input data
    noopPacket(uint8_t* input, size_t inputLength);

    /// @brief encodes a packets raw data into the current packet struct
    /// @param input the data to encode
    /// @param inputLength the length of the input data
    /// @return true on sucess and false on failure
    bool encode(uint8_t* input, size_t inputLength) override;

    /// @brief decodes the current packet struct into raw data
    /// @param output the output array
    /// @param outputLength the length of the output array
    /// @return the size of the written packet, or 0 if there was an error
    size_t decode(uint8_t* output, size_t outputLength) const override;
};