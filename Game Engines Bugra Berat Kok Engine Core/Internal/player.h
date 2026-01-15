#pragma once
#include "BaseObject.h"
#include "InputManager.h"

class Player : public BaseObject
{
public:
    Player(float x, float y, float scale = 3.0f);

    void Update() override;
    void Render(SDL_Renderer* renderer) override;

private:
    float speed = 5.0f; // frame başına piksel (TimeManager'a geçersen değiştiririz)
};
