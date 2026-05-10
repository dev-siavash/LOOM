#ifndef AUDIO_CACHE_H
#define AUDIO_CACHE_H

#include <string>
#include <unordered_map>
#include <SDL_mixer.h>

namespace LOOM::InternalUtilities
{
    class AudioCache
    {
    public:
        Mix_Chunk* GetChunk(const std::string&);
        Mix_Music* GetMusic(const std::string&);
        void ClearChunkCache();
        void ClearMusicCache();
    private:
        std::unordered_map<std::string, Mix_Chunk*> chunkCache;
        std::unordered_map<std::string, Mix_Music*> musicCache;
    };
}

#endif
