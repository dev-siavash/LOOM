/**
 * @file TextCache.h
 * @brief Rendered text cache.
 */
#ifndef TEXT_CACHE_H
#define TEXT_CACHE_H

#include <unordered_map>
#include <SDL.h>

namespace LOOM::InternalUtilities
{
    /** @brief (Internal) Stores rendered text textures by hash key. */
    class TextCache
    {
    public:
        /** @brief Returns the texture for @p key, or nullptr. */
        SDL_Texture* Get(std::size_t);
        /** @brief Stores a texture under a key. */
        void Store(std::size_t, SDL_Texture*);
        /** @brief Returns true if a texture exists for the key. */
        bool Has(std::size_t);
        /** @brief Removes the texture for the key. */
        void Remove(std::size_t);
        /** @brief Removes all textures. */
        void Clear();
    private:
        std::unordered_map<std::size_t, SDL_Texture*> cache;
    };
}

#endif
