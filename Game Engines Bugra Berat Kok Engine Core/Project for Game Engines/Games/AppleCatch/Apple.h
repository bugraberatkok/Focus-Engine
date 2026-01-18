#pragma once
#include "StaticObject.h"

enum class AppleColor
{
    RED,
    GREEN,
    YELLOW,
    BLUE
};

class Apple : public StaticObject
{
private:
    AppleColor color;
    bool collected;
    float lifeTimer;          // Kaç saniyedir var
    float maxLifeTime;        // 4-5 saniye sonra yok olacak

public:
    Apple(float x, float y, AppleColor appleColor);
    ~Apple();

    void Update() override;
    void Render(SDL_Renderer* renderer) override;

    AppleColor GetColor() const { return color; }
    bool IsCollected() const { return collected; }
    bool ShouldDespawn() const { return lifeTimer >= maxLifeTime; }

    void Collect() { collected = true; }
};