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
#include "Fabric.h"
#include "Tow.h"
#include "ShuttleShed.h"
#include "ShuttlePass.h"

namespace LOOM
{
    struct LoomSettings
    {
        Math::Vector globalGravityScale = Math::Vector(0.0f, -980.0f);
        bool drawColliderOutlines = false;
    };

    class Loom
    {
    public:
        Loom() : serviceProvider{ fabric.CreateTow() } {}

        bool Initialize(const std::string& title, bool fullscreen, int screenWidth, int screenHeight);
        void Terminate();

        void Start();
        void Stop() { isRunning = false; }

        void AddShuttle(ShuttlePass::Shuttle, ShuttleShed, int, std::string name = "");
        void RemoveShuttle(std::string name);

        Fabric& GetFabric() { return fabric; }

        LoomSettings& Settings() { return settings; }

        template<typename T>
        T& GetService() { return serviceProvider.FetchFiber<T>(); }

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
