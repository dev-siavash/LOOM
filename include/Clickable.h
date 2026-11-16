/**
 * @file Clickable.h
 * @brief Mouse click fiber.
 */
#ifndef CLICKABLE_H
#define CLICKABLE_H

namespace LOOM::Fibers
{
    /** @brief Detects mouse clicks on the tow's BoxCollider. Requires Transform and BoxCollider. */
    struct Clickable
    {
        /** @brief (Internal) Click state for the current frame. */
        bool isClicked = false;

        /**
         * @brief Returns true on the frame any mouse button is pressed over the tow.
         * @return True on a click frame.
         */
        bool IsClicked() const
        {
            return isClicked;
        }
    };

    /** @brief Serialization traits for Clickable (stateless). */
    template<>
    struct FiberTraits<Clickable>
    {
        /** @brief True if the type can be stored in prefabs. */
        static constexpr bool Serializable = true;
        /** @brief True if the type is a payload-free marker. */
        static constexpr bool IsTag = false;

        /** @brief Writes the fiber to a BinaryWriter. */
        static void Save(InternalUtilities::BinaryWriter& writer, const Clickable& c)
        {
        }

        /** @brief Reads the fiber from a BinaryReader. */
        static Clickable Load(InternalUtilities::BinaryReader& reader)
        {
            return Clickable();
        }
    };
}

#endif
