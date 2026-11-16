/**
 * @file Prefab.h
 * @brief Serialized entity template.
 */
#ifndef PREFAB_H
#define PREFAB_H

#include <vector>
#include <string>

#include "StoredFiber.h"

namespace LOOM
{
    /** @brief Named template of serialized fibers, spawned with Fabric::SpawnPrefab(). */
    struct Prefab
    {
        /** @brief Prefab name. */
        std::string name;
        /** @brief Serialized fibers. */
        std::vector<StoredFiber> fibers;
    };
}

#endif
