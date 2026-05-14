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

    template<>
    struct FiberTraits<BoxCollider>
    {
        static constexpr bool Serializable = true;
        static constexpr bool IsTag = false;

        static void Save(InternalUtilities::BinaryWriter& writer, const BoxCollider& bc)
        {
            writer.Write(bc.size.x);
            writer.Write(bc.size.y);
            writer.Write(bc.offset.x);
            writer.Write(bc.offset.y);
            writer.Write(bc.isTrigger);
        }

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
