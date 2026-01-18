#pragma once
#include "Singleton.h"
#include "SDL.h"
#include <vector>

class InputManager : public Singleton<InputManager>
{
    friend class Singleton<InputManager>;

private:
    const Uint8* mCurrentKeyStates;
    std::vector<SDL_Event> mFrameEvents;

    InputManager() : mCurrentKeyStates(nullptr) {}

    ~InputManager()  // ← EKLE
    {
        mFrameEvents.clear();
    }

public:
    void Update(void);
    bool GetKey(int scanCode);

    void PushEvent(const SDL_Event& e) { mFrameEvents.push_back(e); }
    const std::vector<SDL_Event>& GetFrameEvents() const { return mFrameEvents; }
    void ClearFrameEvents() { mFrameEvents.clear(); }
};