#include <SDL_mixer.h>

#include "AudioCache.h"

Mix_Chunk* LOOM::InternalUtilities::AudioCache::GetChunk(const std::string& path)
{
    if (chunkCache.contains(path))
        return chunkCache[path];

    auto chunk = Mix_LoadWAV(path.c_str());
    if (chunk == NULL)
        return nullptr;

    chunkCache.insert({ path, chunk });
    return chunk;
}

Mix_Music* LOOM::InternalUtilities::AudioCache::GetMusic(const std::string& path)
{
    if (musicCache.contains(path))
        return musicCache[path];

    auto music = Mix_LoadMUS(path.c_str());
    if (music == NULL)
        return nullptr;

    musicCache.insert({ path, music });
    return music;
}

void LOOM::InternalUtilities::AudioCache::ClearChunkCache()
{
    for (auto& e : chunkCache)
        Mix_FreeChunk(e.second);

    chunkCache.clear();
}

void LOOM::InternalUtilities::AudioCache::ClearMusicCache()
{
    for (auto& e : musicCache)
        Mix_FreeMusic(e.second);

    musicCache.clear();
}