/**
 * @file MusicPlayer.h
 * @brief Music service.
 */
#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <string>

namespace LOOM::Fibers
{
    /**
     * @brief Global music service; fetch with Loom::GetService<Fibers::MusicPlayer>().
     *
     * Set @c musicPath, then call Play().
     */
    struct MusicPlayer
    {
        /** @brief Music file path. */
        std::string musicPath;
        /** @brief Volume from 0 to 1. */
        float volume = 0.5f;
        /** @brief True while music is playing (read-only state). */
        bool playing = false;
        /** @brief True while music is paused (read-only state). */
        bool paused = false;
        /** @brief (Internal) Pending pause request. */
        bool pauseRequested = false;
        /** @brief (Internal) Pending play request. */
        bool playRequested = false;

        /** @brief Starts or resumes music; it loops indefinitely. */
        void Play() { playRequested = true; pauseRequested = false; }
        /** @brief Pauses music. */
        void Pause() { pauseRequested = true; playRequested = false; }
    };
}

#endif