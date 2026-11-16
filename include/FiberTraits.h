/**
 * @file FiberTraits.h
 * @brief Serialization traits for fibers.
 */
#ifndef FIBER_TRAITS_H
#define FIBER_TRAITS_H

#include <type_traits>

namespace LOOM::InternalUtilities
{
    class BinaryWriter;
    class BinaryReader;
}

namespace LOOM::Fibers
{
    /**
     * @brief Serialization traits of a fiber type. By default a type is not serializable.
     *
     * Specialize with @c Serializable, @c IsTag, @c Save(BinaryWriter&, const T&) and @c Load(BinaryReader&) to use T in prefabs.
     */
    template<typename T, typename = void>
    struct FiberTraits
    {
        /** @brief True if the type can be stored in prefabs. */
        static constexpr bool Serializable = false;
        /** @brief True if the type is a payload-free marker. */
        static constexpr bool IsTag = false;
    };

    /** @brief Specialization for empty types: serializable tags with no payload. */
    template<typename T>
    struct FiberTraits<T, std::enable_if_t<std::is_empty_v<T>>>
    {
        /** @brief Always true for tags. */
        static constexpr bool Serializable = true;
        /** @brief Always true for tags. */
        static constexpr bool IsTag = true;

        /** @brief Writes nothing. */
        static void Save(InternalUtilities::BinaryWriter&, const T&) {}
        /** @brief Returns a default-constructed tag. */
        static T Load(InternalUtilities::BinaryReader&) { return T{}; }
    };
}

#endif
