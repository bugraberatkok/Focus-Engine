#include "SceneManager.h"
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

    // Zaten varsa uyar
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
    // Scene geçişi varsa yap
    if (isTransitioning && nextScene)
    {
        // Eski scene'den çık
        if (currentScene)
        {
            currentScene->OnExit();
            currentScene->SetActive(false);
            std::cout << "Exited scene: " << currentScene->GetName() << std::endl;
        }

        // Yeni scene'e gir
        currentScene = nextScene;
        currentScene->SetActive(true);
        currentScene->OnEnter();
        std::cout << "Entered scene: " << currentScene->GetName() << std::endl;

        nextScene = nullptr;
        isTransitioning = false;
    }

    // Aktif scene'i güncelle
    if (currentScene && currentScene->IsActive())
    {
        currentScene->Update();
    }
}

void SceneManager::Render()
{
    if (currentScene && currentScene->IsActive())
    {
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
        // Eğer bu scene aktifse önce başka scene'e geç
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
    // Önce aktif scene'den çık
    if (currentScene)
    {
        currentScene->OnExit();
        currentScene = nullptr;
    }

    // Tüm scene'leri sil
    for (auto& pair : scenes)
    {
        delete pair.second;
    }
    scenes.clear();

    std::cout << "All scenes removed." << std::endl;
}