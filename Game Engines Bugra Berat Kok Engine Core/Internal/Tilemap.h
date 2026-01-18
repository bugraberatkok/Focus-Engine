#pragma once
#include <vector>
#include <string>
#include <SDL.h>

class TileMap
{
public:
    bool LoadFromCSV(
        SDL_Renderer* renderer,
        const std::string& tilesetPath,
        int tileSize,
        int mapWidth,
        int mapHeight,
        const std::string& groundCSV
    );

    void Render(SDL_Renderer* renderer);

    // ← YENİ: Platform Collision
    bool IsSolid(int tileX, int tileY) const;           // O tile solid mi?
    int GetTileAt(int tileX, int tileY) const;          // Hangi tile var?
    bool IsSolidPixel(float pixelX, float pixelY) const; // Piksel koordinatından tile'a çevir

    // Map bilgileri
    int GetTileSize() const { return tileSize; }
    int GetMapWidth() const { return mapW; }
    int GetMapHeight() const { return mapH; }
    int GetMapWidthPixels() const { return mapW * tileSize; }
    int GetMapHeightPixels() const { return mapH * tileSize; }

private:
    bool LoadCSV(const std::string& path, std::vector<int>& out);

    SDL_Texture* tileset = nullptr;
    int tileSize = 16;
    int mapW = 0, mapH = 0;
    int tilesetCols = 0;

    std::vector<int> ground;
};