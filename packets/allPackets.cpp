#include "allPackets.h"

packetVariants autoConstructPacket(uint8_t* input, size_t inputLength) {
    // cant decode an empty packet
    if (inputLength == 0) {
        return (errorPacket{input, inputLength});
    }

    packetVariants output;
    // find what kind of packet the input is
    switch (input[0]) {
        case (acceptID):
            output = acceptPacket{input, inputLength};
            break;
        case (announceID):
            output = announcePacket{input, inputLength};
            break;
        case (dataID):
            output = dataPacket{input, inputLength};
            break;
        case (declineID):
            output = declinePacket{input, inputLength};
            break;
        case (descriptorID):
            output = descriptorPacket{input, inputLength};
            break;
        case (errorID):
            output = errorPacket{input, inputLength};
            break;
        case (pingID):
            output = pingPacket{input, inputLength};
            break;
    };
    // if the outputs ID is an error then return an error packet
    std::visit([&output](auto& input) {
        using T = std::decay_t<decltype(input)>;
        if constexpr (std::is_same_v<T, std::monostate>) {
            return;
        } else {
            if (input.getPacketID() == errorID) {
                output = errorPacket{};
            }
        }
    },
               output);
    return (output);
}