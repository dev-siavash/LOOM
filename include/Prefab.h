#ifndef PREFAB_H
#define PREFAB_H

#include <vector>
#include <string>

#include "StoredFiber.h"

namespace LOOM
{
    struct Prefab
    {
        std::string name;
        std::vector<StoredFiber> fibers;
    };
}

#endif
