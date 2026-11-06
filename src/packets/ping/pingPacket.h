#pragma once
#include "../packet.h"

/**
 * Ping
 * a ping is used by the master to see if there are any devices connected
 * ping action:
 * when a ping is received by a device it will respond with a descriptor packet
 * ping triggers:
 * a ping is sent periodicly to check for connected devices, one every 500ms
 * a ping is also sent after the master device receives an announce packet
 * ping structure:
 * byte 0: ping packet ID, value 1
 */

/// @brief structure of a packet to be sent to a virtual device
struct pingPacket : public packet {
    /// @brief constructor for the pingPacket, sets the ID to type pingID
    pingPacket();

    /// @brief constructs a packet using the encode function
    /// @param input the data to encode
    /// @param inputLength the length of the input data
    pingPacket(uint8_t* input, size_t inputLength);

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