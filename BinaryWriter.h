#ifndef BINARY_WRITER_H
#define BINARY_WRITER_H

#include <vector>
#include <string>
#include <type_traits>

#include "FiberTraits.h"

namespace LOOM::InternalUtilities
{
    class BinaryWriter
    {
    public: 
        template<typename T>
        void Write(const T& value)
        {
            if constexpr (std::is_enum_v<T>)
            {
                Write(static_cast<std::underlying_type_t<T>>(value));
            }
            else if constexpr (std::is_arithmetic_v<T>)
            {
                WriteRaw(value);
            }
            else if constexpr (std::is_same_v<T, std::string>)
            {
                auto size = static_cast<std::uint64_t>(value.size());
                Write(size);
                WriteBytes(value.data(), value.size());
            }
            else if constexpr (is_std_vector<T>::value)
            {
                auto size = static_cast<std::uint64_t>(value.size());
                Write(size);
                for (const auto& e : value)
                    Write(e);
            }
            else
            {
                static_assert(LOOM::Fibers::template FiberTraits<T>::Serializable, "Type not serializable, add a FiberTraits specialization.");
                Fibers::FiberTraits<T>::Save(*this, value);
            }
        }

        std::vector<std::byte> Take()
        {
            return std::move(buffer);
        }

    private:
        template<typename T>
        struct is_std_vector : std::false_type {};

        template<typename T, typename Alloc>
        struct is_std_vector <std::vector<T, Alloc>> : std::true_type {};

        template<typename T>
        void WriteRaw(const T& value)
        {
            static_assert(std::is_trivially_copyable_v<T>, "Raw write called on non trivially copyable type.");

            const auto* begin = reinterpret_cast<const std::byte*>(&value);
            buffer.insert(buffer.end(), begin, begin + sizeof(T));
        }

        void WriteBytes(const void* data, std::size_t size)
        {
            const auto* begin = reinterpret_cast<const std::byte*>(data);
            buffer.insert(buffer.end(), begin, begin + size);
        }

        std::vector<std::byte> buffer;
    };
}


#endif
