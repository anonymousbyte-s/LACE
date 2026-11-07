#include "LACE.h"

size_t cobsEncode(const void* input, size_t inputLength, uint8_t* output, size_t outputLength) {
    // check that the output buffer has enough space
    if (inputLength + (inputLength + 253) / 254 + 1 > outputLength) {
        printf("COBS Buffer Overflow\n");
        return (0);
    }

    uint8_t* encode = output + 1;  // Encoded byte pointer
    uint8_t* codep = output;       // Output code pointer
    uint8_t code = 1;              // Code value

    for (const uint8_t* byte = (const uint8_t*)input; inputLength-- > 0; ++byte) {
        if (*byte != 0) {
            // if the byte is not zero, then write it to the output buffer
            *encode = *byte;
            encode++;
            // we have added a byte to the current block, so add that to the block
            // counter
            code++;
        }

        if (*byte == 0 || code == 0xff)  // Input is zero or block completed, restart
        {
            // write the block size to the last zero location
            *codep = code;
            code = 1;
            // encode points to the current zero byte
            codep = encode;
            if (*byte == 0 || inputLength != 0) {
                encode++;
            }
        }
    }
    *codep = code;  // Write final code value
    *encode = 0;    // the final deliminator zero

    // add one for the  final zero
    return (size_t)(encode - output + 1);
}

size_t cobsDecode(const uint8_t* input, size_t inputLength, void* output,
                  size_t outputSize) {
    const uint8_t* byte = input;         // Encoded input byte pointer
    uint8_t* decode = (uint8_t*)output;  // Decoded output byte pointer

    // iterate over the length of the input buffer
    uint8_t code = 0xff;
    uint8_t block = 0;
    while (byte < input + inputLength) {
        // if the block index is not zero, the data is valid to copy
        if (block != 0) {
            *decode = *byte;
            decode++;
            byte++;
        } else {            // if the block counter is zero, the next zero in the data was
                            // reached
            block = *byte;  // Fetch the next block length
            byte++;
            // reinsert the zero, unless it is a delimiter of value 0xff
            if (block != 0 && (code != 0xff)) {
                *decode = 0;
                decode++;
            }
            code = block;
            if (code == 0) {  // Delimiter code found
                break;
            }
        }
        // output buffer overflow
        if (decode - (uint8_t*)output > outputSize) {
            printf("COBS Buffer Overflow\n");
            return (0);
        }
        block--;
    }

    return (size_t)(decode - (uint8_t*)output);
}

uint16_t computeCRC16(const uint8_t* input, const size_t inputLength) {
    uint16_t crc = 0xFFFF;

    for (size_t i = 0; i < inputLength; i++) {
        // XOR-in next input byte
        uint8_t index = (uint8_t)((crc >> 8) ^ input[i]);
        // get current CRC value = remainder
        crc = (uint16_t)((crc << 8) ^ crcTable[index]);
    }
    return (crc);
}

size_t LACEFrameEncode(uint8_t* input, size_t inputLength, uint8_t* output, size_t outputLength) {
    // copy the data to a new buffer with space for the CRC
    uint8_t dataWithCRC[inputLength + 2];
    memcpy(dataWithCRC, input, inputLength);

    // compute the datas CRC
    uint16_t CRC = computeCRC16(input, inputLength);
    // copy the CRC to the data buffer
    dataWithCRC[inputLength++] = CRC & 0xff;
    dataWithCRC[inputLength++] = (CRC >> 8) & 0xff;

    // wrap the data with the CRC into COBS encoding
    size_t writtenSize = cobsEncode(dataWithCRC, inputLength, output, outputLength);

    // return the final length of the frame
    return (writtenSize);
}

size_t LACEFrameDecode(uint8_t* input, size_t inputLength, uint8_t* output, size_t outputLength) {
    // can't decode an empty frame
    if (inputLength == 0) {
        printf("LACE FRAME EMPTY\n");
        return (0);
    }
    // remove the COBS encoding and store that in a new buffer
    uint8_t dataWithCRC[inputLength];
    size_t dataWithCRCLength =
        cobsDecode(input, inputLength, dataWithCRC, inputLength);

    // can't compute a CRC if there is no data in the frame
    if (dataWithCRCLength <= 2) {
        printf("LACE PACKET EMPTY\n");
        return (0);
    }

    // calculate the CRC and check it against the received one
    uint16_t CRC = computeCRC16(dataWithCRC, dataWithCRCLength - 2);

    if (CRC != ((uint16_t)(dataWithCRC[dataWithCRCLength - 2] | (dataWithCRC[dataWithCRCLength - 1] << 8)))) {
        printf("LACE CRC Error check\n");
        return (0);
    }

    size_t dataLength = dataWithCRCLength - 2;

    // copy the data to the output buffer without the CRC
    if (dataLength > outputLength) {
        printf("LACE Decode output buffer overflow\n");
        return (0);
    }

    memcpy(output, dataWithCRC, dataLength);

    return (dataLength);
}