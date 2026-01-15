#include "BackgroundManager.h"
#include "SpriteManager.h"
#include <iostream>

BackgroundManager::BackgroundManager()
    : renderer(nullptr),
    currentBackground(nullptr),
    mode(BackgroundMode::STRETCH),
    screenWidth(1920),
    screenHeight(1080)
{
}

BackgroundManager::~BackgroundManager()
{
    UnloadAll();
}

bool BackgroundManager::LoadBackground(const std::string& id, const std::string& filePath)
{
    // Zaten yüklüyse döndür
    auto it = backgrounds.find(id);
    if (it != backgrounds.end())
    {
        std::cout << "Background already loaded: " << id << std::endl;
        return true;
    }

    // SpriteManager'ı kullan (texture yükleme zaten var)
    SDL_Texture* texture = SpriteManager::GetInstance().LoadTexture(id, filePath);

    if (!texture)
    {
        std::cerr << "Failed to load background: " << filePath << std::endl;
        return false;
    }

    backgrounds[id] = texture;
    std::cout << "Background loaded: " << id << std::endl;
    return true;
}

void BackgroundManager::SetActiveBackground(const std::string& id, BackgroundMode bgMode)
{
    auto it = backgrounds.find(id);
    if (it == backgrounds.end())
    {
        std::cerr << "Background not found: " << id << std::endl;
        return;
    }

    currentBackground = it->second;
    currentBackgroundId = id;
    mode = bgMode;

    std::cout << "Active background set: " << id << std::endl;
}

void BackgroundManager::Render()
{
    if (!renderer || !currentBackground)
        return;

    int texWidth, texHeight;
    SDL_QueryTexture(currentBackground, nullptr, nullptr, &texWidth, &texHeight);

    switch (mode)
    {
    case BackgroundMode::STRETCH:
    {
        // Tüm ekranı kapla (uzat)
        SDL_Rect dstRect = { 0, 0, screenWidth, screenHeight };
        SDL_RenderCopy(renderer, currentBackground, nullptr, &dstRect);
        break;
    }

    case BackgroundMode::FIT:
    {
        // Oranı koru, ekrana sığdır
        float scaleX = (float)screenWidth / texWidth;
        float scaleY = (float)screenHeight / texHeight;
        float scale = (scaleX < scaleY) ? scaleX : scaleY;

        int newWidth = (int)(texWidth * scale);
        int newHeight = (int)(texHeight * scale);
        int x = (screenWidth - newWidth) / 2;
        int y = (screenHeight - newHeight) / 2;

        SDL_Rect dstRect = { x, y, newWidth, newHeight };
        SDL_RenderCopy(renderer, currentBackground, nullptr, &dstRect);
        break;
    }

    case BackgroundMode::REPEAT:
    {
        // Tekrarla (tile gibi)
        for (int y = 0; y < screenHeight; y += texHeight)
        {
            for (int x = 0; x < screenWidth; x += texWidth)
            {
                SDL_Rect dstRect = { x, y, texWidth, texHeight };
                SDL_RenderCopy(renderer, currentBackground, nullptr, &dstRect);
            }
        }
        break;
    }

    case BackgroundMode::CENTER:
    {
        // Ortala (küçükse siyah kenarlar kalır)
        int x = (screenWidth - texWidth) / 2;
        int y = (screenHeight - texHeight) / 2;

        SDL_Rect dstRect = { x, y, texWidth, texHeight };
        SDL_RenderCopy(renderer, currentBackground, nullptr, &dstRect);
        break;
    }
    }
}

void BackgroundManager::UnloadBackground(const std::string& id)
{
    auto it = backgrounds.find(id);
    if (it != backgrounds.end())
    {
        // Aktif background siliniyorsa null'la
        if (currentBackgroundId == id)
        {
            currentBackground = nullptr;
            currentBackgroundId = "";
        }

        // SpriteManager texture'ı sildiği için sadece map'ten çıkar
        backgrounds.erase(it);

        std::cout << "Background unloaded: " << id << std::endl;
    }
}

void BackgroundManager::UnloadAll()
{
    backgrounds.clear();
    currentBackground = nullptr;
    currentBackgroundId = "";

    std::cout << "All backgrounds unloaded." << std::endl;
}