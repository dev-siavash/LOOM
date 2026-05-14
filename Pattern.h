#ifndef PATTERN_H
#define PATTERN_H

#include <string>
#include <SDL.h>

#include "Vector.h"
#include "FiberTraits.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"

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

    template<>
    struct FiberTraits<Pattern>
    {
        static constexpr bool Serializable = true;
        static constexpr bool IsTag = false;

        static void Save(InternalUtilities::BinaryWriter& writer, const Pattern& p)
        {
            writer.Write(p.path);
            writer.Write(p.sortingOrder);
            writer.Write(p.flip);
            writer.Write(p.pivot.x);
            writer.Write(p.pivot.y);
            writer.Write(p.visible);
            writer.Write(p.srcRect.x);
            writer.Write(p.srcRect.y);
            writer.Write(p.srcRect.w);
            writer.Write(p.srcRect.h);
        }

        static Pattern Load(InternalUtilities::BinaryReader& reader)
        {
            Pattern p;
            reader.Read(p.path);
            reader.Read(p.sortingOrder);
            reader.Read(p.flip);
            reader.Read(p.pivot.x);
            reader.Read(p.pivot.y);
            reader.Read(p.visible);
            reader.Read(p.srcRect.x);
            reader.Read(p.srcRect.y);
            reader.Read(p.srcRect.w);
            reader.Read(p.srcRect.h);
            return p;
        }
    };
}

#endif