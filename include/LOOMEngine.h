/**
 * @file LOOMEngine.h
 * @brief Umbrella header: include this to use LOOM.
 */
/**
 * @mainpage LOOM
 * 2D game engine on SDL2 and EnTT. A Loom runs shuttles (systems) over a Fabric of tows (entities) that hold fibers (components).
 *
 * | Term | Meaning |
 * |------|---------|
 * | Loom | Engine: window, main loop, services |
 * | Fabric | World containing all tows and prefabs |
 * | Tow | Entity handle |
 * | Fiber | Component attached to a tow |
 * | Shuttle | System function run every frame |
 * | Shed | Frame phase (PreUpdate, Update, PostUpdate, Render, PostRender) |
 * | Prefab | Serialized tow template |
 *
 * World space has its origin at the screen center, +y up; rotations are in degrees.
 *
 * @code
 * #include "LOOMEngine.h"
 * using namespace LOOM;
 *
 * int main()
 * {
 *     Loom loom;
 *     loom.Initialize("Game", false, 800, 600);
 *
 *     Tow hero = loom.GetFabric().CreateTow();
 *     hero.PlyFiber<Fibers::Transform>();
 *     hero.PlyFiber<Fibers::Pattern>("hero.png");
 *
 *     loom.AddBoundShuttle<Fibers::Transform>(
 *         [](Loom& l, std::vector<Tow>& tows, float dt) { tows[0].FetchFiber<Fibers::Transform>().position.x += 50 * dt; },
 *         ShuttleShed::Update, 0, "Mover");
 *
 *     loom.Start();
 *     loom.Terminate();
 * }
 * @endcode
 */
/** @namespace LOOM  @brief Engine core: Loom, Fabric, Tow, shuttles and prefabs. */
/** @namespace LOOM::Fibers  @brief Built-in fibers and services. */
/** @namespace LOOM::Math  @brief Math types. */
/** @namespace LOOM::Utilities  @brief Utility types. */
/** @namespace LOOM::Shuttles  @brief Built-in shuttles. */
/** @namespace LOOM::InternalUtilities  @brief Implementation details; not part of the public API. */
#ifndef LOOMENGINE_H
#define LOOMENGINE_H

#include "Vector.h"
#include "Color.h"

#include "FiberTraits.h"
#include "MusicPlayer.h"
#include "InputState.h"
#include "Hoverable.h"
#include "Clickable.h"
#include "AudioClip.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "PhysicsBody.h"
#include "CollisionEvent.h"
#include "Pattern.h"
#include "Text.h"

#include "Prefab.h"
#include "PrefabBuilder.h"

#include "ShuttleShed.h"
#include "ShuttlePass.h"
#include "TextureCache.h"

#include "Loom.h"
#include "Fabric.h"
#include "Tow.h"

// Undefine SDL defined main symbol to avoid errors
#undef main

#endif