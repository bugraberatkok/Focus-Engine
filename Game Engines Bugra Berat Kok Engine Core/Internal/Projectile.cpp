#include "Projectile.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include <cmath>
#include <iostream>

Projectile::Projectile(float x, float y, float dirX, float dirY, float speed)
    : BaseObject(),
      directionX(dirX),
      directionY(dirY),
      projectileSpeed(speed),
      damage(10),
      lifeTime(5.0f),
      currentLifeTime(0.0f),
      shouldDestroy(false),
      owner(ProjectileOwner::NEUTRAL)  // ← YENİ
{
    SetPosition(x, y);

    // Normalize direction
    float length = std::sqrt(dirX * dirX + dirY * dirY);
    if (length > 0.001f)
    {
        directionX /= length;
        directionY /= length;
    }

    std::cout << "Projectile spawned at (" << x << ", " << y << ")" << std::endl;
}

Projectile::~Projectile()
{
    std::cout << "Projectile destroyed" << std::endl;
}

void Projectile::Update()
{
    BaseObject::Update();

    float dt = TimeManager::GetInstance().GetDeltaTime();

    // Hareket
    posX += directionX * projectileSpeed * dt;
    posY += directionY * projectileSpeed * dt;

    SetPosition(posX, posY);

    // Ömür kontrolü
    currentLifeTime += dt;
    if (currentLifeTime >= lifeTime)
    {
        shouldDestroy = true;
    }
}

void Projectile::Render(SDL_Renderer* renderer)
{
    BaseObject::Render(renderer);
}