#pragma once
#include "Singleton.h"
#include <SDL.h>

class PhysicsManager : public Singleton<PhysicsManager>
{
    friend class Singleton<PhysicsManager>;

private:
    PhysicsManager() {}

    

public:
    // Sadece 2 adet SDL_Rect arasında AABB collision kontrolü yapar
    bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);

    void DetectAllCollisions();

};
