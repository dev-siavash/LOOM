#ifndef PASS_H
#define PASS_H

#include <functional>

#include "ShuttleShed.h"

namespace LOOM
{
    class Loom;

    struct ShuttlePass
    {
        std::string name;
        std::function<void(Loom&, float)> shuttle;
        ShuttleShed shed;
        int order = 0;
    };
}

#endif