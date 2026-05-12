#ifndef INTERNAL_SHUTTLES
#define INTERNAL_SHUTTLES

#include <functional>
#include <entt/entity/registry.hpp>
#include <SDL.h>

#include "Loom.h"
#include "TextureCache.h"
#include "AudioCache.h"

namespace LOOM::Shuttles
{
    void RenderShuttle
        (entt::registry& frame, SDL_Renderer* renderer, InternalUtilities::TextureCache& textureCache, LoomSettings settings, Math::Vector screenDimensions);
    void InputShuttle
        (entt::registry& frame, std::function<void(void)>);
    void AudioShuttle
        (entt::registry& frame, InternalUtilities::AudioCache& audioCache);
    void PhysicsShuttle
        (entt::registry& frame, Fabric& fabric, LoomSettings settings, float deltaTime);
}

#endif
