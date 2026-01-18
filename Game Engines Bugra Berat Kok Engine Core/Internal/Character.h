#pragma once
#include "BaseObject.h"
#include "AnimationManager.h"
#include "TimeManager.h"

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
    Animation* idleAnim;
    Animation* walkAnim;
    Animation* attackAnim;
    Animation* deathAnim;

    float speed;
    bool facingRight;
    CharacterState currentState;

    bool isDead;



public:
    Character();
    virtual ~Character();

    virtual void SetIdleAnimation(Animation* anim);
    virtual void SetWalkAnimation(Animation* anim);
    virtual void SetAttackAnimation(Animation* anim);
    virtual void SetDeathAnimation(Animation* anim);

    virtual void PlayIdleAnimation();
    virtual void PlayWalkAnimation();
    virtual void PlayAttackAnimation();
    virtual void PlayDeathAnimation();

    void SetFacingRight(bool right);
    bool IsFacingRight() const { return facingRight; }

    CharacterState GetState() const { return currentState; }


    void SetSpeed(float s) { speed = s; }
    float GetSpeed() const { return speed; }



    void Update() override;
    void Render(SDL_Renderer* renderer) override;


};