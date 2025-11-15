#pragma once
#include "BaseObject.h"
#include "TimeManager.h"
#include <SDL.h>
#include <cstdlib> // rand()

class Obstacle : public BaseObject
{
public:
    Obstacle(float x, float y, int w, int h);

    void Update() override;
    void Render(SDL_Renderer* renderer) override;

private:
    float speed = 100.0f;        // h�z
    int direction = 1;           // 1 = sa�, -1 = sol
    float moveDuration = 0.5f;   // hareket s�resi (saniye)
    float elapsedTime = 0.0f;    // ge�en s�re
    float waitTime = 0.0f;       // bekleme s�resi
    bool isMoving = false;       // �u anda hareket ediyor mu?

    void ChooseNewWaitTime();
    void ChooseNewDirection();
};
