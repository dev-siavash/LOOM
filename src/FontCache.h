#ifndef FONT_CACHE_H
#define FONT_CACHE_H

#include <string>
#include <unordered_map>
#include <SDL_ttf.h>

namespace LOOM::InternalUtilities
{
    class FontCache
    {
    public:
        TTF_Font* Get(const std::string&, int);
        void Clear();
    private:
        std::unordered_map<std::string, TTF_Font*> cache;
    };
}

#endif