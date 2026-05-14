#ifndef FIBER_REGISTRY_ENTRY_H
#define FIBER_REGISTRY_ENTRY_H

#include "BinaryReader.h"

namespace LOOM
{
    class Tow;

    struct FiberRegistryEntry
    {
        using LoadFn = void(*)(Tow&, InternalUtilities::BinaryReader&);
        LoadFn load = nullptr;
    };
}

#endif
