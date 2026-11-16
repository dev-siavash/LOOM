/**
 * @file PhysicsBody.h
 * @brief Dynamic body fiber.
 */
#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include "Vector.h"

namespace LOOM::Fibers
{
    /**
     * @brief Makes a tow dynamic: integrates velocity, gravity and drag. Requires Transform.
     *
     * Add a BoxCollider for collisions; colliders without a PhysicsBody are static.
     */
    struct PhysicsBody
    {
        /** @brief Velocity in units/s. */
        Math::Vector velocity;
        /** @brief Relative mass; the lighter body is pushed more in dynamic-dynamic collisions. */
        float mass;
        /** @brief Linear damping; 0 means none. */
        float drag;
        /** @brief Applies LoomSettings::globalGravityScale when true. */
        bool applyGravity;

        /**
         * @brief Constructs a body.
         * @param velocity Initial velocity.
         * @param mass Relative mass.
         * @param drag Linear damping.
         * @param applyGravity Use global gravity.
         */
        PhysicsBody
        (
            Math::Vector velocity = Math::Vector::zero(),
            float mass = 1.0f,
            float drag = 0.0f,
            bool applyGravity = true)
            : velocity{ velocity }, mass{ mass }, drag{ drag }, applyGravity{ applyGravity } 
        {}
    };

    /** @brief Serialization traits for PhysicsBody. */
    template<>
    struct FiberTraits<PhysicsBody>
    {
        /** @brief True if the type can be stored in prefabs. */
        static constexpr bool Serializable = true;
        /** @brief True if the type is a payload-free marker. */
        static constexpr bool IsTag = false;

        /** @brief Writes the fiber to a BinaryWriter. */
        static void Save(InternalUtilities::BinaryWriter& writer, const PhysicsBody& b)
        {
            writer.Write(b.velocity.x);
            writer.Write(b.velocity.y);
            writer.Write(b.mass);
            writer.Write(b.drag);
            writer.Write(b.applyGravity);
        }

        /** @brief Reads the fiber from a BinaryReader. */
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
