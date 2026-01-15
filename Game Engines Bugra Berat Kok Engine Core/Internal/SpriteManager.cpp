#include "SpriteManager.h"
#include <SDL_image.h>
#include <iostream>

SpriteManager::~SpriteManager()
{
    UnloadAll();
}

SDL_Texture* SpriteManager::LoadTexture(const std::string& id, const std::string& filePath)
{
    if (!renderer)
    {
        std::cerr << "SpriteManager: Renderer set edilmemiş!\n";
        return nullptr;
    }

    // Eğer zaten yüklüyse direkt onu döndür
    auto it = textures.find(id);
    if (it != textures.end())
        return it->second;

    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface)
    {
        std::cerr << "IMG_Load error: " << IMG_GetError() << " (" << filePath << ")\n";
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
        std::cerr << "SDL_CreateTextureFromSurface error: " << SDL_GetError() << "\n";
        return nullptr;
    }

    textures[id] = texture;
    return texture;
}

SDL_Texture* SpriteManager::GetTexture(const std::string& id) const
{
    auto it = textures.find(id);
    if (it != textures.end())
        return it->second;

    return nullptr;
}

void SpriteManager::UnloadTexture(const std::string& id)
{
    auto it = textures.find(id);
    if (it != textures.end())
    {
        SDL_DestroyTexture(it->second);
        textures.erase(it);
    }
}

void SpriteManager::UnloadAll()
{
    for (auto& pair : textures)
    {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();
}
