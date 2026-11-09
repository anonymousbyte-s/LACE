#pragma once
#include "../packet.h"

/**
 * Descriptor
 * a descriptor packet is used by a device to describe itself to the master
 * descriptor action:
 * when a descriptor packet is received by a master it will respond with an
 * accept or reject packet
 * descriptor triggers: a descriptor is sent when a device receives a ping packet
 * descriptor structure:
 * byte 0: descriptor packet ID, value 2
 * byte 1: deviceRandomID byte 0
 * byte 2: deviceRandomID byte 1
 * byte 3: deviceRandomID byte 2
 * byte 4: deviceRandomID byte 3
 * byte 5: deviceRandomID byte 4
 * byte 6: deviceRandomID byte 5
 * byte 7: protocol version
 * byte 8: device type byte, uses a byte mask to allow for multiple device types
 */

/// @brief structure of a packet to be sent to a virtual device
struct descriptorPacket : public packet {
   protected:
    /// @brief the deviceRandomID of the ESP32 sending the packet, used
    /// to ID the device before device IDs are assigned to it
    uint8_t deviceRandomID[6] = {0};
    /// @brief version of LACE that the device is using
    uint8_t packetLACEVersion = 0;
    /// @brief the byte mask of the devices that the ESP32 exposes
    uint8_t deviceByteMask = 0;

   public:
    /// @brief constructor for the descriptorPacket, sets the ID to type descriptorID
    descriptorPacket();

    /// @brief constructs a packet using the encode function
    /// @param input the data to encode
    /// @param inputLength the length of the input data
    descriptorPacket(uint8_t* input, size_t inputLength);

    /// @brief sets the deviceRandomID for the packet
    /// @param input buffer containing the deviceRandomID, only the
    /// first 6 bytes will be used, must be at least 6 bytes long
    void setDeviceRandomID(uint8_t* input);

    /// @brief copys the deviceRandomID from the packet to the output buffer
    /// @param output the buffer to copy the deviceRandomID to, must be at least length 6
    void getDeviceRandomID(uint8_t* output) const;

    /// @brief sets the LACE version for the packet
    /// @param PacketLACEVersion the value to set the LACE version to
    void setPacketLACEVersion(uint8_t packetLACEVersion);

    /// @brief gets the LACE version for the packet
    /// @return the version number from the packet
    uint8_t getPacketLACEVersion() const;

    /// @brief adds a device to the packets device byte mask
    /// @param byteMask the byte mask of the device to add
    void addDevice(uint8_t byteMask);

    /// @brief overwrites the device byte mask with a new one
    /// @param byteMask the new byte mask to set
    void setDeviceByteMask(uint8_t byteMask);

    /// @brief returns the packets device byte mask
    /// @return the packets byte mask
    uint8_t getDeviceByteMask() const;

    /// @brief removes a device to the packets device byte mask
    /// @param byteMask the byte mask of the device to remove
    void removeDevice(uint8_t byteMask);

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
