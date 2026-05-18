#include "TextCache.h"

SDL_Texture* LOOM::InternalUtilities::TextCache::Get(std::size_t cacheKey)
{
    if (cache.contains(cacheKey))
        return cache[cacheKey];

    return nullptr;
}

void LOOM::InternalUtilities::TextCache::Store(std::size_t cacheKey, SDL_Texture* texture)
{
    Remove(cacheKey);
    cache[cacheKey] = texture;
}

void LOOM::InternalUtilities::TextCache::Remove(std::size_t cacheKey)
{
    if (!cache.contains(cacheKey))
        return;

    SDL_DestroyTexture(cache[cacheKey]);
    cache.erase(cacheKey);
}

void LOOM::InternalUtilities::TextCache::Clear()
{
    for (auto iter = cache.begin(); iter != cache.end(); iter++)
        SDL_DestroyTexture(iter->second);

    cache.clear();
}