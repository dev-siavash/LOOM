\# LOOM



A small 2D game engine in C++20, built on \[SDL2](https://www.libsdl.org/) and \[EnTT](https://github.com/skypjack/entt).



LOOM is an entity-component-system with a weaving vocabulary: \*\*shuttles\*\* (systems) run over a \*\*fabric\*\* (world) of \*\*tows\*\* (entities) that hold \*\*fibers\*\* (components). It ships with sprites, text, audio, input, UI hover/click detection and simple AABB physics.



```cpp

\#include "LOOMEngine.h"

using namespace LOOM;

using namespace LOOM::Fibers;



int main()

{

&#x20;   Loom loom;

&#x20;   if (!loom.Initialize("Hello LOOM", false, 800, 600))

&#x20;       return 1;



&#x20;   Tow player = loom.GetFabric().CreateTow();

&#x20;   player.PlyFiber<Transform>();

&#x20;   player.PlyFiber<Pattern>("assets/player.png");

&#x20;   player.PlyFiber<PhysicsBody>(Math::Vector::zero(), 1.0f, 0.0f, false);



&#x20;   // Runs every frame for every tow holding Transform + PhysicsBody

&#x20;   loom.AddBoundShuttle<Transform, PhysicsBody>(

&#x20;       \[](Loom\& l, std::vector<Tow>\& tows, float dt) {

&#x20;           auto\& input = l.GetService<InputState>();

&#x20;           float dir = (float)input.IsKeyDown(KeyCode::Right) - (float)input.IsKeyDown(KeyCode::Left);

&#x20;           for (Tow\& t : tows)

&#x20;               t.FetchFiber<PhysicsBody>().velocity.x = dir \* 200.0f;

&#x20;       },

&#x20;       ShuttleShed::Update, 0, "Move");



&#x20;   loom.Start();      // blocks until the window is closed or Stop() is called

&#x20;   loom.Terminate();

}

```



\## Concepts



| Term | Meaning | Type |

|------|---------|------|

| Loom | The engine: window, main loop, services, shuttle scheduling | `LOOM::Loom` |

| Fabric | The world holding every tow and prefab | `LOOM::Fabric` |

| Tow | Entity handle; holds at most one fiber of each type | `LOOM::Tow` |

| Fiber | Component: plain data attached to a tow | `LOOM::Fibers::\*` |

| Shuttle | System: a function run every frame | `ShuttlePass::Shuttle` |

| Shed | Frame phase a shuttle runs in | `LOOM::ShuttleShed` |

| Prefab | Serialized tow template, spawnable by name | `LOOM::Prefab` |



\## Requirements



\- A C++20 compiler

\- \[SDL2](https://github.com/libsdl-org/SDL), SDL2\_image (PNG, JPG), SDL2\_mixer and SDL2\_ttf

\- \[EnTT](https://github.com/skypjack/entt) (header-only)



With \[vcpkg](https://vcpkg.io/):



```

vcpkg install sdl2 sdl2-image sdl2-mixer sdl2-ttf entt

```



\## Project layout



```

.

├── include/   Public headers (LOOMEngine.h is the umbrella header)

├── src/       Implementation (.cpp files)

└── .gitignore

```



LOOM has no build system yet. Compile everything in `src/` into your game, or into a static library, with these settings:



\- C++ standard: C++20

\- Include directories: `include/`, EnTT, and the SDL2 headers (the code uses `#include <SDL.h>`, so the directory that contains `SDL.h` must be on the include path)

\- Link: SDL2, SDL2\_image, SDL2\_mixer, SDL2\_ttf



In Visual Studio, create a C++ project, add `src/\*.cpp`, set the include directories above, and link the SDL2 libraries (vcpkg integration does this for you).



> \*\*Portability note:\*\* the code currently targets MSVC. GCC and Clang fail on a few missing standard includes (for example `<cstdint>` in `BinaryReader.h`, `BinaryWriter.h` and `InputState.h`) and on the include order of `Tow.h` and `Fabric.h`. These are small fixes, but they are not done yet.



Include `LOOMEngine.h` in your game. It undefines SDL's `main` macro, so use a plain `int main()`.



Asset paths (images, sounds, fonts) are resolved relative to the working directory.



\## Using LOOM



\### Frame loop



Each frame, shuttles run in shed order, then by ascending `order` within a shed:



| Shed | Built-in shuttles (order) |

|------|---------------------------|

| `PreUpdate` | input (-1), audio (0) |

| `Update` | your game logic |

| `PostUpdate` | UI hover/click (-1), physics (0) |

| `Render` | text cache (-1), rendering and present (0) |

| `PostRender` | your code, after the frame is presented |



Shuttles added or removed while the loop is running take effect at the end of the frame.



```cpp

loom.AddShuttle(\[](Loom\& l, float dt) { /\* ... \*/ }, ShuttleShed::Update, 0, "MyShuttle");

loom.RemoveShuttle("MyShuttle");

```



\### Tows and fibers



```cpp

Fabric\& fabric = loom.GetFabric();



Tow label = fabric.CreateTow();

label.PlyFiber<Transform>(Math::Vector(0, 200));

label.PlyFiber<Text>("Score: 0", "assets/font.ttf", 32);



label.FetchFiber<Text>().SetText("Score: 10");

if (label.HoldsFiber<Text>()) { /\* ... \*/ }

label.SeverFiber<Text>();



fabric.UnwindTow(label);    // destroy the tow and all its fibers

```



Query tows with `FetchAllTowsOf<...>()`, `FetchTowOf<...>()` and `FirstFiber<T>()`, or let LOOM do it for you with `AddBoundShuttle<...>()`.



\### Services



Global state lives in service fibers on the engine's own tow, fetched with `loom.GetService<T>()`:



| Service | Purpose |

|---------|---------|

| `InputState` | Keyboard and mouse state: `IsKeyDown/Pressed/Released`, `IsMouseButton\*`, `mousePosition` |

| `MusicPlayer` | Background music: set `musicPath`, then `Play()` / `Pause()` |

| `CollisionEvent` | Collision pairs found in the last physics pass |



\### Built-in fibers



| Fiber | Requires | Description |

|-------|----------|-------------|

| `Transform` | none | Position, rotation (degrees) and scale |

| `Pattern` | `Transform` | Sprite with sorting order, flip, pivot and source rectangle |

| `Text` | `Transform` | TrueType text; `MarkStatic()` for text that never changes |

| `BoxCollider` | `Transform` | Axis-aligned box; can be a trigger |

| `PhysicsBody` | `Transform` | Velocity, mass, drag and gravity |

| `Hoverable` | `Transform`, `BoxCollider` | Mouse hover: `IsHovered()`, `EnteredHover()`, `ExitedHover()` |

| `Clickable` | `Transform`, `BoxCollider` | Mouse click: `IsClicked()` |

| `AudioPlayer` | none | Sound effect: `Play()` |



\### Physics and collisions



\- Colliders with a `PhysicsBody` are dynamic. Colliders without one are static.

\- Gravity is `Settings().globalGravityScale` (default `(0, -980)`) in units per second squared.

\- Triggers report collisions but do not push or stop anything.

\- Read results from the `CollisionEvent` service:



```cpp

for (auto\& pair : loom.GetService<CollisionEvent>().collisionPairs)

&#x20;   if (pair.a.HoldsFiber<Hoverable>()) { /\* pair.normal points from b toward a \*/ }

```



Set `loom.Settings().drawColliderOutlines = true` to see colliders.



\### Prefabs



```cpp

fabric.PreFabricate("coin")

&#x20;   .PlyFiber<Transform>()

&#x20;   .PlyFiber<Pattern>("assets/coin.png")

&#x20;   .PlyFiber<BoxCollider>(Math::Vector(16, 16), Math::Vector::zero(), true)

&#x20;   .Register();



Tow coin = fabric.SpawnPrefab("coin");

```



Prefabs only accept serializable fibers. All built-in fibers except `MusicPlayer`, `InputState` and `CollisionEvent` are. To make your own fiber usable in prefabs, specialize `FiberTraits`:



```cpp

struct Health { int hp = 100; };



namespace LOOM::Fibers

{

&#x20;   template<>

&#x20;   struct FiberTraits<Health>

&#x20;   {

&#x20;       static constexpr bool Serializable = true;

&#x20;       static constexpr bool IsTag = false;



&#x20;       static void Save(InternalUtilities::BinaryWriter\& w, const Health\& h) { w.Write(h.hp); }

&#x20;       static Health Load(InternalUtilities::BinaryReader\& r) { Health h; r.Read(h.hp); return h; }

&#x20;   };

}

```



Empty structs are treated as tags automatically and are serializable with no extra code.



\### Conventions



\- \*\*World space:\*\* origin at the screen center, +y up. Screen space (mouse position) has its origin at the top-left, +y down.

\- \*\*Rotation:\*\* degrees.

\- \*\*Sprite pivots:\*\* (0, 0) is top-left and (1, 1) is bottom-right. See `Math::Vector::pivotCenter()` and friends.

\- \*\*Mouse buttons:\*\* 0 left, 1 middle, 2 right.



\## API documentation



All public headers carry Doxygen comments. To generate HTML docs:



```

doxygen -g Doxyfile    # then set INPUT = include and FILE\_PATTERNS = \*.h \*.hpp

doxygen Doxyfile

```



Types in `LOOM::InternalUtilities` and `LOOM::Shuttles` are implementation details and not part of the public API.



\## Notes



\- The engine is single-threaded.

\- `Fabric::Clear()` also destroys the engine's service tow; it is meant for shutdown.

\- Closing the window ends the loop and calls `Terminate()` for you.

