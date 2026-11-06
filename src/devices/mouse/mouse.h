#pragma once
/*

enum mouseClickState {
    leftClick = 0b1,
    rightClick = 0b10,
    middleClick = 0b100,
};

class mouseState {
    /// @brief mouse x position
    int mouseX = 0;
    /// @brief mouse y position
    int mouseY = 0;

    /// @brief mouse click state, use the mouse click event enum as a mask to get each buttons state
    unsigned char click = 0;

   public:
    /// @brief returns the state of a mouse button
    /// @param input the button to check
    /// @return true if the input is clicked, false otherwise
    bool getMouseClick(mouseClickState input);

    /// @brief sets the mouses click state
    /// @param input the mouse button to set
    /// @param state the state to set it to, 1 for clicked, 0 for unclicked
    void setMouseClick(mouseClickState input, bool state);

    /// @brief gets the mouses x position
    /// @return the mouses x position
    int getMouseX();
    /// @brief gets the mouses y position
    /// @return the mouses y position
    int getMouseY();

    /// @brief sets the mouse position
    /// @param x the new x position of the mouse
    /// @param y the new y position of the mouse
    /// @return true if the values are in range, and false otherwise
    bool setMousePos(int x, int y);

    /// @brief moves the mouse from its current position
    /// @param x the x value to move by
    /// @param y the y value to move by
    /// @return true if the new position is in range, and false otherwise
    bool moveMouse(int x, int y);
};*/