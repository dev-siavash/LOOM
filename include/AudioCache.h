/**
 * @file AudioCache.h
 * @brief Audio cache.
 */
#ifndef AUDIO_CACHE_H
#define AUDIO_CACHE_H

#include <string>
#include <unordered_map>
#include <SDL_mixer.h>

namespace LOOM::InternalUtilities
{
    /** @brief (Internal) Loads and caches sound effects and music by file path. */
    class AudioCache
    {
    public:
        /** @brief Returns the cached sound effect, loading it on first use. Returns nullptr on failure. */
        Mix_Chunk* GetChunk(const std::string&);
        /** @brief Returns the cached music, loading it on first use. Returns nullptr on failure. */
        Mix_Music* GetMusic(const std::string&);
        /** @brief Frees all cached sound effects. */
        void ClearChunkCache();
        /** @brief Frees all cached music. */
        void ClearMusicCache();
    private:
        std::unordered_map<std::string, Mix_Chunk*> chunkCache;
        std::unordered_map<std::string, Mix_Music*> musicCache;
    };
}

#endif
