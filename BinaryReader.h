#ifndef BINARY_READER_H
#define BINARY_READER_H

#include <vector>
#include <string>
#include <cstring>
#include <type_traits>
#include <stdexcept>

#include "FiberTraits.h"

namespace LOOM::InternalUtilities
{
    class BinaryReader
    {
    public:
        explicit BinaryReader(const std::vector<std::byte>& data) : data{ data } {}

        template<typename T>
        void Read(T& value)
        {
            if constexpr (std::is_enum_v<T>)
            {
                std::underlying_type_t<T> temp{};
                Read(temp);
                value = static_cast<T>(temp);
            }
            else if constexpr (std::is_arithmetic_v<T>)
            {
                ReadRaw(value);
            }
            else if constexpr (std::is_same_v<T, std::string>)
            {
                std::uint64_t size{};
                Read(size);
                value.resize(static_cast<std::size_t>(size));
                ReadBytes(value.data(), static_cast<std::size_t>(size));
            }
            else if constexpr (is_std_vector<T>::value)
            {
                using elem_t = typename T::value_type;

                std::uint64_t size;
                Read(size);

                value.clear();
                value.reserve(static_cast<std::size_t>(size));

                for (std::uint64_t i = 0; i < size; i++)
                {
                    elem_t elem{};
                    Read(elem);
                    value.push_back(std::move(elem));
                }
            }
            else
            {
                static_assert(Fibers::FiberTraits<T>::Serializable, "Type not serializable, add a FiberTraits specialization.");
                value = Fibers::FiberTraits<T>::Load(*this);
            }
        }
    private:
        template<typename T>
        struct is_std_vector : std::false_type {};

        template<typename T, typename Alloc>
        struct is_std_vector <std::vector<T, Alloc>> : std::true_type {};

        template<typename T>
        void ReadRaw(T& value)
        {
            static_assert(std::is_trivially_copyable_v<T>, "Raw read called on non trivially copyable type.");

            if (offset + sizeof(T) > data.size())
                throw std::runtime_error("LOOM::BinaryReader underflow.");

            std::memcpy(&value, data.data() + offset, sizeof(T));
            offset += sizeof(T);
        }

        void ReadBytes(void* out, std::size_t size)
        {
            if (offset + size > data.size())
                throw std::runtime_error("LOOM::BinaryReader underflow.");

            std::memcpy(out, data.data() + offset, size);
            offset += size;
        }

        const std::vector<std::byte>& data;
        std::size_t offset = 0;
    };
}


#endif

