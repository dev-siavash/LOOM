#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector.h"

namespace LOOM::Fibers
{
    struct Transform
    {
        Math::Vector position = Math::Vector::zero();
        float rotation = 0.0f;
        Math::Vector scale = Math::Vector::one();

        Transform(Math::Vector position = Math::Vector::zero(), float rotation = 0.0f,
            Math::Vector scale = Math::Vector::one())
            : position{ position }, rotation{ rotation }, scale{ scale } 
        {}
    };
}

#endif
