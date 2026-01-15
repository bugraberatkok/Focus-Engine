#pragma once
#include "Singleton.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <map>

class TextManager : public Singleton<TextManager>
{
    friend class Singleton<TextManager>;

private:
    TextManager();
    ~TextManager();

    SDL_Renderer* renderer;

    // Font'ları sakla (farklı boyutlar için)
    std::map<std::string, TTF_Font*> fonts;

    // Cache için (aynı text'i tekrar render etmemek için)
    struct CachedText
    {
        SDL_Texture* texture;
        int width;
        int height;
        std::string text;
        SDL_Color color;
    };

    std::map<std::string, CachedText> textCache;

public:
    // SDL_ttf'i başlat
    bool Init();

    void SetRenderer(SDL_Renderer* r) { renderer = r; }

    // Font yükle
    // id: "arial_24", "comic_32" gibi
    // filePath: "Media/Fonts/arial.ttf"
    // size: 24, 32, 48 gibi
    bool LoadFont(const std::string& id, const std::string& filePath, int size);

    TTF_Font* GetFont(const std::string& id) const;

    // Text render et (basit)
    void RenderText(
        const std::string& text,
        const std::string& fontId,
        int x, int y,
        SDL_Color color = { 255, 255, 255, 255 }
    );

    // Text render et (cache ile - performans için)
    void RenderTextCached(
        const std::string& cacheId,
        const std::string& text,
        const std::string& fontId,
        int x, int y,
        SDL_Color color = { 255, 255, 255, 255 }
    );

    // Text boyutunu hesapla (kullanışlı, center align için)
    void GetTextSize(
        const std::string& text,
        const std::string& fontId,
        int& width, int& height
    );

    // Cache'i temizle
    void ClearCache();

    // Temizlik
    void UnloadFont(const std::string& id);
    void UnloadAll();
};