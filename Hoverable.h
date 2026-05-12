#ifndef HOVERABLE_H
#define HOVERABLE_H

namespace LOOM::Fibers
{
    struct Hoverable
    {
        bool wasHoveredLastFrame = false;
        bool isHovered = false;

        bool IsHovered() const
        {
            return wasHoveredLastFrame && isHovered;
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
}

#endif
