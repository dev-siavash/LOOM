#ifndef INTERNAL_SHUTTLES
#define INTERNAL_SHUTTLES

#include <functional>
#include <entt/entity/registry.hpp>
#include <SDL.h>

#include "MusicPlayer.h"
#include "InputState.h"
#include "CollisionEvent.h"
#include "Loom.h"
#include "TextureCache.h"
#include "AudioCache.h"

namespace LOOM::Shuttles
{
    void RenderShuttle
        (entt::registry& frame, SDL_Renderer* renderer, InternalUtilities::TextureCache& textureCache, LoomSettings settings, Math::Vector screenDimensions);
    void InputShuttle
        (entt::registry& frame, Fibers::InputState& inputState, std::function<void(void)>);
    void AudioShuttle
        (entt::registry& frame, Fibers::MusicPlayer& musicPlayer, InternalUtilities::AudioCache& audioCache);
    void PhysicsShuttle
        (entt::registry& frame, Fabric& fabric, Fibers::CollisionEvent& collisionEvent, LoomSettings settings, float deltaTime);
}

#endif
