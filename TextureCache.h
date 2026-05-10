#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include <string>
#include <unordered_map>
#include <SDL.h>

namespace LOOM::InternalUtilities
{
    class TextureCache
    {
    public:
        SDL_Texture* Get(SDL_Renderer*, const std::string&);
        void Clear();
    private:
        std::unordered_map<std::string, SDL_Texture*> cache;
    };
}

#endif
