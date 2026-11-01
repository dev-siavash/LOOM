#include <algorithm>
#include <vector>

#include "Transform.h"
#include "Pattern.h"
#include "Text.h"
#include "BoxCollider.h"
#include "InternalShuttles.h"
#include "InternalFunctions.h"

using namespace LOOM::InternalUtilities;

namespace LOOM::Shuttles
{
    void RenderShuttle
        (entt::registry& frame, SDL_Renderer* renderer, TextureCache& textureCache, 
            TextCache& textCache, LoomSettings settings, Math::Vector screenDimensions)
    {
        SDL_RenderClear(renderer);

        // PATTERN RENDER

        // Create render list
        std::vector<std::pair<int, entt::entity>> renderList;

        auto pView = frame.view<Fibers::Transform, Fibers::Pattern>();
        pView.each([&](entt::entity entity, Fibers::Transform& t, Fibers::Pattern& p) {
            if (!p.visible || !textureCache.Get(renderer, p.path)) return;
            renderList.push_back({ p.sortingOrder, entity });
        });

        // Sort render list based on sorting order
        std::sort(renderList.begin(), renderList.end(),
            [](const auto& a, const auto& b) { return a.first < b.first; });

        // Render each
        for (auto& [order, entity] : renderList)
        {
            auto& transform = pView.get<Fibers::Transform>(entity);
            auto& pattern = pView.get<Fibers::Pattern>(entity);
            auto texture = textureCache.Get(renderer, pattern.path);

            int texWidth, texHeight;
            // TODO: Implement width and height cache to avoid calling this every frame
            SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);

            auto src = pattern.srcRect;
            if (src.w == 0 && src.h == 0)
                src = { 0, 0, texWidth, texHeight };

            auto destWidth = (int)(src.w * transform.scale.x);
            auto destHeight = (int)(src.h * transform.scale.y);

            auto screenPosition = WorldToScreenPosition(transform.position, screenDimensions);
            auto destX = (int)(screenPosition.x - destWidth * pattern.pivot.x);
            auto destY = (int)(screenPosition.y - destHeight * pattern.pivot.y);

            SDL_Rect dest = { destX, destY, destWidth, destHeight };
            SDL_RenderCopyEx(renderer, texture, &src, &dest, transform.rotation, nullptr, pattern.flip);
        }

        // TEXT RENDER

        auto tView = frame.view<Fibers::Transform, Fibers::Text>();
        tView.each([&](entt::entity entity, Fibers::Transform& transform, Fibers::Text& text)
        {
            SDL_Texture* texture;
            if (!(texture = textCache.Get(text.cacheKey)))
                return;

            int w, h;
            SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
            auto dw = (int)(w * transform.scale.x);
            auto dh = (int)(h * transform.scale.y);

            float px, py = 0.5f;
            switch (text.alignment) {
                case Fibers::Text::Alignment::Left:   px = 1.0f; break;
                case Fibers::Text::Alignment::Center: px = 0.5f; break;
                case Fibers::Text::Alignment::Right:  px = 0.0f; break;
            }

            auto screenPosition = InternalUtilities::WorldToScreenPosition(transform.position, screenDimensions);
            SDL_Rect dest = {
                (int)(screenPosition.x - px * dw),
                (int)(screenPosition.y - py * dh),
                dw, dh
            };

            SDL_Point rotationCenter = { (int)(px * dw), (int)(py * dh) };

            SDL_RenderCopyEx(renderer, texture, nullptr, &dest, transform.rotation, &rotationCenter, SDL_FLIP_NONE);
        });

        // DEBUG

        if (settings.drawColliderOutlines)
        {
            auto view = frame.view<Fibers::Transform, Fibers::BoxCollider>();
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            view.each([&](entt::entity entity, Fibers::Transform& transform, Fibers::BoxCollider& collider) {
                auto screenPosition = WorldToScreenPosition(transform.position, screenDimensions);
                float left = screenPosition.x + collider.offset.x - (collider.size.x * 0.5f);
                float top = screenPosition.y + collider.offset.y - (collider.size.y * 0.5f);
                SDL_Rect rect = { (int)left, (int)top, (int)collider.size.x, (int)collider.size.y };
                SDL_RenderDrawRect(renderer, &rect);
            });
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }

        // PRESENT

        SDL_RenderPresent(renderer);
    }
}