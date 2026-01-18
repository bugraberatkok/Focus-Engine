#pragma once
#include "Singleton.h"
#include <SDL.h>

class BaseObject;

class PhysicsManager : public Singleton<PhysicsManager>
{
    friend class Singleton<PhysicsManager>;

private:
    PhysicsManager();

    float gravity;           // Yerçekimi kuvveti (piksel/saniye^2)
    bool gravityEnabled;     // Gravity açık mı?

public:
    // Collision
    bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);
    void DetectAllCollisions();

    // Gravity
    void SetGravity(float g) { gravity = g; }
    float GetGravity() const { return gravity; }

    void SetGravityEnabled(bool enabled) { gravityEnabled = enabled; }
    bool IsGravityEnabled() const { return gravityEnabled; }

    // Her frame otomatik çağrılacak
    void ApplyGravity(BaseObject* obj, float deltaTime);
};