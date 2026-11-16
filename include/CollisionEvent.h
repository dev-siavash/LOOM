/**
 * @file CollisionEvent.h
 * @brief Collision results service.
 */
#ifndef COLLISION_EVENT_H
#define COLLISION_EVENT_H

#include <vector>

#include "Vector.h"
#include "Tow.h"

namespace LOOM::Fibers
{
    /**
     * @brief Global service listing the collisions of the last physics pass.
     *
     * Fetch with Loom::GetService<Fibers::CollisionEvent>().
     */
    struct CollisionEvent
    {
        /** @brief Two overlapping tows. */
        struct Pair
        {
            /** @brief First tow. */
            Tow a;
            /** @brief Second tow. */
            Tow b;
            /** @brief Unit axis of least penetration, pointing in the direction @c a is pushed out of @c b. */
            Math::Vector normal;
        };

        /** @brief Collisions found this frame; cleared every physics pass. */
        std::vector<Pair> collisionPairs;
    };
}

#endif
