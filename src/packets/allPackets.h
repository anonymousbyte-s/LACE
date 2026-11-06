#pragma once

#include <variant>

#include "accept/acceptPacket.h"
#include "announce/announcePacket.h"
#include "data/dataPacket.h"
#include "decline/declinePacket.h"
#include "descriptor/descriptorPacket.h"
#include "error/errorPacket.h"
#include "ping/pingPacket.h"

using packetVariants = std::variant<
    std::monostate,
    acceptPacket,
    announcePacket,
    dataPacket,
    declinePacket,
    descriptorPacket,
    errorPacket,
    pingPacket>;

/// @brief automatically constructs a packet of the correct type
/// @param input the buffer to construct the packet from
/// @param inputLength the length of the input buffer
/// @return an std::variant of the constructed packet
packetVariants autoConstructPacket(uint8_t* input, size_t inputLength);