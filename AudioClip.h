#ifndef AUDIO_CLIP_H
#define AUDIO_CLIP_H

#include <string>

namespace LOOM::Fibers
{
    struct AudioClip
    {
        std::string path;
        float volume;
        int loops;
        bool playRequested = false;

        AudioClip(
            std::string path = "",
            float volume = 1.0f,
            int loops = 0)
            : path{ path }, volume{ volume }, loops{ loops } 
        {}

        void Play() 
        { 
            if (path == "") return;
            playRequested = true; 
        }

        void Play(std::string clipPath)
        {
            path = clipPath;
            Play();
        }
    };
}

#endif