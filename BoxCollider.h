#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "Vector.h"

namespace LOOM::Fibers
{
    struct BoxCollider
    {
        Math::Vector size;
        Math::Vector offset;
        bool isTrigger;

        BoxCollider(
            Math::Vector size = Math::Vector::one(),
            Math::Vector offset = Math::Vector::zero(),
            bool isTrigger = false) 
            : size{ size }, offset{ offset }, isTrigger{ isTrigger } 
        {}
    };
}

#endif
