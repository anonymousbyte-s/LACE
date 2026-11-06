#pragma once
#include "../descriptor/descriptorPacket.h"

/**
 * Accept
 * an accept packet is send by the master when a connected device is compatible
 * with the master
 * accept action: after an accept is sent to a device that
 * device will start sending its data packets
 * accept triggers: an accept packet is sent when the master receives a descriptor
 * packet and it is compatible with the described device
 * accept structure:
 * byte 0: accept packet ID, value 3
 * byte 1: MAC address byte 0
 * byte 2: MAC address byte 1
 * byte 3: MAC address byte 2
 * byte 4: MAC address byte 3
 * byte 5: MAC address byte 4
 * byte 6: MAC address byte 5
 * byte 7: protocol version in use
 * byte 8: device type byte, uses a byte mask to allow for multiple device types
 * this byte tells the device which one of its devices were accepted, for example
 * if the device presents itself as a keyboard, mouse and gamepad but mice are
 * not supported, then only the keyboard and gamepad bit will be set
 * byte 9+n: Assigned device ID starting from the LSB, lets assume that the same
 * device from above, byte 9+0 will be the device ID for the keyboard as the
 * keyboard bit is bit 0, bit 1 is the mouse bit, but they are not supported so
 * it is skipped, byte 9+1 will be the device ID for the gamepad as it is the
 * next supported device
 */

/// @brief structure of a packet to be sent to a virtual device
struct acceptPacket : public descriptorPacket {
   private:
    /// @brief an array of the assigned device IDs
    uint8_t deviceIDs[8];
    /// @brief the number of devices in the deviceIDs array
    uint8_t deviceIDCount = 0;

   public:
    /// @brief constructor for the acceptPacket, sets the ID to type acceptID
    acceptPacket();

    /// @brief constructs a packet using the encode function
    /// @param input the data to encode
    /// @param inputLength the length of the input data
    acceptPacket(uint8_t* input, size_t inputLength);

    /// @brief adds a device ID to the deviceIDs array
    /// @param input the deviceID to add
    /// @return true on sucess, false if the deviceIDs array is full
    bool addDeviceID(uint8_t input);

    /// @brief sets the entire device ID array at once
    /// @param input the array to copy to the deviceIDs array
    /// @param inputLength the length of the input array
    /// @return true if all of the device IDs could fit, and false if not (will not copy IDs on failure)
    bool setDeviceIDs(uint8_t* input, uint8_t inputLength);

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