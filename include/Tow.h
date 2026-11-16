/**
 * @file Tow.h
 * @brief Handle to an entity that holds fibers.
 */
#ifndef TOW_H
#define TOW_H

#include <entt/entt.hpp>

namespace LOOM
{
    /**
     * @brief Lightweight, copyable handle to an entity. Holds at most one fiber of each type.
     *
     * Obtain tows from Fabric (CreateTow(), FetchAllTowsOf(), SpawnPrefab()...).
     */
    class Tow
    {
        friend class Fabric;
    public:
        /**
         * @brief Constructs a fiber of type T from @p args and attaches it.
         * @tparam T Fiber type.
         * @return Reference to the new fiber.
         * @param args Constructor arguments for T.
         */
        template<typename T, typename ...Args>
        T& PlyFiber(Args... args);

        /**
         * @brief Attaches an empty marker fiber. Asserts if already attached.
         * @tparam T Tag type.
         */
        template<typename T>
        void PlyTag();

        /**
         * @brief Returns the fiber of type T. Asserts if the tow does not hold it.
         * @tparam T Fiber type.
         * @return Reference to the fiber.
         */
        template<typename T>
        T& FetchFiber();

        /**
         * @brief Returns true if the tow holds a fiber of type T.
         * @tparam T Fiber type.
         * @return True if present.
         */
        template<typename T>
        bool HoldsFiber() const;

        /**
         * @brief Removes the fiber of type T. Does nothing if absent.
         * @tparam T Fiber type.
         */
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
