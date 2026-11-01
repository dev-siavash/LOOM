#ifndef AUDIO_CLIP_H
#define AUDIO_CLIP_H

#include <string>

#include "FiberTraits.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"

namespace LOOM::Fibers
{
    struct AudioPlayer
    {
        std::string path;
        float volume;
        int loops;
        bool playRequested = false;

        AudioPlayer(
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

    template<>
    struct FiberTraits<AudioPlayer>
    {
        static constexpr bool Serializable = true;
        static constexpr bool IsTag = false;

        static void Save(InternalUtilities::BinaryWriter& writer, const AudioPlayer& a)
        {
            writer.Write(a.path);
            writer.Write(a.volume);
            writer.Write(a.loops);
        }

        static AudioPlayer Load(InternalUtilities::BinaryReader& reader)
        {
            AudioPlayer a;
            reader.Read(a.path);
            reader.Read(a.volume);
            reader.Read(a.loops);
            return a;
        }
    };
}

#endif