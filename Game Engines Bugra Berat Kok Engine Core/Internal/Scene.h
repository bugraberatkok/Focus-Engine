#pragma once
#include <SDL.h>
#include <string>

// Her scene bu base class'tan türer
class Scene
{
protected:
    std::string sceneName;
    bool isActive;

public:
    Scene(const std::string& name)
        : sceneName(name), isActive(false) {
    }

    virtual ~Scene() {}

    // Her scene bunları implement etmeli
    virtual void OnEnter() = 0;   // Scene'e girildiğinde çağrılır
    virtual void OnExit() = 0;    // Scene'den çıkıldığında çağrılır
    virtual void Update() = 0;    // Her frame
    virtual void Render(SDL_Renderer* renderer) = 0;  // Render
    virtual void HandleInput() = 0;  // Input handling

    // Getters
    const std::string& GetName() const { return sceneName; }
    bool IsActive() const { return isActive; }

    void SetActive(bool active) { isActive = active; }
};