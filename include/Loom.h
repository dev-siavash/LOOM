/**
 * @file Loom.h
 * @brief Engine core: window, main loop and shuttle scheduling.
 */
#ifndef LOOM_H
#define LOOM_H

#include <vector>
#include <string>
#include <functional>
#include <SDL.h>

#include "Vector.h"
#include "TextureCache.h"
#include "AudioCache.h"
#include "FontCache.h"
#include "TextCache.h"
#include "Fabric.h"
#include "Tow.h"
#include "ShuttleShed.h"
#include "ShuttlePass.h"

namespace LOOM
{
    /** @brief Global engine settings, edited through Loom::Settings(). */
    struct LoomSettings
    {
        /** @brief Gravity applied to every PhysicsBody with applyGravity, in units/s^2 (default 0, -980: down). */
        Math::Vector globalGravityScale = Math::Vector(0.0f, -980.0f);
        /** @brief Draws green outlines around all BoxColliders when true (debug aid). */
        bool drawColliderOutlines = false;
    };

    /**
     * @brief The engine. Owns the window, the Fabric, the asset caches and the shuttle loop.
     *
     * Typical flow: Initialize(), create tows and add shuttles, Start(), Terminate().
     * Built-in services (InputState, MusicPlayer, CollisionEvent) are reachable through GetService().
     */
    class Loom
    {
    public:
        /** @brief Creates the engine and its service tow. Call Initialize() before use. */
        Loom() : serviceProvider{ fabric.CreateTow() } {}

        /**
         * @brief Initializes SDL (video, image, mixer, ttf), creates the window and renderer and installs the built-in shuttles.
         * @param title Window title.
         * @param fullscreen Fullscreen window; the screen size is then read from the renderer.
         * @param screenWidth Window width in pixels (windowed mode).
         * @param screenHeight Window height in pixels (windowed mode).
         * @return false if the window or renderer could not be created.
         * @throws std::runtime_error If an SDL subsystem fails to initialize.
         */
        bool Initialize(const std::string& title, bool fullscreen, int screenWidth, int screenHeight);
        /** @brief Clears the Fabric and caches, then shuts SDL down. Called automatically when the window is closed. */
        void Terminate();

        /**
         * @brief Runs the main loop until Stop() is called or the window is closed. Blocks.
         *
         * Each frame runs every shuttle ordered by ShuttleShed, then by ascending order.
         * Shuttles added or removed during the loop take effect at the end of the frame.
         */
        void Start();
        /** @brief Ends the main loop after the current frame. Does not shut SDL down; see Terminate(). */
        void Stop() { isRunning = false; }

        /**
         * @brief Registers a system function.
         *
         * The callback receives the engine and the frame delta time (seconds). It runs in the given shed, ordered by ascending order value inside it. The optional name identifies it for RemoveShuttle(). Added while running, it takes effect at the end of the frame.
         */
        void AddShuttle(ShuttlePass::Shuttle, ShuttleShed, int, std::string name = "");
        /**
         * @brief Removes the shuttle registered under @p name. Empty names are ignored.
         * @param name Name given to AddShuttle().
         */
        void RemoveShuttle(std::string name);

        /**
         * @brief Returns the Fabric holding all tows and prefabs.
         * @return The Fabric.
         */
        Fabric& GetFabric() { return fabric; }

        /**
         * @brief Returns the mutable engine settings.
         * @return The settings.
         */
        LoomSettings& Settings() { return settings; }

        /**
         * @brief Returns a global service fiber (InputState, MusicPlayer or CollisionEvent).
         * @tparam T Service type.
         * @return Reference to the service.
         */
        template<typename T>
        T& GetService() { return serviceProvider.FetchFiber<T>(); }

        /**
         * @brief Registers a shuttle bound to a fiber set.
         *
         * Each frame it receives every Tow holding all of @p Fibers, and is skipped when none match.
         * @tparam Fibers Fiber types a tow must hold.
         * @param boundShuttle Callback receiving the engine, the matching tows and delta time.
         * @param shed Phase of the frame it runs in.
         * @param order Position inside the shed; lower runs first.
         * @param name Optional identifier.
         */
        template<typename ...Fibers>
        void AddBoundShuttle(ShuttlePass::BoundShuttle boundShuttle, ShuttleShed shed, int order, std::string name = "")
        {
            ShuttlePass::Shuttle shuttle = [boundShuttle](Loom& loom, float dt) {
                auto tows = loom.GetFabric().FetchAllTowsOf<Fibers...>();
                if (!tows.empty())
                    boundShuttle(loom, tows, dt);
            };

            ShuttlePass pass(name, shuttle, shed, order);

            if (!isRunning)
                shuttlePasses.push_back(pass);
            else
                shuttlePassesToAdd.push_back(pass);
        }

        /**
         * @brief Returns true while the main loop is running.
         * @return True while looping.
         */
        bool IsRunning() const { return isRunning; }

    private:
        void SetupInternalShuttles();

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        int screenWidth = 800;
        int screenHeight = 600;

        Fabric fabric;
        Tow serviceProvider;
        InternalUtilities::TextureCache textureCache;
        InternalUtilities::AudioCache audioCache;
        InternalUtilities::FontCache fontCache;
        InternalUtilities::TextCache textCache;

        std::vector<ShuttlePass> shuttlePasses;
        std::vector<ShuttlePass> shuttlePassesToAdd;
        std::vector<std::string> shuttlePassNamesToRemove;

        LoomSettings settings;

        bool isRunning = false;
        bool delayedTermination = false;
        Uint64 lastTime = 0;
    };
}

#endif
