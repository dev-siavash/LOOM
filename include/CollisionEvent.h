#ifndef COLLISION_EVENT_H
#define COLLISION_EVENT_H

#include <vector>

#include "Vector.h"
#include "Tow.h"

namespace LOOM::Fibers
{
    struct CollisionEvent
    {
        struct Pair
        {
            Tow a;
            Tow b;
            Math::Vector normal;
        };

        std::vector<Pair> collisionPairs;
    };
}

#endif
