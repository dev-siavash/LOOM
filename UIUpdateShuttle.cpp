#include "Transform.h"
#include "BoxCollider.h"
#include "Hoverable.h"
#include "Clickable.h"
#include "InternalShuttles.h"
#include "InternalFunctions.h"


namespace LOOM::Shuttles
{
    void UIUpdateShuttle(entt::registry& frame, Fibers::InputState& inputState, Math::Vector screenDimensions)
    {
        auto mousePosition = 
            InternalUtilities::ScreenToWorldPosition(inputState.mousePosition, screenDimensions);

        // Update hoverables
        auto hView = frame.view<Fibers::Transform, Fibers::BoxCollider, Fibers::Hoverable>();
        hView.each([&](entt::entity entity, Fibers::Transform& transform, Fibers::BoxCollider& collider, Fibers::Hoverable& hoverable) {
            hoverable.wasHoveredLastFrame = hoverable.isHovered;
            // Calculate bounds and hoverability
            auto center = transform.position + collider.offset;
            auto left = center.x - (collider.size.x / 2.0f);
            auto right = center.x + (collider.size.x / 2.0f);
            auto bottom = center.y - (collider.size.y / 2.0f);
            auto top = center.y + (collider.size.y / 2.0f);
            hoverable.isHovered = mousePosition.x >= left && mousePosition.x <= right
                && mousePosition.y >= bottom && mousePosition.y <= top;
        });

        // Update clickables
        auto cView = frame.view<Fibers::Transform, Fibers::BoxCollider, Fibers::Clickable>();
        cView.each([&](entt::entity entity, Fibers::Transform& transform, Fibers::BoxCollider& collider, Fibers::Clickable& clickable) {
            clickable.wasHeldLastFrame = clickable.isHeld;
            // Calculate bounds and hoverability
            bool isHovered = false;
            if (auto hoverable = frame.try_get<Fibers::Hoverable>(entity))
                isHovered = hoverable->IsHovered();
            else
            {
                auto center = transform.position + collider.offset;
                auto left = center.x - (collider.size.x / 2.0f);
                auto right = center.x + (collider.size.x / 2.0f);
                auto bottom = center.y - (collider.size.y / 2.0f);
                auto top = center.y + (collider.size.y / 2.0f);
                isHovered = mousePosition.x >= left && mousePosition.x <= right && mousePosition.y >= bottom && mousePosition.y <= top;
            }
            bool anyButtonDown = inputState.IsMouseButtonDown(0) || inputState.IsMouseButtonDown(1) || inputState.IsMouseButtonDown(2);
            clickable.isHeld = isHovered && anyButtonDown;
        });
    }
}