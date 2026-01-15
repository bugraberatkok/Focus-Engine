#pragma once
#include "Singleton.h"
#include <SDL.h>
#include <string>
#include <map>

class SpriteManager : public Singleton<SpriteManager>
{
    friend class Singleton<SpriteManager>;

private:
    SpriteManager() : renderer(nullptr) {}
    ~SpriteManager();

    SDL_Renderer* renderer;
    std::map<std::string, SDL_Texture*> textures;

public:
    // Önce main'de set edeceğiz
    void SetRenderer(SDL_Renderer* r) { renderer = r; }

    // id: "player_idle", "enemy_red" gibi
    // filePath: "Media/player_idle.png" gibi
    SDL_Texture* LoadTexture(const std::string& id, const std::string& filePath);

    SDL_Texture* GetTexture(const std::string& id) const;
    void UnloadTexture(const std::string& id);
    void UnloadAll();
};
