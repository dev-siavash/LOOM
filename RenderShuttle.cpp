#include <algorithm>
#include <vector>

#include "Transform.h"
#include "Pattern.h"
#include "InternalShuttles.h"

using namespace LOOM::InternalUtilities;

namespace LOOM::Shuttles
{
    void RenderShuttle(entt::registry& frame, SDL_Renderer* renderer, TextureCache& textureCache)
    {
        SDL_RenderClear(renderer);

        auto view = frame.view<Fibers::Transform, Fibers::Pattern>();

        // Create render list
        std::vector<std::pair<int, entt::entity>> renderList;
        view.each([&](entt::entity entity, Fibers::Transform& t, Fibers::Pattern& p) {
            if (!p.visible || !textureCache.Get(renderer, p.path)) return;
            renderList.push_back({ p.sortingOrder, entity });
        });

        // Sort render list based on sorting order
        std::sort(renderList.begin(), renderList.end(),
            [](const auto& a, const auto& b) { return a.first < b.first; });

        // Render each
        for (auto& [order, entity] : renderList)
        {
            auto& transform = view.get<Fibers::Transform>(entity);
            auto& pattern = view.get<Fibers::Pattern>(entity);
            auto texture = textureCache.Get(renderer, pattern.path);

            int texWidth, texHeight;
            // TODO: Implement width and height cache to avoid calling this every frame
            SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);

            auto src = pattern.srcRect;
            if (src.w == 0 && src.h == 0)
                src = { 0, 0, texWidth, texHeight };

            auto destWidth = (int)(src.w * transform.scale.x);
            auto destHeight = (int)(src.h * transform.scale.y);

            auto destX = (int)(transform.position.x - destWidth * pattern.pivot.x);
            auto destY = (int)(transform.position.y - destHeight * pattern.pivot.y);

            SDL_Rect dest = { destX, destY, destWidth, destHeight };
            SDL_RenderCopyEx(renderer, texture, &src, &dest, transform.rotation, nullptr, pattern.flip);
        }

        SDL_RenderPresent(renderer);
    }
}