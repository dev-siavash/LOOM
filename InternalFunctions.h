#ifndef HELPERS_H
#define HELPERS_H

#include <functional>
#include <SDL.h>

#include "FiberTypeId.h"
#include "Vector.h"
#include "KeyCode.h"

namespace LOOM::InternalUtilities
{
    template<typename T>
    FiberTypeId TypeId()
    {
        return typeid(T);
    }

    inline void Hash(std::size_t& seed) {}

    template<typename T, typename ...Rest>
    inline void Hash(std::size_t& seed, const T& value, const Rest&... rest)
    {
        seed ^= std::hash<T>{}(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        Hash(seed, rest...);
    }

    LOOM::KeyCode ScancodeToKeyCode(SDL_Scancode scancode);

    Math::Vector ScreenToWorldPosition(Math::Vector screenPosition, Math::Vector screenDimensions);

    Math::Vector WorldToScreenPosition(Math::Vector worldPosition, Math::Vector screenDimensions);
}

#endif
