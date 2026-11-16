/**
 * @file RectF.h
 * @brief Float rectangle.
 */
#ifndef RECT_F_H
#define RECT_F_H

namespace LOOM::Math
{
    /** @brief Rectangle with float position (x, y) and size (w, h). */
    struct RectF
    {
        /**
         * @var float y
         * Top edge.
         */
        /** @brief Left edge. */
        float x, y;
        /**
         * @var float h
         * Height.
         */
        /** @brief Width. */
        float w, h;
    };
}

#endif
