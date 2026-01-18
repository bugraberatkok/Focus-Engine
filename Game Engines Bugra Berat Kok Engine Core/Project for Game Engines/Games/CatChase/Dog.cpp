#include "Dog.h"
#include "AnimationManager.h"
#include "TimeManager.h"
#include <cmath>
#include <iostream>

Dog::Dog(float x, float y)
    : Character(),
    targetX(x),
    targetY(y)
{
    SetPosition(x, y);
    SetSpeed(120.0f);
    SetScale(2.5f);

    walkAnim = AnimationManager::GetInstance().GetAnimation("dog_walk");
    idleAnim = AnimationManager::GetInstance().GetAnimation("dog_idle");

    if (idleAnim)
    {
        SetAnimation(idleAnim);
        currentState = CharacterState::IDLE;
    }

    SetCollisionRect(56, 48);
    SetCollisionOffset(25, 65);

    std::cout << "Dog spawned at (" << x << ", " << y << ")" << std::endl;
}

Dog::~Dog()
{
    std::cout << "Dog destroyed" << std::endl;
}

void Dog::Update()
{
    Character::Update();

    float dt = TimeManager::GetInstance().GetDeltaTime();

    // DOĞRU MERKEZ HESAPLAMA (rect zaten offsetli)
    float dogCx = rect.x + rect.w * 0.5f;
    float dogCy = rect.y + rect.h * 0.5f;

    float dx = targetX - dogCx;
    float dy = targetY - dogCy;
    float distance = std::sqrt(dx * dx + dy * dy);

    const float arriveRadius = 10.0f;  // Daha küçük yap

    if (distance > arriveRadius)
    {
        dx /= distance;
        dy /= distance;

        posX += dx * speed * dt;
        posY += dy * speed * dt;

        if (dx < 0) SetFacingRight(false);
        else        SetFacingRight(true);

        if (walkAnim && currentState != CharacterState::WALKING)
            PlayWalkAnimation();
    }
    else
    {
        if (idleAnim && currentState != CharacterState::IDLE)
            PlayIdleAnimation();
    }

    SetPosition(posX, posY);
}

void Dog::Render(SDL_Renderer* renderer)
{
    Character::Render(renderer);

}

void Dog::SetTarget(float x, float y)
{
    targetX = x;
    targetY = y;
}

void Dog::Nudge(float dx, float dy)
{
    posX += dx;
    posY += dy;
}