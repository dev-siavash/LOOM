/**
 * @file Fabric.h
 * @brief Container of all tows, fibers and prefabs.
 */
#ifndef FABRIC_H
#define FABRIC_H

#include <typeindex>
#include <unordered_map>
#include <vector>
#include <string>
#include <optional>
#include <entt/entt.hpp>

#include "InternalFunctions.h"
#include "BinaryReader.h"
#include "FiberTraits.h"
#include "FiberRegistryEntry.h"
#include "Prefab.h"

namespace LOOM
{
    class PrefabBuilder;

    /**
     * @brief The world. Owns every Tow, its fibers and the registered prefabs.
     *
     * Non-copyable and non-movable.
     */
    class Fabric
    {
        friend class Loom;
        friend class Tow;
    public:
        Fabric() {} 

        Fabric(const Fabric&) = delete;
        Fabric(Fabric&&) = delete;
        Fabric& operator=(const Fabric&) = delete;
        Fabric& operator=(Fabric&&) = delete;

        /**
         * @brief Creates an empty tow.
         * @return The new tow.
         */
        Tow CreateTow();
        /** @brief Destroys a tow and all its fibers. The handle must not be used afterwards. */
        void UnwindTow(Tow);

        /**
         * @brief Returns every tow holding all of the given fibers.
         * @tparam Fibers Required fiber types.
         * @return Matching tows; empty if none.
         */
        template<typename ...Fibers>
        std::vector<Tow> FetchAllTowsOf() {
            std::vector<Tow> result;

            auto rawView = frame.view<Fibers...>();
            for (auto iterator = rawView.begin(); iterator != rawView.end(); iterator++)
                result.push_back(Tow(this, *iterator));

            return result;
        }

        /**
         * @brief Returns the first tow holding all of the given fibers, or std::nullopt.
         * @tparam Fibers Required fiber types.
         * @return The tow, or std::nullopt.
         */
        template<typename ...Fibers>
        std::optional<Tow> FetchTowOf() {
            auto rawView = frame.view<Fibers...>();
            if (rawView.front() == entt::null)
                return std::nullopt;
            return Tow(this, rawView.front());
        }

        /**
         * @brief Returns a pointer to the first fiber of type T in the Fabric, or nullptr if none exists.
         * @return Pointer to the fiber, or nullptr.
         */
        template<typename T>
        T* FirstFiber() {
            auto rawView = frame.view<T>();
            if (rawView.empty())
                return nullptr;

            return &(frame.get<T>(rawView.front()));
        }

        /**
         * @brief Stores a prefab under @p name, replacing any prefab with that name.
         * @param name Prefab name.
         * @param prefab Prefab to store.
         */
        void RegisterPrefab(std::string name, Prefab prefab)
        {
            prefabs[name] = prefab;
        }

        /**
         * @brief Creates a tow from a registered prefab.
         * @param name Prefab name.
         * @throws std::runtime_error If the prefab or one of its fiber types is not registered.
         * @return The spawned tow.
         */
        Tow SpawnPrefab(const std::string& name);

        /** @brief Registers fiber type T so prefabs can load it. Done automatically by PrefabBuilder. */
        template<typename T>
        void RegisterFiber();

        /**
         * @brief Starts building a prefab named @p name. Finish with PrefabBuilder::Register().
         * @param name Prefab name.
         * @return A builder for the prefab.
         */
        PrefabBuilder PreFabricate(std::string name);

        /** @brief Destroys all tows, including the engine's service tow. */
        void Clear();

    private:
        entt::registry frame;
        std::unordered_map<std::string, Prefab> prefabs;
        std::unordered_map<std::type_index, FiberRegistryEntry> fiberRegistry;
    };
}

#include "FabricTow.hpp"

#endif

