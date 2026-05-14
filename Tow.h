#ifndef TOW_H
#define TOW_H

#include <entt/entt.hpp>

namespace LOOM
{
    class Tow
    {
        friend class Fabric;
    public:
        template<typename T, typename ...Args>
        T& PlyFiber(Args... args);

        template<typename T>
        void PlyTag();

        template<typename T>
        T& FetchFiber();

        template<typename T>
        bool HoldsFiber() const;

        template<typename T>
        void SeverFiber();
    private:
        Tow() : fabric{ nullptr }, id{ entt::entity() } {}
        Tow(Fabric* fabric, entt::entity id) : fabric{ fabric }, id { id } {}

        Fabric* fabric;
        entt::entity id;
    };
}

#include "FabricTow.hpp"

#endif
