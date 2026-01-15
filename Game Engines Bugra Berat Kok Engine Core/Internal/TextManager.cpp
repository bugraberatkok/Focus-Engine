#include "TextManager.h"
#include <iostream>

TextManager::TextManager()
    : renderer(nullptr)
{
}

TextManager::~TextManager()
{
    ClearCache();
    UnloadAll();
    TTF_Quit();
}

bool TextManager::Init()
{
    if (TTF_Init() == -1)
    {
        std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
        return false;
    }

    std::cout << "TextManager initialized successfully!" << std::endl;
    return true;
}

bool TextManager::LoadFont(const std::string& id, const std::string& filePath, int size)
{
    // Zaten yüklüyse döndür
    auto it = fonts.find(id);
    if (it != fonts.end())
    {
        std::cout << "Font already loaded: " << id << std::endl;
        return true;
    }

    TTF_Font* font = TTF_OpenFont(filePath.c_str(), size);

    if (!font)
    {
        std::cerr << "Failed to load font: " << filePath
            << " | Error: " << TTF_GetError() << std::endl;
        return false;
    }

    fonts[id] = font;
    std::cout << "Font loaded: " << id << " (size: " << size << ")" << std::endl;
    return true;
}

TTF_Font* TextManager::GetFont(const std::string& id) const
{
    auto it = fonts.find(id);
    if (it != fonts.end())
        return it->second;

    std::cerr << "Font not found: " << id << std::endl;
    return nullptr;
}

void TextManager::RenderText(
    const std::string& text,
    const std::string& fontId,
    int x, int y,
    SDL_Color color)
{
    if (!renderer)
    {
        std::cerr << "TextManager: Renderer not set!" << std::endl;
        return;
    }

    TTF_Font* font = GetFont(fontId);
    if (!font)
        return;

    // Text'i surface olarak render et
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!surface)
    {
        std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        return;
    }

    // Surface'i texture'a çevir
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!texture)
    {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    // Render et
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = surface->w;
    dstRect.h = surface->h;

    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

    // Temizlik
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void TextManager::RenderTextCached(
    const std::string& cacheId,
    const std::string& text,
    const std::string& fontId,
    int x, int y,
    SDL_Color color)
{
    if (!renderer)
        return;

    // Cache'de var mı kontrol et
    auto it = textCache.find(cacheId);

    // Cache'de yoksa veya text değişmişse yeniden oluştur
    if (it == textCache.end() ||
        it->second.text != text ||
        it->second.color.r != color.r ||
        it->second.color.g != color.g ||
        it->second.color.b != color.b)
    {
        // Eski cache'i temizle
        if (it != textCache.end() && it->second.texture)
        {
            SDL_DestroyTexture(it->second.texture);
        }

        TTF_Font* font = GetFont(fontId);
        if (!font)
            return;

        SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
        if (!surface)
            return;

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        if (texture)
        {
            CachedText cached;
            cached.texture = texture;
            cached.width = surface->w;
            cached.height = surface->h;
            cached.text = text;
            cached.color = color;

            textCache[cacheId] = cached;
        }

        SDL_FreeSurface(surface);
    }

    // Cache'den render et
    it = textCache.find(cacheId);
    if (it != textCache.end() && it->second.texture)
    {
        SDL_Rect dstRect;
        dstRect.x = x;
        dstRect.y = y;
        dstRect.w = it->second.width;
        dstRect.h = it->second.height;

        SDL_RenderCopy(renderer, it->second.texture, nullptr, &dstRect);
    }
}

void TextManager::GetTextSize(
    const std::string& text,
    const std::string& fontId,
    int& width, int& height)
{
    TTF_Font* font = GetFont(fontId);
    if (!font)
    {
        width = height = 0;
        return;
    }

    TTF_SizeText(font, text.c_str(), &width, &height);
}

void TextManager::ClearCache()
{
    for (auto& pair : textCache)
    {
        if (pair.second.texture)
        {
            SDL_DestroyTexture(pair.second.texture);
        }
    }
    textCache.clear();
}

void TextManager::UnloadFont(const std::string& id)
{
    auto it = fonts.find(id);
    if (it != fonts.end())
    {
        TTF_CloseFont(it->second);
        fonts.erase(it);
    }
}

void TextManager::UnloadAll()
{
    for (auto& pair : fonts)
    {
        TTF_CloseFont(pair.second);
    }
    fonts.clear();

    std::cout << "All fonts unloaded." << std::endl;
}