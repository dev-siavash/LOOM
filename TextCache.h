#ifndef TEXT_CACHE_H
#define TEXT_CACHE_H

#include <unordered_map>
#include <SDL.h>

namespace LOOM::InternalUtilities
{
    class TextCache
    {
    public:
        SDL_Texture* Get(std::size_t);
        void Store(std::size_t, SDL_Texture*);
        void Remove(std::size_t);
        void Clear();
    private:
        std::unordered_map<std::size_t, SDL_Texture*> cache;
    };
}

#endif
