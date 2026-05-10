#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include "Vector.h"

namespace LOOM::Fibers
{
    struct PhysicsBody
    {
        Math::Vector velocity;
        float mass;
        float drag;
        bool applyGravity;

        PhysicsBody
        (
            Math::Vector velocity = Math::Vector::zero(),
            float mass = 1.0f,
            float drag = 0.0f,
            bool applyGravity = true)
            : velocity{ velocity }, mass{ mass }, drag{ drag }, applyGravity{ applyGravity } 
        {}
    };
}

#endif
