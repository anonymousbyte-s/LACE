#include "allPackets.h"

packetVariants autoConstructPacket(uint8_t* input, size_t inputLength) {
    // cant decode an empty packet
    if (inputLength == 0) {
        return (errorPacket{});
    }

    packetVariants output;
    // find what kind of packet the input is
    switch (input[0]) {
        case (acceptID):
            output.emplace<acceptPacket>(input, inputLength);
            break;
        case (announceID):
            output.emplace<announcePacket>(input, inputLength);
            break;
        case (dataID):
            output.emplace<dataPacket>(input, inputLength);
            break;
        case (declineID):
            output.emplace<declinePacket>(input, inputLength);
            break;
        case (descriptorID):
            output.emplace<descriptorPacket>(input, inputLength);
            break;
        case (errorID):
            output.emplace<errorPacket>(input, inputLength);
            break;
        case (pingID):
            output.emplace<pingPacket>(input, inputLength);
            break;
    };

    // if the outputs ID is an error then return an error packet
    if (asPacket(output)->getPacketID() == errorID) {
        output.emplace<errorPacket>();
    }
    return (output);
}