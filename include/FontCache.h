/**
 * @file FontCache.h
 * @brief Font cache.
 */
#ifndef FONT_CACHE_H
#define FONT_CACHE_H

#include <string>
#include <unordered_map>
#include <SDL_ttf.h>

namespace LOOM::InternalUtilities
{
    /** @brief (Internal) Loads and caches fonts by path and size. */
    class FontCache
    {
    public:
        /** @brief Returns the cached font, loading it on first use. Returns nullptr on failure. */
        TTF_Font* Get(const std::string&, int);
        /** @brief Closes all cached fonts. */
        void Clear();
    private:
        std::unordered_map<std::string, TTF_Font*> cache;
    };
}

#endif