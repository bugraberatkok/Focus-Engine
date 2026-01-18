#pragma once
#include "Singleton.h"
#include "Scene.h"
#include <SDL.h>
#include <map>
#include <string>
#include "Tilemap.h"
#include "GameSceneBase.h"

class SceneManager : public Singleton<SceneManager>
{
    friend class Singleton<SceneManager>;

private:
    SceneManager();
    ~SceneManager();

    SDL_Renderer* renderer;
    std::map<std::string, Scene*> scenes;
    Scene* currentScene;
    Scene* nextScene;
    bool isTransitioning;

    TileMap activeMap;
    bool hasMap = false;

    void LoadTilemapForScene(Scene* scene);

public:
    TileMap* GetActiveMap()
    {
        return hasMap ? &activeMap : nullptr;
    }

    void SetRenderer(SDL_Renderer* r) { renderer = r; }
    void AddScene(const std::string& name, Scene* scene);
    void ChangeScene(const std::string& name);
    Scene* GetCurrentScene() const { return currentScene; }
    void Update();
    void Render();
    void HandleInput();
    void RemoveScene(const std::string& name);
    void RemoveAllScenes();

    // ==========================================================
    // ✅ YENİ (CatChase-safe): İstersen elle tilemap yükle
    // ==========================================================
    bool LoadActiveTileMapFromCSV(
        const std::string& tilesetPath,
        int tileSize,
        int mapW,
        int mapH,
        const std::string& groundCSV
    );

    void ClearActiveMap() { hasMap = false; }
};
