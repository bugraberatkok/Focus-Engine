#include "SceneManager.h"
#include "CameraManager.h"
#include "BackgroundManager.h"
#include <iostream>

SceneManager::SceneManager()
    : renderer(nullptr),
    currentScene(nullptr),
    nextScene(nullptr),
    isTransitioning(false)
{
}

SceneManager::~SceneManager()
{
    RemoveAllScenes();
}

void SceneManager::AddScene(const std::string& name, Scene* scene)
{
    if (!scene)
    {
        std::cerr << "Cannot add null scene!" << std::endl;
        return;
    }

    auto it = scenes.find(name);
    if (it != scenes.end())
    {
        std::cerr << "Scene already exists: " << name << std::endl;
        return;
    }

    scenes[name] = scene;
    std::cout << "Scene added: " << name << std::endl;
}

void SceneManager::ChangeScene(const std::string& name)
{
    auto it = scenes.find(name);
    if (it == scenes.end())
    {
        std::cerr << "Scene not found: " << name << std::endl;
        return;
    }

    nextScene = it->second;
    isTransitioning = true;
}

void SceneManager::Update()
{
    if (isTransitioning && nextScene)
    {
        if (currentScene)
        {
            currentScene->OnExit();
            currentScene->SetActive(false);
            std::cout << "Exited scene: " << currentScene->GetName() << std::endl;
        }

        currentScene = nextScene;
        currentScene->SetActive(true);

        // ✅ engine map'i yükler (GameSceneBase ise ve spec.enabled true ise)
        LoadTilemapForScene(currentScene);

        currentScene->OnEnter();

        std::cout << "Entered scene: " << currentScene->GetName() << std::endl;

        nextScene = nullptr;
        isTransitioning = false;
    }

    if (currentScene && currentScene->IsActive())
    {
        currentScene->Update();
    }
}

void SceneManager::Render()
{
    if (currentScene && currentScene->IsActive())
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        BackgroundManager::GetInstance().Render();
        if (hasMap)
            activeMap.Render(renderer);

        currentScene->Render(renderer);
    }
}

void SceneManager::HandleInput()
{
    if (currentScene && currentScene->IsActive())
    {
        currentScene->HandleInput();
    }
}

void SceneManager::RemoveScene(const std::string& name)
{
    auto it = scenes.find(name);
    if (it != scenes.end())
    {
        if (currentScene == it->second)
        {
            currentScene->OnExit();
            currentScene = nullptr;
        }

        delete it->second;
        scenes.erase(it);
        std::cout << "Scene removed: " << name << std::endl;
    }
}

void SceneManager::RemoveAllScenes()
{
    if (currentScene)
    {
        currentScene->OnExit();
        currentScene = nullptr;
    }

    for (auto& pair : scenes)
    {
        delete pair.second;
    }
    scenes.clear();

    std::cout << "All scenes removed." << std::endl;
}

void SceneManager::LoadTilemapForScene(Scene* scene)
{
    std::cout << "=== LoadTilemapForScene ===" << std::endl;

    hasMap = false;
    if (!scene || !renderer)
    {
        std::cout << "ERROR: Scene or renderer is NULL" << std::endl;
        return;
    }

    auto* gs = dynamic_cast<GameSceneBase*>(scene);
    if (!gs)
    {
        std::cout << "Not a GameSceneBase, skipping tilemap" << std::endl;
        return;
    }

    const TilemapSpec& spec = gs->GetTilemapSpec();
    std::cout << "Spec enabled: " << spec.enabled << std::endl;
    std::cout << "Spec CSV: " << spec.groundCsvPath << std::endl;

    if (!spec.enabled)
    {
        std::cout << "Tilemap disabled in spec" << std::endl;
        return;
    }

    std::cout << "Loading tilemap..." << std::endl;
    hasMap = activeMap.LoadFromCSV(
        renderer,
        spec.tilesetPath,
        spec.tileSize,
        spec.mapW,
        spec.mapH,
        spec.groundCsvPath
    );

    std::cout << "LoadFromCSV result: " << hasMap << std::endl;

    if (hasMap)
    {
        float mapWidthPixels = (float)activeMap.GetMapWidthPixels();
        float mapHeightPixels = (float)activeMap.GetMapHeightPixels();
        std::cout << "Map loaded! Size: " << mapWidthPixels << "x" << mapHeightPixels << std::endl;

        CameraManager::GetInstance().SetBounds(0, mapWidthPixels, 0, mapHeightPixels);
    }
    else
    {
        std::cout << "ERROR: Failed to load tilemap!" << std::endl;
    }

    std::cout << "===========================" << std::endl;
}

// ==========================================================
// ✅ YENİ (CatChase-safe): elle tilemap yükleme fonksiyonu
// ==========================================================
bool SceneManager::LoadActiveTileMapFromCSV(
    const std::string& tilesetPath,
    int tileSize,
    int mapW,
    int mapH,
    const std::string& groundCSV
)
{
    hasMap = false;
    if (!renderer) return false;

    hasMap = activeMap.LoadFromCSV(
        renderer,
        tilesetPath,
        tileSize,
        mapW,
        mapH,
        groundCSV
    );

    if (hasMap)
    {
        float mapWidthPixels = (float)activeMap.GetMapWidthPixels();
        float mapHeightPixels = (float)activeMap.GetMapHeightPixels();
        CameraManager::GetInstance().SetBounds(0, mapWidthPixels, 0, mapHeightPixels);
    }

    return hasMap;
}
