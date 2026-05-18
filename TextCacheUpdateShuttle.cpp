#include "Transform.h"
#include "Text.h"
#include "InternalFunctions.h"
#include "InternalShuttles.h"

using namespace LOOM::InternalUtilities;

void LOOM::Shuttles::TextCacheUpdateShuttle
    (entt::registry& frame, SDL_Renderer* renderer, FontCache& fontCache, TextCache& textCache, Math::Vector screenDimensions)
{
    auto view = frame.view<Fibers::Transform, Fibers::Text>();
    view.each([&](entt::entity entity, Fibers::Transform& transform, Fibers::Text& text) 
    {
        std::size_t key;
        Hash(key, text.text, text.fontPath, text.fontSize, text.color.r, text.color.g, text.color.b, text.color.a);

        if (key == text.cacheKey)
            return;

        auto font = fontCache.Get(text.fontPath, text.fontSize);
        if (!font)
            return;

        auto surface = TTF_RenderUTF8_Solid(font, text.text.c_str(), { text.color.r, text.color.g, text.color.b, text.color.a });
        if (!surface)
            return;

        auto texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        textCache.Store(key, texture);
        text.cacheKey = key;
    });
}