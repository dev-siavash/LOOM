#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <string>

namespace LOOM::Fibers
{
    struct MusicPlayer
    {
        std::string musicPath;
        float volume = 0.5f;
        bool playing = false;
        bool paused = false;
        bool pauseRequested = false;
        bool playRequested = false;

        void Play() { playRequested = true; pauseRequested = false; }
        void Pause() { pauseRequested = true; playRequested = false; }
    };
}

#endif