#pragma once
#include "../packet.h"

/**
 * Announce
 * an announce packet is sent by a device to the master to let it know that it
 * is connected this allows to master to skip wating to send the ping packet,
 * which can speed up the handshake
 * announce action: when an announce packet is received by the master device the
 * master will respond with a ping packet and the handshake continues from there
 * announce triggers: when a device is first connnected to the master it will send an announce packet
 * byte 0: announce packet ID, value 0
 */

/// @brief structure of a packet to be sent to a virtual device
struct announcePacket : public packet {
    /// @brief constructor for the announcePacket, sets the ID to type annoucePacket
    announcePacket();

    /// @brief constructs a packet using the encode function
    /// @param input the data to encode
    /// @param inputLength the length of the input data
    announcePacket(uint8_t* input, size_t inputLength);

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