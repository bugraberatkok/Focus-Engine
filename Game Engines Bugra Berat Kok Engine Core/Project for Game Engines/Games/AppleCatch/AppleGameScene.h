#pragma once
#include "GameSceneBase.h"

class AppleCollectorGame;

class AppleGameScene : public GameSceneBase
{
private:
    int screenW, screenH;
    AppleCollectorGame* game;
    bool initialized;

public:
    AppleGameScene(int w, int h, AppleCollectorGame* gameRef);

    void OnEnter() override;
    void OnExit() override;
    void Update() override;
    void Render(SDL_Renderer* renderer) override;
    void HandleInput() override;
};