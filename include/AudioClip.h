/**
 * @file AudioClip.h
 * @brief Sound effect fiber.
 */
#ifndef AUDIO_CLIP_H
#define AUDIO_CLIP_H

#include <string>

#include "FiberTraits.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"

namespace LOOM::Fibers
{
    /** @brief Plays a sound effect on request. */
    struct AudioPlayer
    {
        /** @brief Sound file path. */
        std::string path;
        /** @brief Volume from 0 to 1. */
        float volume;
        /** @brief Extra repetitions; 0 plays once, -1 loops forever. */
        int loops;
        /** @brief (Internal) Set by Play(), consumed by the audio shuttle. */
        bool playRequested = false;

        /**
         * @brief Constructs a player.
         * @param path Sound file path.
         * @param volume Volume 0-1.
         * @param loops Extra repetitions (-1 forever).
         */
        AudioPlayer(
            std::string path = "",
            float volume = 1.0f,
            int loops = 0)
            : path{ path }, volume{ volume }, loops{ loops } 
        {}

        /** @brief Requests playback of the current clip. Ignored if the path is empty. */
        void Play() 
        { 
            if (path == "") return;
            playRequested = true; 
        }

        /**
         * @brief Sets the clip path and requests playback.
         * @param clipPath Sound file path.
         */
        void Play(std::string clipPath)
        {
            path = clipPath;
            Play();
        }
    };

    /** @brief Serialization traits for AudioPlayer. */
    template<>
    struct FiberTraits<AudioPlayer>
    {
        /** @brief True if the type can be stored in prefabs. */
        static constexpr bool Serializable = true;
        /** @brief True if the type is a payload-free marker. */
        static constexpr bool IsTag = false;

        /** @brief Writes the fiber to a BinaryWriter. */
        static void Save(InternalUtilities::BinaryWriter& writer, const AudioPlayer& a)
        {
            writer.Write(a.path);
            writer.Write(a.volume);
            writer.Write(a.loops);
        }

        /** @brief Reads the fiber from a BinaryReader. */
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