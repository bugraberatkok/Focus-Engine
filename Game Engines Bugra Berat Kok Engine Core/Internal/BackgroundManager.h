#pragma once
#include "Singleton.h"
#include <SDL.h>
#include <string>
#include <map>

enum class BackgroundMode
{
    STRETCH,    // Ekrana sığdır (uzat)
    FIT,        // Oranı koru, sığdır
    REPEAT,     // Tekrarla (tile gibi ama basit)
    CENTER      // Ortala
};

class BackgroundManager : public Singleton<BackgroundManager>
{
    friend class Singleton<BackgroundManager>;

private:
    BackgroundManager();
    ~BackgroundManager();

    SDL_Renderer* renderer;

    // Background'ları sakla
    std::map<std::string, SDL_Texture*> backgrounds;

    // Aktif background
    SDL_Texture* currentBackground;
    std::string currentBackgroundId;
    BackgroundMode mode;

    int screenWidth;
    int screenHeight;

public:
    void SetRenderer(SDL_Renderer* r) { renderer = r; }
    void SetScreenSize(int w, int h) { screenWidth = w; screenHeight = h; }

    // Background yükle
    bool LoadBackground(const std::string& id, const std::string& filePath);

    // Aktif background'u değiştir
    void SetActiveBackground(const std::string& id, BackgroundMode mode = BackgroundMode::STRETCH);

    // Render et
    void Render();

    // Temizlik
    void UnloadBackground(const std::string& id);
    void UnloadAll();
};