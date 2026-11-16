/**
 * @file PrefabBuilder.h
 * @brief Fluent prefab construction.
 */
#ifndef PREFAB_BUILDER_H
#define PREFAB_BUILDER_H

#include "InternalFunctions.h"
#include "FiberTraits.h"
#include "BinaryWriter.h"
#include "Prefab.h"

namespace LOOM
{

    /**
     * @brief Fluent builder for a Prefab. Obtained from Fabric::PreFabricate().
     *
     * @code
     * fabric.PreFabricate("coin")
     *       .PlyFiber<Fibers::Transform>()
     *       .PlyFiber<Fibers::Pattern>("coin.png")
     *       .Register();
     * @endcode
     */
    class PrefabBuilder
    {
        friend class Fabric;
    public:
        /**
         * @brief Serializes a T constructed from @p args into the prefab and registers T.
         * T must be serializable (FiberTraits<T>::Serializable).
         * @return This builder.
         * @param args Arguments forwarded to T's constructor.
         */
        template<typename T, typename ...Args>
        PrefabBuilder& PlyFiber(Args... args)
        {
            static_assert(Fibers::FiberTraits<T>::Serializable, "Non serializable fiber types can't be plied to prefabs.");

            T value(args...);
            InternalUtilities::BinaryWriter writer;
            Fibers::FiberTraits<T>::Save(writer, value);

            prefab.fibers.emplace_back(InternalUtilities::TypeId<T>(), writer.Take());

            fabric->RegisterFiber<T>();

            return *this;
        }

        /**
         * @brief Adds an empty tag fiber to the prefab. T must satisfy FiberTraits<T>::IsTag.
         * @return This builder.
         */
        template<typename T>
        PrefabBuilder& PlyTag()
        {
            static_assert(Fibers::FiberTraits<T>::IsTag, "Fiber not marked as tag can't be plied to a prefab as one.");

            prefab.fibers.emplace_back(InternalUtilities::TypeId<T>(), std::vector<std::byte>());

            fabric->RegisterFiber<T>();

            return *this;
        }

        /**
         * @brief Stores the prefab in the Fabric.
         * @return The finished prefab.
         */
        Prefab Register()
        {
            fabric->RegisterPrefab(prefab.name, prefab);
            return std::move(prefab);
        }

    private: 
        explicit PrefabBuilder(Fabric* fabric, std::string name)
        {
            this->fabric = fabric;
            prefab.name = name;
        }

        Prefab prefab;
        Fabric* fabric;
    };
}

#endif
