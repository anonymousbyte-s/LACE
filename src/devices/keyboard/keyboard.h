#pragma once
#include "../device.h"
#include "cstdint"
#include "driver/uart.h"

#define virtualKeyboardCount UART_NUM_MAX

extern const deviceButton KEY_A;
extern const deviceButton KEY_B;
extern const deviceButton KEY_C;
extern const deviceButton KEY_D;
extern const deviceButton KEY_E;
extern const deviceButton KEY_F;
extern const deviceButton KEY_G;
extern const deviceButton KEY_H;
extern const deviceButton KEY_I;
extern const deviceButton KEY_J;
extern const deviceButton KEY_K;
extern const deviceButton KEY_L;
extern const deviceButton KEY_M;
extern const deviceButton KEY_N;
extern const deviceButton KEY_O;
extern const deviceButton KEY_P;
extern const deviceButton KEY_Q;
extern const deviceButton KEY_R;
extern const deviceButton KEY_S;
extern const deviceButton KEY_T;
extern const deviceButton KEY_U;
extern const deviceButton KEY_V;
extern const deviceButton KEY_W;
extern const deviceButton KEY_X;
extern const deviceButton KEY_Y;
extern const deviceButton KEY_Z;

class virtualKeyboard : public LACEDevice {
   public:
    /// @brief initializes the keyboard
    virtualKeyboard();

    /// @brief checks if the input packet is a keyboard packet, and if it is it will process it
    /// @param input the packet to process
    /// @return true if the packet was processed, 0 if it was rejected
    bool processLACEPacket(dataPacket input) override;

    /// @brief returns a dataPacket struct with the keyboard data
    /// @return the encoded dataPacket
    dataPacket encodeLACEPacket() override;
};
