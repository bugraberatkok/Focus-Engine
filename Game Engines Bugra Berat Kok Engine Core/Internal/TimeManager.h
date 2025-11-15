#pragma once
#include "Singleton.h"
#include "SDL.h"

class TimeManager : public Singleton<TimeManager>
{
    friend class Singleton<TimeManager>;

private:
    Uint32 lastTick;
    float deltaTime;

    TimeManager() : lastTick(0), deltaTime(0.0f) {}

public:
    void Update()
    {
        Uint32 currentTick = SDL_GetTicks();
        deltaTime = (currentTick - lastTick) / 1000.0f; //ms
        lastTick = currentTick;
    }

    float GetDeltaTime() const { return deltaTime; }
};
