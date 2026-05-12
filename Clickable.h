#ifndef CLICKABLE_H
#define CLICKABLE_H

namespace LOOM::Fibers
{
    struct Clickable
    {
        bool wasHeldLastFrame = false;
        bool isHeld = false;

        bool IsClicked() const
        {
            return !wasHeldLastFrame && isHeld;
        }

        bool IsReleased() const
        {
            return wasHeldLastFrame && !isHeld;
        }
    };
}

#endif
