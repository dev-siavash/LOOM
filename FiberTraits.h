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
    template<typename T, typename = void>
    struct FiberTraits
    {
        static constexpr bool Serializable = false;
        static constexpr bool IsTag = false;
    };

    template<typename T>
    struct FiberTraits<T, std::enable_if_t<std::is_empty_v<T>>>
    {
        static constexpr bool Serializable = true;
        static constexpr bool IsTag = true;

        static void Save(InternalUtilities::BinaryWriter&, const T&) {}
        static T Load(InternalUtilities::BinaryReader&) { return T{}; }
    };
}

#endif
