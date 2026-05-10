#include "Fabric.h"
#include "Tow.h"

LOOM::Tow LOOM::Fabric::CreateTow() {
    return LOOM::Tow(this, frame.create());
}

void LOOM::Fabric::UnwindTow(Tow tow) {
    frame.destroy(tow.id);
}

void LOOM::Fabric::Clear() {
    frame.clear();
}