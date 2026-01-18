#include "Cat.h"
#include "AnimationManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include <iostream>

Cat::Cat(float x, float y)
    : Character(),
    isCatching(false),
    score(0)
{
    SetPosition(x, y);
    SetSpeed(200.0f);
    SetScale(2.0f);

    idleAnim = AnimationManager::GetInstance().GetAnimation("cat_idle");
    walkAnim = AnimationManager::GetInstance().GetAnimation("cat_walk");
    attackAnim = AnimationManager::GetInstance().GetAnimation("cat_attack");

    if (idleAnim)
    {
        SetAnimation(idleAnim);
        currentState = CharacterState::IDLE;
    }

    SetCollisionRect(60, 40);
    SetCollisionOffset(-5, 25);

    std::cout << "Cat created at (" << x << ", " << y << ")" << std::endl;
}

Cat::~Cat()
{
    std::cout << "Cat destroyed. Final score: " << score << std::endl;
}

void Cat::Update()
{
    Character::Update();

    float dt = TimeManager::GetInstance().GetDeltaTime();
    InputManager& input = InputManager::GetInstance();

    bool moving = false;

    if (input.GetKey(SDL_SCANCODE_UP))
    {
        posY -= speed * dt;
        moving = true;
    }
    if (input.GetKey(SDL_SCANCODE_DOWN))
    {
        posY += speed * dt;
        moving = true;
    }
    if (input.GetKey(SDL_SCANCODE_LEFT))
    {
        posX -= speed * dt;
        SetFacingRight(false);
        SetCollisionOffset(10, 55);
        moving = true;
    }
    if (input.GetKey(SDL_SCANCODE_RIGHT))
    {
        posX += speed * dt;
        SetFacingRight(true);
        SetCollisionOffset(20, 55);
        moving = true;
    }

    isCatching = input.GetKey(SDL_SCANCODE_SPACE);

    if (isCatching && attackAnim)
    {
        if (currentState != CharacterState::ATTACKING)
            PlayAttackAnimation();
    }
    else if (moving && walkAnim)
    {
        if (currentState != CharacterState::WALKING)
            PlayWalkAnimation();
    }
    else if (!moving && idleAnim)
    {
        if (currentState != CharacterState::IDLE)
            PlayIdleAnimation();
    }

    SetPosition(posX, posY);
}

void Cat::Render(SDL_Renderer* renderer)
{
    Character::Render(renderer);


   
}