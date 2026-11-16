/**
 * @file Transform.h
 * @brief Position, rotation and scale.
 */
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector.h"
#include "FiberTraits.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"

namespace LOOM::Fibers
{
    /**
     * @brief Spatial state of a tow.
     *
     * World space: origin at the screen center, +y up.
     */
    struct Transform
    {
        /** @brief World position. */
        Math::Vector position = Math::Vector::zero();
        /** @brief Rotation in degrees (clockwise on screen). */
        float rotation = 0.0f;
        /** @brief Scale multiplier. */
        Math::Vector scale = Math::Vector::one();

        /**
         * @brief Constructs a transform.
         * @param position World position.
         * @param rotation Degrees.
         * @param scale Scale multiplier.
         */
        Transform(Math::Vector position = Math::Vector::zero(), float rotation = 0.0f,
            Math::Vector scale = Math::Vector::one())
            : position{ position }, rotation{ rotation }, scale{ scale } 
        {}
    };

    /** @brief Serialization traits for Transform. */
    template<>
    struct FiberTraits<Transform>
    {
        /** @brief True if the type can be stored in prefabs. */
        static constexpr bool Serializable = true;
        /** @brief True if the type is a payload-free marker. */
        static constexpr bool IsTag = false;

        /** @brief Writes the fiber to a BinaryWriter. */
        static void Save(InternalUtilities::BinaryWriter& writer, const Transform& t)
        {
            writer.Write(t.position.x);
            writer.Write(t.position.y);
            writer.Write(t.rotation);
            writer.Write(t.scale.x);
            writer.Write(t.scale.y);
        }

        /** @brief Reads the fiber from a BinaryReader. */
        static Transform Load(InternalUtilities::BinaryReader& reader)
        {
            Transform t;
            reader.Read(t.position.x);
            reader.Read(t.position.y);
            reader.Read(t.rotation);
            reader.Read(t.scale.x);
            reader.Read(t.scale.y);
            return t;
        }
    };
}

#endif
