#ifndef FABRIC_H
#define FABRIC_H

#include <vector>
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
            rawView.each([&](entt::entity entity, Fibers...) {
                result.push_back(Tow(this, entity));
            });

            return result;
        }

        template<typename ...Fibers>
        Tow FetchTowOf() {
            auto rawView = frame.view<Fibers...>();
            return Tow(this, rawView.front());
        }

        void Clear();

    private:
        entt::registry frame;
    };
}

#endif

