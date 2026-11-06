#pragma once
#include "../packet.h"

/**
 * Decline
 * a decline packet is sent when the master refuses a connection to a device
 * decline action:
 * after a decline packet is sent the device will not send data
 * decline triggers:
 * when a connected device is using an unsuported protocol
 * byte 0: decline packet ID, value 4
 * byte 1: MAC address byte 0
 * byte 2: MAC address byte 1
 * byte 3: MAC address byte 2
 * byte 4: MAC address byte 3
 * byte 5: MAC address byte 4
 * byte 6: MAC address byte 5
 * byte 7: decline reason
 */

/// @brief structure of a packet to be sent to a virtual device
struct declinePacket : public packet {
   private:
    /// @brief the MAC address of the ESP32 sending the packet, used
    /// to ID the device before device IDs are assigned to it
    uint8_t MACAddress[6] = {0};
    /// @brief the reason that the connection was declined
    uint8_t declineReason = 0;

   public:
    /// @brief constructor for the declinePacket, sets the ID to type declineID
    declinePacket();

    /// @brief constructs a packet using the encode function
    /// @param input the data to encode
    /// @param inputLength the length of the input data
    declinePacket(uint8_t* input, size_t inputLength);

    /// @brief sets the MAC address for the packet
    /// @param input buffer containing the MAC address, only the
    /// first 6 bytes will be used, must be at least 6 bytes long
    void setMACAddress(uint8_t* input);

    /// @brief copys the mac address from the packet to the output buffer
    /// @param output the buffer to copy the mac address to, must be at least length 6
    void getMACAddress(uint8_t* output) const;

    /// @brief sets the packets decline reason
    /// @param declineReason the reason that the connection was declined
    void setDeclineReason(uint8_t declineReason);

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