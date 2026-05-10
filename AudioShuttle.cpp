#include "AudioClip.h"
#include "MusicPlayer.h"
#include "InternalShuttles.h"

#include <iostream>

using namespace LOOM::InternalUtilities;

namespace LOOM::Shuttles
{
    void AudioShuttle(entt::registry& frame, AudioCache& audioCache)
    {
        static entt::entity musicPlayerEntity = entt::null;
        if (musicPlayerEntity == entt::null)
        {
            auto view = frame.view<Fibers::MusicPlayer>();
            if (view.empty())
            {
                musicPlayerEntity = frame.create();
                frame.emplace<Fibers::MusicPlayer>(musicPlayerEntity);
            }
            else
                musicPlayerEntity = view.front();
        }

        // Music handling
        auto& musicPlayer = frame.get<Fibers::MusicPlayer>(musicPlayerEntity);
        auto music = audioCache.GetMusic(musicPlayer.musicPath);
        if (music != nullptr)
        {
            if (musicPlayer.playRequested && !Mix_PlayingMusic())
            {
                Mix_PlayMusic(music, -1);
                musicPlayer.paused = false;
                musicPlayer.playing = true;
                musicPlayer.playRequested = false;
                musicPlayer.pauseRequested = false;
            }
            else if (musicPlayer.playRequested && Mix_PausedMusic())
            {
                Mix_ResumeMusic();
                musicPlayer.paused = false;
                musicPlayer.playing = true;
                musicPlayer.playRequested = false;
                musicPlayer.pauseRequested = false;
            }
            else if (musicPlayer.pauseRequested && !Mix_PausedMusic())
            {
                Mix_PauseMusic();
                musicPlayer.paused = true;
                musicPlayer.playing = false;
                musicPlayer.pauseRequested = false;
            }
            Mix_VolumeMusic((int)(musicPlayer.volume * MIX_MAX_VOLUME));
        }

        // Sound Effects Handling
        auto view = frame.view<Fibers::AudioClip>();
        view.each([&audioCache](entt::entity entity, Fibers::AudioClip& audioClip) {
            auto chunk = audioCache.GetChunk(audioClip.path);
            if (chunk == nullptr)
                return;
            if (audioClip.playRequested)
            {
                Mix_VolumeChunk(chunk, (int)(audioClip.volume * MIX_MAX_VOLUME));
                Mix_PlayChannel(-1, chunk, audioClip.loops);
                audioClip.playRequested = false;
            }
        });
    }
}