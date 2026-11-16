/**
 * @file InternalFunctions.h
 * @brief Engine helper functions.
 */
#ifndef HELPERS_H
#define HELPERS_H

#include <functional>
#include <SDL.h>

#include "FiberTypeId.h"
#include "Vector.h"
#include "KeyCode.h"

namespace LOOM::InternalUtilities
{
    /** @brief (Internal) Returns the FiberTypeId of T. */
    template<typename T>
    FiberTypeId TypeId()
    {
        return typeid(T);
    }

    /** @brief (Internal) Terminates the Hash() recursion. */
    inline void Hash(std::size_t& seed) {}

    /** @brief (Internal) Combines the hashes of all arguments into @p seed. */
    template<typename T, typename ...Rest>
    inline void Hash(std::size_t& seed, const T& value, const Rest&... rest)
    {
        seed ^= std::hash<T>{}(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        Hash(seed, rest...);
    }

    /** @brief (Internal) Maps an SDL scancode to a KeyCode (Unknown if unsupported). */
    LOOM::KeyCode ScancodeToKeyCode(SDL_Scancode scancode);

    /** @brief (Internal) Converts screen pixels (origin top-left, y down) to world space (origin center, y up). */
    Math::Vector ScreenToWorldPosition(Math::Vector screenPosition, Math::Vector screenDimensions);

    /** @brief (Internal) Converts world space (origin center, y up) to screen pixels (origin top-left, y down). */
    Math::Vector WorldToScreenPosition(Math::Vector worldPosition, Math::Vector screenDimensions);
}

#endif
