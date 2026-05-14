#ifndef HELPERS_H
#define HELPERS_H

#include <typeindex>
#include <SDL.h>

#include "Vector.h"
#include "KeyCode.h"

using FiberTypeId = std::type_index;

namespace LOOM::InternalUtilities
{
    template<typename T>
    FiberTypeId TypeId()
    {
        return typeid(T);
    }

    LOOM::KeyCode ScancodeToKeyCode(SDL_Scancode scancode);

    Math::Vector ScreenToWorldPosition(Math::Vector screenPosition, Math::Vector screenDimensions);

    Math::Vector WorldToScreenPosition(Math::Vector worldPosition, Math::Vector screenDimensions);
}

#endif
