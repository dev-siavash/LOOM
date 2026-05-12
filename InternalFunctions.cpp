#include "InternalFunctions.h"

LOOM::KeyCode LOOM::InternalUtilities::ScancodeToKeyCode(SDL_Scancode scancode)
{
    switch (scancode) {
    case SDL_SCANCODE_0: return KeyCode::D0;
    case SDL_SCANCODE_1: return KeyCode::D1;
    case SDL_SCANCODE_2: return KeyCode::D2;
    case SDL_SCANCODE_3: return KeyCode::D3;
    case SDL_SCANCODE_4: return KeyCode::D4;
    case SDL_SCANCODE_5: return KeyCode::D5;
    case SDL_SCANCODE_6: return KeyCode::D6;
    case SDL_SCANCODE_7: return KeyCode::D7;
    case SDL_SCANCODE_8: return KeyCode::D8;
    case SDL_SCANCODE_9: return KeyCode::D9;

    case SDL_SCANCODE_A: return KeyCode::A;
    case SDL_SCANCODE_B: return KeyCode::B;
    case SDL_SCANCODE_C: return KeyCode::C;
    case SDL_SCANCODE_D: return KeyCode::D;
    case SDL_SCANCODE_E: return KeyCode::E;
    case SDL_SCANCODE_F: return KeyCode::F;
    case SDL_SCANCODE_G: return KeyCode::G;
    case SDL_SCANCODE_H: return KeyCode::H;
    case SDL_SCANCODE_I: return KeyCode::I;
    case SDL_SCANCODE_J: return KeyCode::J;
    case SDL_SCANCODE_K: return KeyCode::K;
    case SDL_SCANCODE_L: return KeyCode::L;
    case SDL_SCANCODE_M: return KeyCode::M;
    case SDL_SCANCODE_N: return KeyCode::N;
    case SDL_SCANCODE_O: return KeyCode::O;
    case SDL_SCANCODE_P: return KeyCode::P;
    case SDL_SCANCODE_Q: return KeyCode::Q;
    case SDL_SCANCODE_R: return KeyCode::R;
    case SDL_SCANCODE_S: return KeyCode::S;
    case SDL_SCANCODE_T: return KeyCode::T;
    case SDL_SCANCODE_U: return KeyCode::U;
    case SDL_SCANCODE_V: return KeyCode::V;
    case SDL_SCANCODE_W: return KeyCode::W;
    case SDL_SCANCODE_X: return KeyCode::X;
    case SDL_SCANCODE_Y: return KeyCode::Y;
    case SDL_SCANCODE_Z: return KeyCode::Z;

    case SDL_SCANCODE_SPACE:     return KeyCode::Space;
    case SDL_SCANCODE_RETURN:    return KeyCode::Return;
    case SDL_SCANCODE_ESCAPE:    return KeyCode::Escape;
    case SDL_SCANCODE_TAB:       return KeyCode::Tab;
    case SDL_SCANCODE_BACKSPACE: return KeyCode::Backspace;

    case SDL_SCANCODE_LSHIFT:    return KeyCode::LeftShift;
    case SDL_SCANCODE_RSHIFT:    return KeyCode::RightShift;
    case SDL_SCANCODE_LCTRL:     return KeyCode::LeftCtrl;
    case SDL_SCANCODE_RCTRL:     return KeyCode::RightCtrl;
    case SDL_SCANCODE_LALT:      return KeyCode::LeftAlt;
    case SDL_SCANCODE_RALT:      return KeyCode::RightAlt;

    case SDL_SCANCODE_UP:    return KeyCode::Up;
    case SDL_SCANCODE_DOWN:  return KeyCode::Down;
    case SDL_SCANCODE_LEFT:  return KeyCode::Left;
    case SDL_SCANCODE_RIGHT: return KeyCode::Right;

    case SDL_SCANCODE_F1:  return KeyCode::F1;
    case SDL_SCANCODE_F2:  return KeyCode::F2;
    case SDL_SCANCODE_F3:  return KeyCode::F3;
    case SDL_SCANCODE_F4:  return KeyCode::F4;
    case SDL_SCANCODE_F5:  return KeyCode::F5;
    case SDL_SCANCODE_F6:  return KeyCode::F6;
    case SDL_SCANCODE_F7:  return KeyCode::F7;
    case SDL_SCANCODE_F8:  return KeyCode::F8;
    case SDL_SCANCODE_F9:  return KeyCode::F9;
    case SDL_SCANCODE_F10: return KeyCode::F10;
    case SDL_SCANCODE_F11: return KeyCode::F11;
    case SDL_SCANCODE_F12: return KeyCode::F12;

    default: return KeyCode::Unknown;
    }
}

LOOM::Math::Vector LOOM::InternalUtilities::ScreenToWorldPosition(LOOM::Math::Vector screenPosition, LOOM::Math::Vector screenDimensions)
{
    return { screenPosition.x - screenDimensions.x / 2.0f, screenDimensions.y / 2.0f - screenPosition.y };
}

LOOM::Math::Vector LOOM::InternalUtilities::WorldToScreenPosition(LOOM::Math::Vector worldPosition, LOOM::Math::Vector screenDimensions)
{
    return { worldPosition.x + screenDimensions.x / 2.0f, screenDimensions.y / 2.0f - worldPosition.y };
}