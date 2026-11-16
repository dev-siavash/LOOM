/**
 * @file Pattern.h
 * @brief Sprite fiber.
 */
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
    /**
     * @brief Sprite drawn at the tow's Transform. Requires Transform.
     *
     * Drawn size is the source rectangle times Transform::scale. Missing textures are skipped.
     */
    struct Pattern
    {
        /** @brief Image file path (loaded once and cached). */
        std::string path;
        /** @brief Draw order; lower values are drawn first. */
        int sortingOrder;
        /** @brief SDL flip flags, set from the constructor's flipX/flipY. */
        SDL_RendererFlip flip;
        /** @brief Anchor in sprite space (0..1, origin top-left); see Math::Vector::pivotCenter() and friends. */
        Math::Vector pivot;
        /** @brief Hides the sprite when false. */
        bool visible;
        /** @brief Region of the image to draw; zero width and height selects the whole image. */
        SDL_Rect srcRect;

        /**
         * @brief Constructs a sprite.
         * @param path Image path.
         * @param sortingOrder Draw order.
         * @param flipX Mirror horizontally.
         * @param flipY Mirror vertically.
         * @param pivot Anchor point.
         * @param visible Initial visibility.
         * @param srcRect Source region.
         */
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

    /** @brief Serialization traits for Pattern. */
    template<>
    struct FiberTraits<Pattern>
    {
        /** @brief True if the type can be stored in prefabs. */
        static constexpr bool Serializable = true;
        /** @brief True if the type is a payload-free marker. */
        static constexpr bool IsTag = false;

        /** @brief Writes the fiber to a BinaryWriter. */
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

        /** @brief Reads the fiber from a BinaryReader. */
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