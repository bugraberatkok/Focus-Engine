#pragma once
#include "BaseObject.h"
#include "AnimationManager.h"
#include "TimeManager.h"

// Karakter durumları
enum class CharacterState
{
    IDLE,
    WALKING,
    ATTACKING,
    DEAD
};

class Character : public BaseObject
{
protected:
    // Animasyon state'leri
    Animation* idleAnim;
    Animation* walkAnim;
    Animation* attackAnim;
    Animation* deathAnim;

    // Karakter özellikleri
    float speed;
    bool facingRight;
    CharacterState currentState;

    // Sağlık sistemi (opsiyonel kullanım)
    int health;
    int maxHealth;
    bool isDead;

    // Animasyon helper
    void UpdateAnimationState();

public:
    Character();
    virtual ~Character();

    // Animasyon yönetimi
    virtual void SetIdleAnimation(Animation* anim);
    virtual void SetWalkAnimation(Animation* anim);
    virtual void SetAttackAnimation(Animation* anim);
    virtual void SetDeathAnimation(Animation* anim);

    virtual void PlayIdleAnimation();
    virtual void PlayWalkAnimation();
    virtual void PlayAttackAnimation();
    virtual void PlayDeathAnimation();

    // Yön kontrolü
    void SetFacingRight(bool right);
    bool IsFacingRight() const { return facingRight; }

    // Durum kontrolü
    CharacterState GetState() const { return currentState; }
    void SetState(CharacterState state);

    // Hareket
    void SetSpeed(float s) { speed = s; }
    float GetSpeed() const { return speed; }

    // Sağlık (child'lar kullanabilir)
    virtual void TakeDamage(int amount);
    virtual void Heal(int amount);
    virtual void Die();
    bool IsDead() const { return isDead; }
    int GetHealth() const { return health; }
    int GetMaxHealth() const { return maxHealth; }
    void SetHealth(int h) { health = h; }
    void SetMaxHealth(int h) { maxHealth = h; health = h; }

    // Her frame çağrılır
    void Update() override;
    void Render(SDL_Renderer* renderer) override;

    // Child'lar override edebilir
    virtual void OnDeath() {}
    virtual void OnTakeDamage(int amount) {}
};