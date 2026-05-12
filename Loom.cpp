#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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
            pass.shuttle(deltaTime);

        if (delayedTermination)
            Terminate();
    }

}

void LOOM::Loom::SetupInternalShuttles()
{
    // Input
    shuttlePasses.push_back({
        [this](float dt) {
            Shuttles::InputShuttle(fabric.frame, serviceProvider.FetchFiber<Fibers::InputState>(), [this]() { this->delayedTermination = true; });
        },
        ShuttleShed::PreUpdate, 0});
    // Audio
    shuttlePasses.push_back({
        [this](float dt) {
            Shuttles::AudioShuttle(fabric.frame, serviceProvider.FetchFiber<Fibers::MusicPlayer>(), audioCache);
        },
        ShuttleShed::PreUpdate, 1});
    // Physics
    shuttlePasses.push_back({
        [this](float dt) {
            Shuttles::PhysicsShuttle(fabric.frame, fabric, serviceProvider.FetchFiber<Fibers::CollisionEvent>(), settings, dt);
        },
        ShuttleShed::PostUpdate, 0});
    // Render
    shuttlePasses.push_back({
        [this](float dt) {
            Shuttles::RenderShuttle(fabric.frame, renderer, textureCache, settings, Math::Vector(screenWidth, screenHeight));
        },
        ShuttleShed::Render, 0});
}