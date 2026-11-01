#ifndef HOVERABLE_H
#define HOVERABLE_H

#include "FiberTraits.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"

namespace LOOM::Fibers
{
    struct Hoverable
    {
        bool wasHoveredLastFrame = false;
        bool isHovered = false;

        bool IsHovered() const
        {
            return isHovered;
        }

        bool EnteredHover() const
        {
            return !wasHoveredLastFrame && isHovered;
        }

        bool ExitedHover() const
        {
            return wasHoveredLastFrame && !isHovered;
        }
    };

    template<>
    struct FiberTraits<Hoverable>
    {
        static constexpr bool Serializable = true;
        static constexpr bool IsTag = false;

        static void Save(InternalUtilities::BinaryWriter& writer, const Hoverable& h)
        {
        }

        static Hoverable Load(InternalUtilities::BinaryReader& reader)
        {
            return Hoverable();
        }
    };
}

#endif
