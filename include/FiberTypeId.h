/**
 * @file FiberTypeId.h
 * @brief Fiber type identifier.
 */
#ifndef FIBER_TYPE_ID_H
#define FIBER_TYPE_ID_H

#include <typeindex>

namespace LOOM
{
    /** @brief Runtime identifier of a fiber type. */
    using FiberTypeId = std::type_index;
}

#endif