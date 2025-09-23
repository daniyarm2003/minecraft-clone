#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <glm/glm.hpp>

namespace Input {
    enum class ButtonPressState {
        PRESSED,
        HELD,
        RELEASE_STARTED,
        RELEASED
    };

    class InputManager {
    public:
        void onKeyPress(int key);
        void onKeyRelease(int key);
        void onMouseMove(double xpos, double ypos);

        void onMouseButtonPress(int mouseButton);
        void onMouseButtonRelease(int mouseButton);

        void updateButtonStates();

        bool isKeyPressed(int key) const;
        ButtonPressState getKeyPressState(int key) const;

        bool isMouseButtonPressed(int mouseButton) const;
        ButtonPressState getMouseButtonPressState(int mouseButton) const;

        const glm::vec2& getMousePosition() const;
        glm::vec2 getMouseDelta() const;

        void resetMouseDelta();

    private:
        static constexpr int MAX_KEYS = 1024;
        static constexpr int MAX_MOUSE_BUTTONS = 3;

        bool keysPressed[MAX_KEYS] = { false };
        ButtonPressState keyStates[MAX_KEYS] = { ButtonPressState::RELEASED };

        bool mouseButtonsPressed[MAX_MOUSE_BUTTONS] = { false };
        ButtonPressState mouseButtonStates[MAX_KEYS] = { ButtonPressState::RELEASED };

        bool isMouseInitialized = false;

        glm::vec2 lastMousePosition = glm::vec2(0.0f);
        glm::vec2 mousePosition = glm::vec2(0.0f);
    };
}

#endif // INPUT_MANAGER_H