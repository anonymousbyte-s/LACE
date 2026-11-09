#pragma once
#include "../packet.h"

/**
 * Data
 * a data packet is send by a device after a sucessful handshake
 * data action:
 * when a data packet is received by the master, it will decode the data packet
 * data triggers:
 * a data packet is sent once a device has data to send to the master device
 * byte 0: data packet ID, value 5
 * byte 1: device ID
 * byte 2: device type
 * byte 3+n: data byte n for that state type
 */

/// @brief structure of a packet to be sent to a virtual device
struct dataPacket : public packet {
   private:
    /// @brief the type of device sending the data
    deviceType packetDeviceType;
    /// @brief the ID of the device sending the data
    uint8_t deviceID;

    /// @brief the packets data
    uint8_t data[maxPacketDataLength];
    /// @brief the length of the packet data
    size_t dataLength = 0;

   public:
    /// @brief constructor for the dataPacket, sets the ID to type dataID
    dataPacket();

    /// @brief constructs a packet using the encode function
    /// @param input the data to encode
    /// @param inputLength the length of the input data
    dataPacket(uint8_t* input, size_t inputLength);

    /// @brief returns the type of device the packet is coming from
    /// @return the type of device
    deviceType getPacketDeviceType() const;

    /// @brief sets the type of device the packet is coming from
    /// @param packetDeviceType the device type to set the packet to
    void setPacketDeviceType(deviceType packetDeviceType);

    /// @brief sets the packets device ID
    /// @param deviceID the ID to set it to
    void setDeviceID(uint8_t deviceID);

    /// @brief returns the device ID
    /// @return the devce ID
    uint8_t getDeviceID() const;

    /// @brief copies data from the input array to the data array
    /// @param input the data to copy to the struct
    /// @param length the length of the data to copy
    /// @return 1 if the data was copied, 0 if there was an overflow
    bool setData(uint8_t* input, size_t dataLength);

    /// @brief adds data to the end of the data array
    /// @param input the data to add to the struct
    /// @param length the length of the data to add
    /// @return 1 if the data was copied, 0 if there was an overflow
    bool addData(uint8_t* input, size_t dataLength);

    /// @brief writes the packets data to the output buffer
    /// @param output the output buffer to write to
    /// @param outptuLength the length of the output buffer
    /// @return the amount of byte written to the output buffer, or 0 if there was an error
    size_t getData(uint8_t* output, size_t outptuLength) const;

    /// @brief returns the length of the data in the packet
    /// @return the length of the data in the packet
    size_t getDataLength() const;

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
