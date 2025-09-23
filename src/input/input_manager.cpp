#include "input_manager.h"

namespace Input {
    void InputManager::onKeyPress(int key) {
        if (key < 0 || key >= MAX_KEYS) {
            return;
        }

        this->keysPressed[key] = true;
    }

    void InputManager::onKeyRelease(int key) {
        if (key < 0 || key >= MAX_KEYS) {
            return;
        }

        this->keysPressed[key] = false;
    }

    void InputManager::onMouseButtonPress(int mouseButton) {
        if (mouseButton < 0 || mouseButton >= MAX_MOUSE_BUTTONS) {
            return;
        }

        this->mouseButtonsPressed[mouseButton] = true;
    }

    void InputManager::onMouseButtonRelease(int mouseButton) {
        if (mouseButton < 0 || mouseButton >= MAX_MOUSE_BUTTONS) {
            return;
        }

        this->mouseButtonsPressed[mouseButton] = false;
    }

    void InputManager::onMouseMove(double xpos, double ypos) {
        glm::vec2 newMousePosition = glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos));

        this->lastMousePosition = this->isMouseInitialized ? this->mousePosition : newMousePosition;
        this->mousePosition = newMousePosition;

        this->isMouseInitialized = true;
    }

    void InputManager::updateButtonStates() {
        for (int i = 0; i < MAX_KEYS; i++) {
            if (this->keysPressed[i]) {
                if (this->keyStates[i] == ButtonPressState::PRESSED || this->keyStates[i] == ButtonPressState::HELD) {
                    this->keyStates[i] = ButtonPressState::HELD;
                } 
                else {
                    this->keyStates[i] = ButtonPressState::PRESSED;
                }
            } 
            else {
                if (this->keyStates[i] == ButtonPressState::RELEASED || this->keyStates[i] == ButtonPressState::RELEASE_STARTED) {
                    this->keyStates[i] = ButtonPressState::RELEASED;
                } 
                else {
                    this->keyStates[i] = ButtonPressState::RELEASE_STARTED;
                }
            }
        }

        for(int i = 0; i < MAX_MOUSE_BUTTONS; i++) {
            if (this->mouseButtonsPressed[i]) {
                if (this->mouseButtonStates[i] == ButtonPressState::PRESSED || this->mouseButtonStates[i] == ButtonPressState::HELD) {
                    this->mouseButtonStates[i] = ButtonPressState::HELD;
                } 
                else {
                    this->mouseButtonStates[i] = ButtonPressState::PRESSED;
                }
            } 
            else {
                if (this->mouseButtonStates[i] == ButtonPressState::RELEASED || this->mouseButtonStates[i] == ButtonPressState::RELEASE_STARTED) {
                    this->mouseButtonStates[i] = ButtonPressState::RELEASED;
                } 
                else {
                    this->mouseButtonStates[i] = ButtonPressState::RELEASE_STARTED;
                }
            }
        }
    }

    bool InputManager::isKeyPressed(int key) const {
        if (key < 0 || key >= MAX_KEYS) {
            return false;
        }

        return this->keysPressed[key];
    }

    ButtonPressState InputManager::getKeyPressState(int key) const {
        if (key < 0 || key >= MAX_KEYS) {
            return ButtonPressState::RELEASED;
        }

        return this->keyStates[key];
    }

    bool InputManager::isMouseButtonPressed(int mouseButton) const {
        if (mouseButton < 0 || mouseButton >= MAX_MOUSE_BUTTONS) {
            return false;
        }

        return this->mouseButtonsPressed[mouseButton];
    }

    ButtonPressState InputManager::getMouseButtonPressState(int mouseButton) const {
        if (mouseButton < 0 || mouseButton >= MAX_MOUSE_BUTTONS) {
            return ButtonPressState::RELEASED;
        }

        return this->mouseButtonStates[mouseButton];
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