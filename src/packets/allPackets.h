#pragma once

#include <variant>

#include "accept/acceptPacket.h"
#include "announce/announcePacket.h"
#include "data/dataPacket.h"
#include "decline/declinePacket.h"
#include "descriptor/descriptorPacket.h"
#include "error/errorPacket.h"
#include "noop/noopPacket.h"
#include "ping/pingPacket.h"

using packetVariants = std::variant<
    announcePacket,
    pingPacket,
    descriptorPacket,
    acceptPacket,
    declinePacket,
    dataPacket,
    noopPacket,
    errorPacket>;

/// @brief converts from an std::variant back to a packet struct
/// @param v the std::variant to convert
/// @return a pointer to the packet struct
inline packet* asPacket(packetVariants& v) {
    return std::visit([](auto& p) -> packet* { return &p; }, v);
}

/// @brief automatically constructs a packet of the correct type
/// @param input the buffer to construct the packet from
/// @param inputLength the length of the input buffer
/// @return an std::variant of the constructed packet
packetVariants autoConstructPacket(uint8_t* input, size_t inputLength);