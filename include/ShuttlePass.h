/**
 * @file ShuttlePass.h
 * @brief Scheduled system entry.
 */
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

    /** @brief A named shuttle bound to a shed and an order. */
    struct ShuttlePass
    {
        /** @brief System callback: (engine, delta time in seconds). */
        using Shuttle = std::function<void(Loom&, float)>;
        /** @brief System callback: (engine, matching tows, delta time in seconds). */
        using BoundShuttle = std::function<void(Loom&, std::vector<Tow>&, float)>;

        /** @brief Identifier used for removal. */
        std::string name;
        /** @brief The callback. */
        Shuttle shuttle;
        /** @brief Phase the callback runs in. */
        ShuttleShed shed;
        /** @brief Position inside the shed; lower runs first. */
        int order;

        /** @brief Constructs a pass from its name, callback, shed and order. */
        ShuttlePass(std::string name, Shuttle shuttle, ShuttleShed shed, int order = 0)
            : name{ name }, shuttle{ shuttle }, shed{ shed }, order{ order }
        {}
    };
}

#endif