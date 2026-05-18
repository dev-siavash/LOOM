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