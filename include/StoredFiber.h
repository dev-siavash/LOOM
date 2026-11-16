/**
 * @file StoredFiber.h
 * @brief Serialized fiber record.
 */
#ifndef STORED_FIBER_H
#define STORED_FIBER_H

#include <vector>
#include <typeindex>

namespace LOOM
{
    /** @brief A fiber type paired with its serialized bytes. */
    struct StoredFiber
    {
        /** @brief Fiber type. */
        std::type_index type = typeid(void);
        /** @brief Serialized data. */
        std::vector<std::byte> payload;

        StoredFiber() = default;
        /** @brief Constructs a record from a type and its serialized bytes. */
        StoredFiber(std::type_index type, std::vector<std::byte> payload)
            : type{ type }, payload{ payload } {}
    };
}

#endif
