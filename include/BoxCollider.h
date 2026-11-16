/**
 * @file BoxCollider.h
 * @brief Axis-aligned box collider.
 */
#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "Vector.h"

namespace LOOM::Fibers
{
    /**
     * @brief Axis-aligned box centered on Transform::position + offset. Requires Transform.
     *
     * Also defines the hit area of Hoverable and Clickable.
     */
    struct BoxCollider
    {
        /** @brief Width and height in world units. */
        Math::Vector size;
        /** @brief Box center offset from the transform position. */
        Math::Vector offset;
        /** @brief Triggers report collisions but are neither pushed apart nor stop bodies. */
        bool isTrigger;

        /**
         * @brief Constructs a collider.
         * @param size Box size.
         * @param offset Center offset.
         * @param isTrigger Trigger flag.
         */
        BoxCollider(
            Math::Vector size = Math::Vector::one(),
            Math::Vector offset = Math::Vector::zero(),
            bool isTrigger = false) 
            : size{ size }, offset{ offset }, isTrigger{ isTrigger } 
        {}
    };

    /** @brief Serialization traits for BoxCollider. */
    template<>
    struct FiberTraits<BoxCollider>
    {
        /** @brief True if the type can be stored in prefabs. */
        static constexpr bool Serializable = true;
        /** @brief True if the type is a payload-free marker. */
        static constexpr bool IsTag = false;

        /** @brief Writes the fiber to a BinaryWriter. */
        static void Save(InternalUtilities::BinaryWriter& writer, const BoxCollider& bc)
        {
            writer.Write(bc.size.x);
            writer.Write(bc.size.y);
            writer.Write(bc.offset.x);
            writer.Write(bc.offset.y);
            writer.Write(bc.isTrigger);
        }

        /** @brief Reads the fiber from a BinaryReader. */
        static BoxCollider Load(InternalUtilities::BinaryReader& reader)
        {
            BoxCollider bc;
            reader.Read(bc.size.x);
            reader.Read(bc.size.y);
            reader.Read(bc.offset.x);
            reader.Read(bc.offset.y);
            reader.Read(bc.isTrigger);
            return bc;
        }
    };
}

#endif
