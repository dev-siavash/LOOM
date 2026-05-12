#ifndef PASS_H
#define PASS_H

#include <functional>

#include "ShuttleShed.h"

namespace LOOM
{
    struct ShuttlePass
    {
        std::function<void(Fabric&, Tow, float)> shuttle;
        ShuttleShed shed;
        int order = 0;
    };
}

#endif