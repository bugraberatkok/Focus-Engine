#include "Character.h"
#include "PhysicsManager.h"
#include "SceneManager.h"
#include <iostream>

Character::Character()
    : BaseObject(),
    idleAnim(nullptr),
    walkAnim(nullptr),
    attackAnim(nullptr),
    deathAnim(nullptr),
    speed(100.0f),
    facingRight(true),
    currentState(CharacterState::IDLE),
    isDead(false)
{

}

Character::~Character()
{
    // Animasyonlar AnimationManager'da saklanıyor
}

void Character::SetIdleAnimation(Animation* anim)
{
    idleAnim = anim;
}

void Character::SetWalkAnimation(Animation* anim)
{
    walkAnim = anim;
}

void Character::SetAttackAnimation(Animation* anim)
{
    attackAnim = anim;
}

void Character::SetDeathAnimation(Animation* anim)
{
    deathAnim = anim;
}


void Character::PlayIdleAnimation()
{
    if (idleAnim && currentState != CharacterState::DEAD)
    {
        SetAnimation(idleAnim);
        currentState = CharacterState::IDLE;
    }
}

void Character::PlayWalkAnimation()
{
    if (walkAnim && currentState != CharacterState::DEAD)
    {
        SetAnimation(walkAnim);
        currentState = CharacterState::WALKING;
    }
}

void Character::PlayAttackAnimation()
{
    if (attackAnim && currentState != CharacterState::DEAD)
    {
        SetAnimation(attackAnim);
        currentState = CharacterState::ATTACKING;
    }
}

void Character::PlayDeathAnimation()
{
    if (deathAnim)
    {
        SetAnimation(deathAnim);
        currentState = CharacterState::DEAD;
        isDead = true;
    }
}


void Character::SetFacingRight(bool right)
{
    facingRight = right;

    if (facingRight)
        SetFlip(SDL_FLIP_NONE);
    else
        SetFlip(SDL_FLIP_HORIZONTAL);
}



// Character.cpp - TAM DÜZELTME

void Character::Update()
{
    if (animState)
    {
        float dt = TimeManager::GetInstance().GetDeltaTime();
        AnimationManager::GetInstance().UpdateAnimation(*animState, dt);
    }

    
}

void Character::Render(SDL_Renderer* renderer)
{
    BaseObject::Render(renderer);
}