#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include <unordered_map>

#include "Vector.h"
#include "KeyCode.h"

namespace LOOM::Fibers
{
    struct InputState
    {
        std::unordered_map<KeyCode, bool> keyStates;
        Math::Vector mousePosition = Math::Vector::zero();
        bool mouseButtonStates[3] = { false, false, false };

        std::unordered_map<KeyCode, bool> prevKeyStates;
        bool prevMouseButtonStates[3] = { false, false, false };

        bool IsKeyDown(KeyCode keyCode) const {
            return keyStates.contains(keyCode) && keyStates.at(keyCode);
        }

        bool IsKeyPressed(KeyCode keyCode) const {
            return IsKeyDown(keyCode) && (!prevKeyStates.contains(keyCode) || !prevKeyStates.at(keyCode));
        }

        bool IsKeyReleased(KeyCode keyCode) const {
            return !IsKeyDown(keyCode) && (prevKeyStates.contains(keyCode) && prevKeyStates.at(keyCode));
        }

        bool IsMouseButtonDown(uint8_t index) const {
            return mouseButtonStates[index];
        }

        bool IsMouseButtonPressed(uint8_t index) const {
            return mouseButtonStates[index] && !prevMouseButtonStates[index];
        }

        bool IsMouseButtonReleased(uint8_t index) const {
            return !mouseButtonStates[index] && prevMouseButtonStates[index];
        }
    };
}

#endif