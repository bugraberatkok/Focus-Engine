#include "Mouse.h"
#include "AnimationManager.h"
#include "TimeManager.h"
#include <cmath>
#include <iostream>

Mouse::Mouse(float x, float y, float dirX, float dirY)
    : Character(),
    shouldDelete(false)
{
    SetPosition(x, y);
    SetSpeed(150.0f);
    SetScale(1.5f);

    float length = std::sqrt(dirX * dirX + dirY * dirY);
    if (length > 0.001f)
    {
        this->dirX = dirX / length;
        this->dirY = dirY / length;
    }
    else
    {
        this->dirX = 1.0f;
        this->dirY = 0.0f;
    }

    if (this->dirX < 0)
        SetFacingRight(false);
    else
        SetFacingRight(true);

    walkAnim = AnimationManager::GetInstance().GetAnimation("mouse_walk");
    deathAnim = AnimationManager::GetInstance().GetAnimation("mouse_death");

    if (walkAnim)
        SetAnimation(walkAnim);

    SetCollisionRect(20, 20);
    SetCollisionOffset(10, 30);

    std::cout << "Mouse spawned at (" << x << ", " << y
        << ") direction: (" << this->dirX << ", " << this->dirY << ")" << std::endl;
}

Mouse::~Mouse()
{
    std::cout << "Mouse destroyed" << std::endl;
}

void Mouse::Update()
{
    if (isDead)
        return;

    Character::Update();

    float dt = TimeManager::GetInstance().GetDeltaTime();

    posX += dirX * speed * dt;
    posY += dirY * speed * dt;

    SetPosition(posX, posY);
}

void Mouse::Render(SDL_Renderer* renderer)
{
    Character::Render(renderer);


}

bool Mouse::IsOutOfBounds(int screenWidth, int screenHeight) const
{
    return (posX < -100 || posX > screenWidth + 100 ||
        posY < -100 || posY > screenHeight + 100);
}