#ifndef HERLPERS_H
#define HELPERS_H

#include <SDL.h>

#include "Vector.h"
#include "KeyCode.h"

namespace LOOM::InternalUtilities
{
    LOOM::KeyCode ScancodeToKeyCode(SDL_Scancode scancode);

    Math::Vector ScreenToWorldPosition(Math::Vector screenPosition, Math::Vector screenDimensions);

    Math::Vector WorldToScreenPosition(Math::Vector worldPosition, Math::Vector screenDimensions);
}

#endif
