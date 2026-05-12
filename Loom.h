#ifndef LOOM_H
#define LOOM_H

#include <vector>
#include <string>
#include <functional>
#include <SDL.h>

#include "Vector.h"
#include "TextureCache.h"
#include "AudioCache.h"
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

        void AddShuttle(decltype(ShuttlePass::shuttle), ShuttleShed, int, std::string name = "");
        void RemoveShuttle(std::string name);

        Fabric& GetFabric() { return fabric; }
        LoomSettings& Settings() { return settings; }

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
