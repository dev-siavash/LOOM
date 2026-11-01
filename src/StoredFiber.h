#ifndef STORED_FIBER_H
#define STORED_FIBER_H

#include <vector>
#include <typeindex>

namespace LOOM
{
    struct StoredFiber
    {
        std::type_index type = typeid(void);
        std::vector<std::byte> payload;

        StoredFiber() = default;
        StoredFiber(std::type_index type, std::vector<std::byte> payload)
            : type{ type }, payload{ payload } {}
    };
}

#endif
