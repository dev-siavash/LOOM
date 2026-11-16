/**
 * @file TextureCache.h
 * @brief Texture cache.
 */
#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include <string>
#include <unordered_map>
#include <SDL.h>

namespace LOOM::InternalUtilities
{
    /** @brief (Internal) Loads and caches textures by file path. */
    class TextureCache
    {
    public:
        /** @brief Returns the cached texture, loading it on first use. Returns nullptr on failure. */
        SDL_Texture* Get(SDL_Renderer*, const std::string&);
        /** @brief Destroys all cached textures. */
        void Clear();
    private:
        std::unordered_map<std::string, SDL_Texture*> cache;
    };
}

#endif
