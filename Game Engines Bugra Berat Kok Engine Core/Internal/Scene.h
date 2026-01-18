#pragma once
#include <SDL.h>
#include <string>

class Scene
{
protected:
    std::string sceneName;
    bool isActive;

public:
    explicit Scene(const std::string& name)
        : sceneName(name), isActive(false) {
    }

    virtual ~Scene() {}

    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    virtual void Update() = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;
    virtual void HandleInput() = 0;

    const std::string& GetName() const { return sceneName; }
    bool IsActive() const { return isActive; }
    void SetActive(bool active) { isActive = active; }
};
