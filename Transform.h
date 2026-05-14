#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector.h"
#include "FiberTraits.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"

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

    template<>
    struct FiberTraits<Transform>
    {
        static constexpr bool Serializable = true;
        static constexpr bool IsTag = false;

        static void Save(InternalUtilities::BinaryWriter& writer, const Transform& t)
        {
            writer.Write(t.position.x);
            writer.Write(t.position.y);
            writer.Write(t.rotation);
            writer.Write(t.scale.x);
            writer.Write(t.scale.y);
        }

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
