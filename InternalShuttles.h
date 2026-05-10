#ifndef INTERNAL_SHUTTLES
#define INTERNAL_SHUTTLES

#include <functional>
#include <entt/entity/registry.hpp>
#include <SDL.h>

#include "TextureCache.h"
#include "AudioCache.h"

namespace LOOM::Shuttles
{
    class Fabric;

    void RenderShuttle(entt::registry& frame, SDL_Renderer* renderer, InternalUtilities::TextureCache& textureCache);
    void InputShuttle(entt::registry& frame, std::function<void(void)>);
    void AudioShuttle(entt::registry& frame, InternalUtilities::AudioCache& audioCache);
}

#endif
