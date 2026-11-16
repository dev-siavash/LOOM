/**
 * @file InputState.h
 * @brief Keyboard and mouse state service.
 */
#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include <unordered_map>

#include "Vector.h"
#include "KeyCode.h"

namespace LOOM::Fibers
{
    /**
     * @brief Global input service; fetch with Loom::GetService<Fibers::InputState>().
     *
     * Mouse button indices: 0 left, 1 middle, 2 right.
     */
    struct InputState
    {
        /** @brief Current key states. */
        std::unordered_map<KeyCode, bool> keyStates;
        /** @brief Mouse position in screen pixels (origin top-left). */
        Math::Vector mousePosition = Math::Vector::zero();
        /** @brief Current mouse button states. */
        bool mouseButtonStates[3] = { false, false, false };

        /** @brief (Internal) Key states of the previous frame. */
        std::unordered_map<KeyCode, bool> prevKeyStates;
        /** @brief (Internal) Mouse button states of the previous frame. */
        bool prevMouseButtonStates[3] = { false, false, false };

        /**
         * @brief Returns true while the key is held.
         * @param keyCode Key to test.
         * @return True while held.
         */
        bool IsKeyDown(KeyCode keyCode) const {
            return keyStates.contains(keyCode) && keyStates.at(keyCode);
        }

        /**
         * @brief Returns true on the frame the key goes down.
         * @param keyCode Key to test.
         * @return True on the press frame.
         */
        bool IsKeyPressed(KeyCode keyCode) const {
            return IsKeyDown(keyCode) && (!prevKeyStates.contains(keyCode) || !prevKeyStates.at(keyCode));
        }

        /**
         * @brief Returns true on the frame the key goes up.
         * @param keyCode Key to test.
         * @return True on the release frame.
         */
        bool IsKeyReleased(KeyCode keyCode) const {
            return !IsKeyDown(keyCode) && (prevKeyStates.contains(keyCode) && prevKeyStates.at(keyCode));
        }

        /**
         * @brief Returns true while the button is held.
         * @param index Button index (0-2).
         * @return True while held.
         */
        bool IsMouseButtonDown(uint8_t index) const {
            return mouseButtonStates[index];
        }

        /**
         * @brief Returns true on the frame the button goes down.
         * @param index Button index (0-2).
         * @return True on the press frame.
         */
        bool IsMouseButtonPressed(uint8_t index) const {
            return mouseButtonStates[index] && !prevMouseButtonStates[index];
        }

        /**
         * @brief Returns true on the frame the button goes up.
         * @param index Button index (0-2).
         * @return True on the release frame.
         */
        bool IsMouseButtonReleased(uint8_t index) const {
            return !mouseButtonStates[index] && prevMouseButtonStates[index];
        }
    };
}

#endif