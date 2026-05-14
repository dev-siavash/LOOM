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

        void RegisterPrefab(std::string name, Prefab prefab)
        {
            prefabs[name] = prefab;
        }

        Tow& SpawnPrefab(const std::string& name);

        template<typename T>
        void RegisterFiber();

        PrefabBuilder PreFabricate(std::string name);

        void Clear();

    private:
        entt::registry frame;
        std::unordered_map<std::string, Prefab> prefabs;
        std::unordered_map<std::type_index, FiberRegistryEntry> fiberRegistry;
    };
}

#include "FabricTow.hpp"

#endif

