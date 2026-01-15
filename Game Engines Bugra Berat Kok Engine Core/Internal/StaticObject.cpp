#include "StaticObject.h"
#include "TimeManager.h"
#include "AnimationManager.h"

StaticObject::StaticObject()
    : BaseObject(),
    hasCollision(false),
    isPickup(false)
{
}

StaticObject::~StaticObject()
{
}

void StaticObject::Update()
{
    // Statik objeler genelde hareket etmez
    // Ama animasyon varsa (ateş, su vs) güncelle
    if (animState)
    {
        float dt = TimeManager::GetInstance().GetDeltaTime();
        AnimationManager::GetInstance().UpdateAnimation(*animState, dt);
    }
}

void StaticObject::Render(SDL_Renderer* renderer)
{
    BaseObject::Render(renderer);
}

