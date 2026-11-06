#pragma once
#include <packets/allPackets.h>

#include "cstdint"
#include "driver/uart.h"
#include "esp_log.h"

struct deviceButton {
    /// @brief the byte mask
    const uint8_t byteMask;
    /// @brief the amount of bytes into the keyboard key array the byte is
    const uint8_t byteMaskOffset;
};

class LACEDevice {
   protected:
    /// @brief pointer to the button array
    uint8_t* buttonArray = nullptr;
    /// @brief the length of the button arrays
    uint8_t buttonArrayLength;
    /// @brief used to identify the device and the packets it sends
    uint8_t deviceID;

   public:
    /// @brief contructs the LACEDevice and allocates memory for the button array
    /// @param buttonArrayLength the length of the devices button array
    LACEDevice(uint8_t buttonArrayLength);

    /// @brief returns the devices ID
    /// @return the devices ID
    uint8_t getID();

    /// @brief sets the device ID
    /// @param deviceID the ID to set it to
    void setID(uint8_t deviceID);

    /// @brief gets a buttons value
    /// @param button the button to get the state of
    /// @return the buttons value
    bool getButton(const deviceButton button);

    /// @brief sets a buttons value
    /// @param button the button to set
    /// @param state the value to set it to
    /// @return true on sucess, false on failure
    bool setButton(const deviceButton button, const bool state);

    /// @brief attempts to process a lace packet
    /// @param input the packet to process
    /// @return returns true if the packet was processed and false if it was rejected
    virtual bool processLACEPacket(dataPacket input) = 0;

    /// @brief deconstructor for a LACEDevice, will free the buttonArray memory
    ~LACEDevice();
};