#include <SDL_image.h>

#include "TextureCache.h"

SDL_Texture* LOOM::InternalUtilities::TextureCache::Get(SDL_Renderer* renderer, const std::string& path)
{
    if (cache.contains(path))
        return cache[path];

    auto texture = IMG_LoadTexture(renderer, path.c_str());
    if (texture == NULL)
        return nullptr;

    cache.insert({ path, texture });
    return texture;
}

void LOOM::InternalUtilities::TextureCache::Clear()
{
    for (auto& e : cache)
        SDL_DestroyTexture(e.second);

    cache.clear();
}