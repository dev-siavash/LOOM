/**
 * @file FiberRegistryEntry.h
 * @brief Fabric fiber loader entry.
 */
#ifndef FIBER_REGISTRY_ENTRY_H
#define FIBER_REGISTRY_ENTRY_H

#include "BinaryReader.h"

namespace LOOM
{
    class Tow;

    /** @brief (Internal) Per-type loader used by Fabric::SpawnPrefab(). */
    struct FiberRegistryEntry
    {
        /** @brief Loader signature: deserializes a fiber from the reader and plies it to the tow. */
        using LoadFn = void(*)(Tow&, InternalUtilities::BinaryReader&);
        /** @brief Loader for the fiber type; null if unset. */
        LoadFn load = nullptr;
    };
}

#endif
