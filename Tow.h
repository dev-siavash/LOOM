#ifndef TOW_H
#define TOW_H

#include <entt/entt.hpp>

#include "Fabric.h"

namespace LOOM
{
    class Tow
    {
        friend class Fabric;
    public:
        template<typename T, typename ...Args>
        T& PlyFiber(Args... args) {
            return fabric->frame.emplace<T>(id, args...);
        }

        template<typename T>
        T& FetchFiber() {
            assert(HoldsFiber<T>());
            return fabric->frame.get<T>(id);
        }

        template<typename T>
        bool HoldsFiber() const {
            return fabric->frame.all_of<T>(id);
        }

        template<typename T>
        void SeverFiber() {
            if (HoldsFiber<T>())
                fabric->frame.remove<T>(id);
        }
    private:
        Tow() : fabric{ nullptr }, id{ entt::entity() } {}
        Tow(Fabric* fabric, entt::entity id) : fabric{ fabric }, id { id } {}

        Fabric* fabric;
        entt::entity id;
    };
}

#endif
