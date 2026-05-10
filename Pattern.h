#ifndef PATTERN_H
#define PATTERN_H

#include <string>
#include <SDL.h>

#include "Vector.h"

namespace LOOM::Fibers
{
    struct Pattern
    {
        std::string path;
        SDL_Rect srcRect;
        Math::Vector pivot;
        SDL_RendererFlip flip;
        int sortingOrder;
        bool visible;

        Pattern(
            std::string path = "",
            SDL_Rect srcRect = { 0, 0, 0, 0 },
            Math::Vector pivot = Math::Vector::pivotCenter(),
            SDL_RendererFlip flip = SDL_FLIP_NONE,
            int sortingOrder = 0,
            bool visible = true)
            : path{ path }, srcRect{ srcRect }, pivot{ pivot }, flip{ flip }, 
            sortingOrder{ sortingOrder }, visible{ visible } 
        {}
    };
}

#endif