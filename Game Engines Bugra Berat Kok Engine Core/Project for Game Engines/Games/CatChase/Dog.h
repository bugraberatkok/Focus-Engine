#pragma once
#include "Character.h"

class Dog : public Character
{
private:
    float targetX, targetY;

public:
    Dog(float x, float y);
    ~Dog();

    void Update() override;
    void Render(SDL_Renderer* renderer) override;

    void SetTarget(float x, float y);
    void Nudge(float dx, float dy);
};