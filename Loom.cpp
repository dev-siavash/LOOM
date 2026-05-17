#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "MusicPlayer.h"
#include "InputState.h"
#include "CollisionEvent.h"
#include "InternalShuttles.h"
#include "Loom.h"

bool LOOM::Loom::Initialize(const std::string& title, bool fullScreen, int screenWidth, int screenHeight)
{
    int windowFlags = fullScreen ? SDL_WINDOW_FULLSCREEN : 0;
    int rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::string msg = "SDL failed to initialize. SDL_Error: ";
        msg += SDL_GetError();
        throw std::runtime_error(msg);
    }

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
        SDL_Quit();
        std::string msg = "SDL_image failed to initialize. SDL_Error: ";
        msg += IMG_GetError();
        throw std::runtime_error(msg);
    }

    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Quit();
        IMG_Quit();
        std::string msg = "SDL_mixer failed to initialize. SDL_Error: ";
        msg += Mix_GetError();
        throw std::runtime_error(msg);
    }

    if (TTF_Init() < 0) {
        SDL_Quit();
        IMG_Quit();
        Mix_CloseAudio();
        std::string msg = "SDL_ttf failed to initialize. SDL_Error: ";
        msg += TTF_GetError();
        throw std::runtime_error(msg);
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, windowFlags);
    if (!window)
        return false;

    renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    if (!renderer)
        return false;

    if (fullScreen)
        SDL_GetRendererOutputSize(renderer, &this->screenWidth, &this->screenHeight);
    else
    {
        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;
    }

    serviceProvider.PlyFiber<Fibers::MusicPlayer>();
    serviceProvider.PlyFiber<Fibers::InputState>();
    serviceProvider.PlyFiber<Fibers::CollisionEvent>();

    lastTime = SDL_GetPerformanceCounter();
    SetupInternalShuttles();

    return true;
}

void LOOM::Loom::Terminate()
{
    isRunning = false;
    fabric.Clear();
    textureCache.Clear();
    audioCache.ClearChunkCache();
    audioCache.ClearMusicCache();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
}

void LOOM::Loom::Start()
{
    isRunning = true;

    std::sort(shuttlePasses.begin(), shuttlePasses.end(),
        [](const ShuttlePass& a, const ShuttlePass& b) {
            if (a.shed != b.shed)
                return static_cast<int>(a.shed) < static_cast<int>(b.shed);
            return a.order < b.order;
        });

    while (isRunning)
    {
        auto currentTime = SDL_GetPerformanceCounter();
        auto deltaTime = (currentTime - lastTime) / (float)SDL_GetPerformanceFrequency();
        lastTime = currentTime;

        for (auto& pass : shuttlePasses)
            pass.shuttle(*this, deltaTime);

        if (shuttlePassesToAdd.size() > 0)
        {
            for (auto& pass : shuttlePassesToAdd)
                shuttlePasses.push_back(pass);
            shuttlePassesToAdd.clear();

            std::sort(shuttlePasses.begin(), shuttlePasses.end(),
                [](const ShuttlePass& a, const ShuttlePass& b) {
                    if (a.shed != b.shed)
                        return static_cast<int>(a.shed) < static_cast<int>(b.shed);
                    return a.order < b.order;
                });
        }

        if (shuttlePassNamesToRemove.size() > 0)
        {
            for (auto& name : shuttlePassNamesToRemove)
            {
                shuttlePasses.erase(std::remove_if(shuttlePasses.begin(), shuttlePasses.end(),
                    [&name](ShuttlePass pass) { return pass.name == name; }), shuttlePasses.end());
            }

            shuttlePassNamesToRemove.clear();
        }

        if (delayedTermination)
            Terminate();
    }
}

void LOOM::Loom::AddShuttle(ShuttlePass::Shuttle shuttle, ShuttleShed shed, int order, std::string name)
{
    ShuttlePass pass(name, shuttle, shed, order);

    if (!isRunning)
        shuttlePasses.push_back(pass);
    else
        shuttlePassesToAdd.push_back(pass);
}

void LOOM::Loom::RemoveShuttle(std::string name)
{
    if (name == "")
        return;

    if (!isRunning)
    {
        shuttlePasses.erase(std::remove_if(shuttlePasses.begin(), shuttlePasses.end(),
            [&name](ShuttlePass pass) { return pass.name == name; }), shuttlePasses.end());
    }
    else
        shuttlePassNamesToRemove.push_back(name);
}

void LOOM::Loom::SetupInternalShuttles()
{
    // Input
    shuttlePasses.push_back({
        "LOOMInputShuttle",
        [this](Loom& loom, float dt) {
            Shuttles::InputShuttle(fabric.frame, GetService<Fibers::InputState>(), [this]() { this->delayedTermination = true; });
        },
        ShuttleShed::PreUpdate, 0 });
    // Audio
    shuttlePasses.push_back({
        "LOOMAudioShuttle",
        [this](Loom& loom, float dt) {
            Shuttles::AudioShuttle(fabric.frame, GetService<Fibers::MusicPlayer>(), audioCache);
        },
        ShuttleShed::PreUpdate, 1 });
    // UI
    shuttlePasses.push_back({
        "LOOMUIUpdateShuttle",
        [this](Loom& loom, float dt) {
            Shuttles::UIUpdateShuttle(fabric.frame, GetService<Fibers::InputState>(), Math::Vector((float)screenWidth, (float)screenHeight));
        },
        ShuttleShed::PostUpdate, 0 });
    // Physics
    shuttlePasses.push_back({
        "LOOMPhyicsShuttle",
        [this](Loom& loom, float dt) {
            Shuttles::PhysicsShuttle(fabric.frame, fabric, GetService<Fibers::CollisionEvent>(), settings, dt);
        },
        ShuttleShed::PostUpdate, 1 });
    // Render
    shuttlePasses.push_back({
        "LOOMRenderShuttle",
        [this](Loom& loom, float dt) {
            Shuttles::RenderShuttle(fabric.frame, renderer, textureCache, settings, Math::Vector((float)screenWidth, (float)screenHeight));
        },
        ShuttleShed::Render, 0 });
}