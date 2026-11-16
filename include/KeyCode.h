/**
 * @file KeyCode.h
 * @brief Keyboard key codes.
 */
#ifndef KEYCODE_H
#define KEYCODE_H

namespace LOOM
{
    /** @brief Supported keyboard keys. Unmapped keys report Unknown. */
    enum class KeyCode
    {
        Unknown = -1, 

        /** @brief Number row keys. */
        D0, D1, D2, D3, D4, D5, D6, D7, D8, D9,

        /** @brief Letter keys. */
        A, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

        /** @brief Control keys. */
        Space, Return, Escape, Tab, Backspace,
        /** @brief Modifier keys. */
        LeftShift, RightShift, LeftCtrl, RightCtrl, LeftAlt, RightAlt,

        /** @brief Arrow keys. */
        Up, Down, Left, Right,

        /** @brief Function keys. */
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
    };
}

#endif