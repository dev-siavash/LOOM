#ifndef PASS_H
#define PASS_H

#include <vector>
#include <string>
#include <functional>

#include "ShuttleShed.h"

namespace LOOM
{
    class Loom;
    class Tow;

    struct ShuttlePass
    {
        using Shuttle = std::function<void(Loom&, float)>;
        using QueryShuttle = std::function<void(Loom&, std::vector<Tow>, float)>;

        std::string name;
        Shuttle shuttle;
        ShuttleShed shed;
        int order;

        ShuttlePass(std::string name, Shuttle shuttle, ShuttleShed shed, int order = 0)
            : name{ name }, shuttle{ shuttle }, shed{ shed }, order{ order }
        {}
    };
}

#endif