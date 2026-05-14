#include "Fabric.h"
#include "Tow.h"
#include "PrefabBuilder.h"

LOOM::Tow LOOM::Fabric::CreateTow() {
    return LOOM::Tow(this, frame.create());
}

void LOOM::Fabric::UnwindTow(Tow tow) {
    frame.destroy(tow.id);
}

LOOM::Tow& LOOM::Fabric::SpawnPrefab(const std::string& name)
{
    auto prefabIt = prefabs.find(name);
    if (prefabIt == prefabs.end())
        throw std::runtime_error("Can't spawn prefab " + name + ". Prefab not found.");

    Tow tow = CreateTow();
    for (const auto& stored : prefabIt->second.fibers)
    {
        auto regIt = fiberRegistry.find(stored.type);
        if (regIt == fiberRegistry.end())
            throw std::runtime_error("Can't spawn prefab " + name + ". Fiber type attached is not registered.");

        InternalUtilities::BinaryReader reader(stored.payload);
        regIt->second.load(tow, reader);
    }

    return tow;
}

LOOM::PrefabBuilder LOOM::Fabric::PreFabricate(std::string name)
{
    return PrefabBuilder(this, name);
}

void LOOM::Fabric::Clear() {
    frame.clear();
}