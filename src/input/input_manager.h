#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <glm/glm.hpp>

namespace Input {
    enum class KeyPressState {
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

        void updateKeyStates();

        bool isKeyPressed(int key) const;
        KeyPressState getKeyPressState(int key) const;

        const glm::vec2& getMousePosition() const;
        glm::vec2 getMouseDelta() const;

        void resetMouseDelta();

    private:
        static constexpr int MAX_KEYS = 1024;

        bool keysPressed[MAX_KEYS] = { false };
        KeyPressState keyStates[MAX_KEYS] = { KeyPressState::RELEASED };

        bool isMouseInitialized = false;

        glm::vec2 lastMousePosition = glm::vec2(0.0f);
        glm::vec2 mousePosition = glm::vec2(0.0f);
    };
}

#endif // INPUT_MANAGER_H