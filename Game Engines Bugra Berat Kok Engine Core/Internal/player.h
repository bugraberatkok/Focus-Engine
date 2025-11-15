#pragma once
#include "BaseObject.h"
#include "InputManager.h"

class Player : public BaseObject
{
public:
    Player(float x, float y, int w, int h);

    void Update() override;
    void Render(SDL_Renderer* renderer) override;

private:
    float speed = 5.0f; // hareket h�z�
};
