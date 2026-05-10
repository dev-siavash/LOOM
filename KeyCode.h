#ifndef KEYCODE_H
#define KEYCODE_H

namespace LOOM
{
    enum class KeyCode
    {
        Unknown = -1, 

        D0, D1, D2, D3, D4, D5, D6, D7, D8, D9,

        A, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

        Space, Return, Escape, Tab, Backspace,
        LeftShift, RightShift, LeftCtrl, RightCtrl, LeftAlt, RightAlt,

        Up, Down, Left, Right,

        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
    };
}

#endif