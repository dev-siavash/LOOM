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

    template<>
    struct FiberTraits<PhysicsBody>
    {
        static constexpr bool Serializable = true;
        static constexpr bool IsTag = false;

        static void Save(InternalUtilities::BinaryWriter& writer, const PhysicsBody& b)
        {
            writer.Write(b.velocity.x);
            writer.Write(b.velocity.y);
            writer.Write(b.mass);
            writer.Write(b.drag);
            writer.Write(b.applyGravity);
        }

        static PhysicsBody Load(InternalUtilities::BinaryReader& reader)
        {
            PhysicsBody b;
            reader.Read(b.velocity.x);
            reader.Read(b.velocity.y);
            reader.Read(b.mass);
            reader.Read(b.drag);
            reader.Read(b.applyGravity);
            return b;
        }
    };
}

#endif
