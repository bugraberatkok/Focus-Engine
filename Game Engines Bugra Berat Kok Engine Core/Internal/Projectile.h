#pragma once
#include "BaseObject.h"

enum class ProjectileOwner
{
    PLAYER,
    ENEMY,
    NEUTRAL
};

class Projectile : public BaseObject
{
protected:
    float directionX;
    float directionY;
    float projectileSpeed;
    int damage;
    float lifeTime;
    float currentLifeTime;
    bool shouldDestroy;
    ProjectileOwner owner;  // ← YENİ

public:
    Projectile(float x, float y, float dirX, float dirY, float speed = 300.0f);
    virtual ~Projectile();

    void Update() override;
    void Render(SDL_Renderer* renderer) override;

    void SetDamage(int dmg) { damage = dmg; }
    int GetDamage() const { return damage; }

    void SetLifeTime(float time) { lifeTime = time; }

    void SetOwner(ProjectileOwner o) { owner = o; }  // ← YENİ
    ProjectileOwner GetOwner() const { return owner; }  // ← YENİ

    bool ShouldDestroy() const { return shouldDestroy; }
    void MarkForDestroy() { shouldDestroy = true; }

    virtual void OnHit() { MarkForDestroy(); }
};