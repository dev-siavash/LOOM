#ifndef CLICKABLE_H
#define CLICKABLE_H

namespace LOOM::Fibers
{
    struct Clickable
    {
        bool isClicked = false;

        bool IsClicked() const
        {
            return isClicked;
        }
    };

    template<>
    struct FiberTraits<Clickable>
    {
        static constexpr bool Serializable = true;
        static constexpr bool IsTag = false;

        static void Save(InternalUtilities::BinaryWriter& writer, const Clickable& c)
        {
        }

        static Clickable Load(InternalUtilities::BinaryReader& reader)
        {
            return Clickable();
        }
    };
}

#endif
