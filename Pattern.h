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
        int sortingOrder;
        SDL_RendererFlip flip;
        Math::Vector pivot;
        bool visible;
        SDL_Rect srcRect;

        Pattern(
            std::string path = "",
            int sortingOrder = 0,
            bool flipX = false,
            bool flipY = false,
            Math::Vector pivot = Math::Vector::pivotCenter(),
            bool visible = true,
            SDL_Rect srcRect = { 0, 0, 0, 0 })
            : path{ path }, srcRect{ srcRect }, pivot{ pivot }, 
            sortingOrder{ sortingOrder }, visible{ visible } 
        {
            if (flipX && flipY)
                flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
            else if (flipX)
                flip = (SDL_RendererFlip)SDL_FLIP_HORIZONTAL;
            else if (flipY)
                flip = (SDL_RendererFlip)SDL_FLIP_VERTICAL;
            else
                flip = (SDL_RendererFlip)SDL_FLIP_NONE;
        }
    };
}

#endif