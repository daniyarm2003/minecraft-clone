#include "input_manager.h"

namespace Input {
    void InputManager::onKeyPress(int key) {
        if (key < 0 || key >= MAX_KEYS) return;

        this->keysPressed[key] = true;
    }

    void InputManager::onKeyRelease(int key) {
        if (key < 0 || key >= MAX_KEYS) return;

        this->keysPressed[key] = false;
    }

    void InputManager::onMouseMove(double xpos, double ypos) {
        glm::vec2 newMousePosition = glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos));

        this->lastMousePosition = this->isMouseInitialized ? this->mousePosition : newMousePosition;
        this->mousePosition = newMousePosition;

        this->isMouseInitialized = true;
    }

    void InputManager::updateKeyStates() {
        for (int i = 0; i < MAX_KEYS; i++) {
            if (this->keysPressed[i]) {
                if (this->keyStates[i] == KeyPressState::PRESSED || this->keyStates[i] == KeyPressState::HELD) {
                    this->keyStates[i] = KeyPressState::HELD;
                } 
                else {
                    this->keyStates[i] = KeyPressState::PRESSED;
                }
            } 
            else {
                if (this->keyStates[i] == KeyPressState::RELEASED || this->keyStates[i] == KeyPressState::RELEASE_STARTED) {
                    this->keyStates[i] = KeyPressState::RELEASED;
                } 
                else {
                    this->keyStates[i] = KeyPressState::RELEASE_STARTED;
                }
            }
        }
    }

    bool InputManager::isKeyPressed(int key) const {
        if (key < 0 || key >= MAX_KEYS) return false;

        return this->keysPressed[key];
    }

    KeyPressState InputManager::getKeyPressState(int key) const {
        if (key < 0 || key >= MAX_KEYS) return KeyPressState::RELEASED;

        return this->keyStates[key];
    }

    const glm::vec2& InputManager::getMousePosition() const {
        return this->mousePosition;
    }

    glm::vec2 InputManager::getMouseDelta() const {
        return this->mousePosition - this->lastMousePosition;
    }

    void InputManager::resetMouseDelta() {
        this->lastMousePosition = this->mousePosition;
    }
}