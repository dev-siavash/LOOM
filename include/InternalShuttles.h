/**
 * @file InternalShuttles.h
 * @brief Built-in shuttles.
 */
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
    /** @brief (Internal) Draws patterns by sorting order, then text, then optional collider outlines, and presents the frame. */
    void RenderShuttle
        (entt::registry& frame, SDL_Renderer* renderer, InternalUtilities::TextureCache& textureCache, 
            InternalUtilities::TextCache& textCache, LoomSettings settings, Math::Vector screenDimensions);
    /** @brief (Internal) Polls SDL events and updates InputState; calls the callback when the window is closed. */
    void InputShuttle
        (entt::registry& frame, Fibers::InputState& inputState, std::function<void(void)>);
    /** @brief (Internal) Applies MusicPlayer and AudioPlayer requests. */
    void AudioShuttle
        (entt::registry& frame, Fibers::MusicPlayer& musicPlayer, InternalUtilities::AudioCache& audioCache);
    /** @brief (Internal) Integrates PhysicsBody, detects AABB collisions, resolves them and fills CollisionEvent. */
    void PhysicsShuttle
        (entt::registry& frame, Fabric& fabric, Fibers::CollisionEvent& collisionEvent, LoomSettings settings, float deltaTime);
    /** @brief (Internal) Updates Hoverable and Clickable from the mouse position. */
    void UIUpdateShuttle
        (entt::registry& frame, Fibers::InputState& inputState, Math::Vector screenDimensions);
    /** @brief (Internal) Renders new or changed Text into the text cache. */
    void TextCacheUpdateShuttle
        (entt::registry& frame, SDL_Renderer* renderer, InternalUtilities::FontCache& fontCache,
            InternalUtilities::TextCache& textCache, Math::Vector screenDimensions);
}

#endif
