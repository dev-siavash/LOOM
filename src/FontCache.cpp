#include "FontCache.h"

TTF_Font* LOOM::InternalUtilities::FontCache::Get(const std::string& path, int pointSize)
{
    if (cache.contains(path))
        return cache[path];

    auto font = TTF_OpenFont(path.c_str(), pointSize);
    if (font == NULL)
        return nullptr;

    cache.insert({ path, font });
    return font;
}

void LOOM::InternalUtilities::FontCache::Clear()
{
    for (auto& e : cache)
        TTF_CloseFont(e.second);

    cache.clear();
}