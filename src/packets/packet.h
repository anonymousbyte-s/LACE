#pragma once
#include <stdio.h>

#include <cstring>

#include "packetIDs.h"

#define maxPacketDataLength 32

/**
 * Light Asynchronous Communication Encapsulation (LACE) protocol specification
 *
 * Handshake packets
 *
 * Announce
 * an announce packet is sent by a device to the master to let it know that it
 * is connected this allows to master to skip wating to send the ping packet,
 * which can speed up the handshake
 * announce action: when an announce packet is received by the master device the
 * master will respond with a ping packet and the handshake continues from there
 * announce triggers: when a device is first connnected to the master it will send an announce packet
 * byte 0: announce packet ID, value 0
 *
 * Ping
 * a ping is used by the master to see if there are any devices connected
 * ping action:
 * when a ping is received by a device it will respond with a descriptor packet
 * ping triggers:
 * a ping is sent periodicly to check for connected devices, one every 500ms
 * a ping is also sent after the master device receives an announce packet
 * ping structure:
 * byte 0: ping packet ID, value 1
 *
 * Descriptor
 * a descriptor packet is used by a device to describe itself to the master
 * descriptor action:
 * when a descriptor packet is received by a master it will respond with an
 * accept or reject packet
 * descriptor triggers: a descriptor is sent when a device receives a ping packet
 * descriptor structure:
 * byte 0: descriptor packet ID, value 2
 * byte 1: MAC address byte 0
 * byte 2: MAC address byte 1
 * byte 3: MAC address byte 2
 * byte 4: MAC address byte 3
 * byte 5: MAC address byte 4
 * byte 6: MAC address byte 5
 * byte 7: protocol version
 * byte 8: device type byte, uses a byte mask to allow for multiple device types
 *
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
 *
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
 * byte 1: decline reason
 *
 * Data packets
 *
 * Data
 * a data packet is send by a device after a sucessful handshake
 * data action:
 * when a data packet is received by the master, it will decode the data packet
 * data triggers:
 * a data packet is sent once a device has data to send to the master device
 * byte 0: data packet ID, value 5
 * byte 1: device ID
 * byte 2: state ID
 * byte 3+n: data byte n for that state type
 */

/// @brief base packet class
struct packet {
   protected:
    /// @brief the type of packet being sent
    packetID ID;

    /// @brief the default constructor
    packet() = default;

   public:
    /// @brief returns the packets ID
    /// @return the packets ID
    packetID getPacketID() const;

    /// @brief encodes a packets raw data into the current packet struct
    /// @param input the data to encode
    /// @param inputLength the length of the input data
    /// @return true on sucess and false on failure
    virtual bool encode(uint8_t* input, size_t inputLength) = 0;

    /// @brief decodes the current packet struct into raw data
    /// @param output the output array
    /// @param outputLength the length of the output array
    /// @return the size of the written packet, or 0 if there was an error
    virtual size_t decode(uint8_t* output, size_t outputLength) const = 0;
};