#ifndef FABRIC_H
#define FABRIC_H

#include <vector>
#include <optional>
#include <entt/entt.hpp>

namespace LOOM
{
    class Fabric
    {
        friend class Loom;
        friend class Tow;
    public:
        Tow CreateTow();
        void UnwindTow(Tow);

        template<typename ...Fibers>
        std::vector<Tow> FetchAllTowsOf() {
            std::vector<Tow> result;

            auto rawView = frame.view<Fibers...>();
            for (auto iterator = rawView.begin(); iterator != rawView.end(); iterator++)
                result.push_back(Tow(this, *iterator));

            return result;
        }

        template<typename ...Fibers>
        std::optional<Tow> FetchTowOf() {
            auto rawView = frame.view<Fibers...>();
            if (rawView.empty())
                return std::nullopt;
            return Tow(this, rawView.front());
        }

        void Clear();

    private:
        entt::registry frame;
    };
}

#endif

