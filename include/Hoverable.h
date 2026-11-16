/**
 * @file Hoverable.h
 * @brief Mouse hover fiber.
 */
#ifndef HOVERABLE_H
#define HOVERABLE_H

#include "FiberTraits.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"

namespace LOOM::Fibers
{
    /** @brief Tracks whether the mouse is over the tow's BoxCollider. Requires Transform and BoxCollider. */
    struct Hoverable
    {
        /** @brief (Internal) Previous frame's hover state. */
        bool wasHoveredLastFrame = false;
        /** @brief (Internal) Current hover state. */
        bool isHovered = false;

        /**
         * @brief Returns true while the mouse is over the tow.
         * @return True while hovered.
         */
        bool IsHovered() const
        {
            return isHovered;
        }

        /**
         * @brief Returns true on the frame the mouse enters the tow.
         * @return True on the entering frame.
         */
        bool EnteredHover() const
        {
            return !wasHoveredLastFrame && isHovered;
        }

        /**
         * @brief Returns true on the frame the mouse leaves the tow.
         * @return True on the leaving frame.
         */
        bool ExitedHover() const
        {
            return wasHoveredLastFrame && !isHovered;
        }
    };

    /** @brief Serialization traits for Hoverable (stateless). */
    template<>
    struct FiberTraits<Hoverable>
    {
        /** @brief True if the type can be stored in prefabs. */
        static constexpr bool Serializable = true;
        /** @brief True if the type is a payload-free marker. */
        static constexpr bool IsTag = false;

        /** @brief Writes the fiber to a BinaryWriter. */
        static void Save(InternalUtilities::BinaryWriter& writer, const Hoverable& h)
        {
        }

        /** @brief Reads the fiber from a BinaryReader. */
        static Hoverable Load(InternalUtilities::BinaryReader& reader)
        {
            return Hoverable();
        }
    };
}

#endif
