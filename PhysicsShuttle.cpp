#include "RectF.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "PhysicsBody.h"
#include "CollisionEvent.h"
#include "InternalShuttles.h"
#include "Fabric.h"

namespace LOOM::Shuttles
{
    void PhysicsShuttle(entt::registry& frame, Fabric& fabric, LoomSettings settings, float deltaTime)
    {
        static entt::entity collisionEventEntity = entt::null;
        if (collisionEventEntity == entt::null)
        {
            auto view = frame.view<Fibers::CollisionEvent>();
            if (view.empty())
            {
                collisionEventEntity = frame.create();
                frame.emplace<Fibers::CollisionEvent>(collisionEventEntity);
            }
            else
                collisionEventEntity = view.front();
        }

        // Clear previous frames collision data
        auto& collisionEvent = frame.get<Fibers::CollisionEvent>(collisionEventEntity);
        collisionEvent.collisionPairs.clear();

        // Calculate and apply velocity
        auto view = frame.view<Fibers::Transform, Fibers::PhysicsBody>();
        view.each([&settings, deltaTime](entt::entity entity, Fibers::Transform& transform, Fibers::PhysicsBody& physicsBody) {
            if (physicsBody.applyGravity)
                physicsBody.velocity += settings.globalGravityScale * deltaTime;
            physicsBody.velocity /= 1.0f + physicsBody.drag * deltaTime;
            transform.position += physicsBody.velocity * deltaTime;
        });

        auto getAABB = [&](Tow t) {
            auto& transform = t.FetchFiber<Fibers::Transform>();
            auto& collider = t.FetchFiber<Fibers::BoxCollider>();
            auto left = transform.position.x + collider.offset.x - collider.size.x * 0.5f;
            auto top = transform.position.y + collider.offset.y - collider.size.y * 0.5f;
            auto right = left + collider.size.x;
            float bottom = top + collider.size.y;
            return Math::RectF{ left, top, collider.size.x, collider.size.y };
        };

        auto physicTows = fabric.FetchAllTowsOf<Fibers::Transform, Fibers::BoxCollider>();
        if (physicTows.size() >= 2)
        {
            for (size_t i = 0; i < physicTows.size() - 1; i++)
            {
                auto aRect = getAABB(physicTows[i]);
                for (size_t j = i + 1; j < physicTows.size(); j++)
                {
                    auto bRect = getAABB(physicTows[j]);

                    float overlapLeft = (aRect.x + aRect.w) - bRect.x;
                    float overlapRight = (bRect.x + bRect.w) - aRect.x;
                    float overlapTop = (aRect.y + aRect.h) - bRect.y;
                    float overlapBottom = (bRect.y + bRect.h) - aRect.y;

                    float minX = (overlapLeft < overlapRight) ? -overlapLeft : overlapRight;
                    float minY = (overlapTop < overlapBottom) ? -overlapTop : overlapBottom;
                    
                    bool overlapping = (overlapLeft > 0.0f) && (overlapRight > 0.0f) && (overlapTop > 0.0f) && (overlapBottom > 0.0f);
                    if (!overlapping)
                        continue;

                    Math::Vector mtv;
                    if (abs(minX) < abs(minY))
                    {
                        mtv.x = minX;
                        mtv.y = 0.0f;
                    }
                    else
                    {
                        mtv.y = minY;
                        mtv.x = 0.0f;
                    }


                    bool aDynamic = physicTows[i].HoldsFiber<Fibers::PhysicsBody>();
                    bool bDynamic = physicTows[j].HoldsFiber<Fibers::PhysicsBody>();
                    if (aDynamic || bDynamic)
                    {
                        float aMass = aDynamic ?
                            physicTows[i].FetchFiber<Fibers::PhysicsBody>().mass : std::numeric_limits<float>::max();
                        float bMass = bDynamic ?
                            physicTows[j].FetchFiber<Fibers::PhysicsBody>().mass : std::numeric_limits<float>::max();

                        Math::Vector correctionA, correctionB;
                        if (aDynamic && bDynamic)
                        {
                            correctionA = mtv * (bMass / (aMass + bMass));
                            correctionB = mtv * -(aMass / (aMass + bMass));
                        }
                        else if (aDynamic)
                            correctionA = mtv;
                        else
                            correctionB = mtv * -1;

                        physicTows[i].FetchFiber<Fibers::Transform>().position += correctionA;
                        physicTows[j].FetchFiber<Fibers::Transform>().position += correctionB;
                    }

                    auto normal = mtv.normalized();
                    auto resolveVelocity = [&](Tow& tow, Math::Vector pushDirection) {
                        if (!tow.HoldsFiber<Fibers::PhysicsBody>())
                            return;

                        auto& body = tow.FetchFiber<Fibers::PhysicsBody>();
                        auto velocityAlongPush = (body.velocity.x * pushDirection.x) + (body.velocity.y * pushDirection.y);
                        if (velocityAlongPush < 0.0f)
                            body.velocity -= pushDirection * velocityAlongPush;
                    };

                    resolveVelocity(physicTows[i], normal);
                    resolveVelocity(physicTows[j], normal * -1.0f);

                    collisionEvent.collisionPairs.push_back({ physicTows[i], physicTows[j], normal });
                }
            }
        }
    }
}