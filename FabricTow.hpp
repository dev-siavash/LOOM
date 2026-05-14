#ifndef FABRIC_TOW_HPP
#define FABRIC_TOW_HPP

#include "Fabric.h"
#include "Tow.h"

template<typename T, typename ...Args>
T& LOOM::Tow::PlyFiber(Args... args) {
    return fabric->frame.emplace<T>(id, args...);
}

template<typename T>
void LOOM::Tow::PlyTag() {
    fabric->frame.emplace<T>(id);
}

template<typename T>
T& LOOM::Tow::FetchFiber() {
    assert(HoldsFiber<T>());
    return fabric->frame.get<T>(id);
}

template<typename T>
bool LOOM::Tow::HoldsFiber() const {
    return fabric->frame.all_of<T>(id);
}

template<typename T>
void LOOM::Tow::SeverFiber() {
    if (HoldsFiber<T>())
        fabric->frame.remove<T>(id);
}

template<typename T>
void LOOM::Fabric::RegisterFiber()
{
    FiberRegistryEntry entry;

    entry.load = [](Tow& tow, InternalUtilities::BinaryReader& reader)
        {
            if constexpr (Fibers::FiberTraits<T>::IsTag)
                tow.template PlyTag<T>();
            else
            {
                T value = Fibers::FiberTraits<T>::Load(reader);
                tow.template PlyFiber<T>(std::move(value));
            }
        };

    fiberRegistry[InternalUtilities::TypeId<T>()] = entry;
}

#endif
