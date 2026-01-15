#pragma once
#include "Singleton.h"
#include "Scene.h"
#include <SDL.h>
#include <map>
#include <string>

class SceneManager : public Singleton<SceneManager>
{
    friend class Singleton<SceneManager>;

private:
    SceneManager();
    ~SceneManager();

    SDL_Renderer* renderer;

    // Tüm scene'leri sakla
    std::map<std::string, Scene*> scenes;

    // Aktif scene
    Scene* currentScene;
    Scene* nextScene;  // Scene geçişi için

    bool isTransitioning;

public:
    void SetRenderer(SDL_Renderer* r) { renderer = r; }

    // Scene ekle
    void AddScene(const std::string& name, Scene* scene);

    // Scene'e geç
    void ChangeScene(const std::string& name);

    // Şu anki scene'i al
    Scene* GetCurrentScene() const { return currentScene; }

    // Update ve Render
    void Update();
    void Render();
    void HandleInput();

    // Temizlik
    void RemoveScene(const std::string& name);
    void RemoveAllScenes();
};