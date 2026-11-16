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
#include "FontCache.h"
#include "TextCache.h"

namespace LOOM::Shuttles
{
    void RenderShuttle
        (entt::registry& frame, SDL_Renderer* renderer, InternalUtilities::TextureCache& textureCache, 
            InternalUtilities::TextCache& textCache, LoomSettings settings, Math::Vector screenDimensions);
    void InputShuttle
        (entt::registry& frame, Fibers::InputState& inputState, std::function<void(void)>);
    void AudioShuttle
        (entt::registry& frame, Fibers::MusicPlayer& musicPlayer, InternalUtilities::AudioCache& audioCache);
    void PhysicsShuttle
        (entt::registry& frame, Fabric& fabric, Fibers::CollisionEvent& collisionEvent, LoomSettings settings, float deltaTime);
    void UIUpdateShuttle
        (entt::registry& frame, Fibers::InputState& inputState, Math::Vector screenDimensions);
    void TextCacheUpdateShuttle
        (entt::registry& frame, SDL_Renderer* renderer, InternalUtilities::FontCache& fontCache,
            InternalUtilities::TextCache& textCache, Math::Vector screenDimensions);
}

#endif
