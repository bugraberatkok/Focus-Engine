#include "Character.h"
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
    health(100),
    maxHealth(100),
    isDead(false)
{
}

Character::~Character()
{
    // Animasyonlar AnimationManager'da saklanıyor, silmeye gerek yok
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

    // Flip'i güncelle
    if (facingRight)
        SetFlip(SDL_FLIP_NONE);
    else
        SetFlip(SDL_FLIP_HORIZONTAL);
}

void Character::SetState(CharacterState state)
{
    if (currentState == state)
        return;

    currentState = state;

    // Duruma göre animasyon değiştir
    switch (state)
    {
    case CharacterState::IDLE:
        PlayIdleAnimation();
        break;
    case CharacterState::WALKING:
        PlayWalkAnimation();
        break;
    case CharacterState::ATTACKING:
        PlayAttackAnimation();
        break;
    case CharacterState::DEAD:
        PlayDeathAnimation();
        break;
    }
}

void Character::TakeDamage(int amount)
{
    if (isDead)
        return;

    health -= amount;
    if (health < 0)
        health = 0;

    std::cout << "Character took " << amount << " damage. Health: " << health << std::endl;

    OnTakeDamage(amount);

    if (health <= 0)
    {
        Die();
    }
}

void Character::Heal(int amount)
{
    if (isDead)
        return;

    health += amount;
    if (health > maxHealth)
        health = maxHealth;

    std::cout << "Character healed " << amount << ". Health: " << health << std::endl;
}

void Character::Die()
{
    if (isDead)
        return;

    isDead = true;
    PlayDeathAnimation();

    std::cout << "Character died!" << std::endl;

    OnDeath();
}

void Character::Update()
{
    // Animasyonu güncelle
    if (animState)
    {
        float dt = TimeManager::GetInstance().GetDeltaTime();
        AnimationManager::GetInstance().UpdateAnimation(*animState, dt);
    }

    // Child'lar kendi Update'lerini override edebilir
}

void Character::Render(SDL_Renderer* renderer)
{
    // BaseObject'in Render'ını çağır (animasyon çizer)
    BaseObject::Render(renderer);
}