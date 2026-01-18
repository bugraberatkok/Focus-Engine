#pragma once
#include "UISceneBase.h"

class AppleCollectorGame;

class AppleGameOverScene : public UISceneBase
{
private:
    AppleCollectorGame* game;
    int screenW, screenH;

public:
    AppleGameOverScene(int w, int h, AppleCollectorGame* gameRef);

    void OnEnter() override;
    void OnExit() override;
    void Update() override;
    void Render(SDL_Renderer* renderer) override;
    void HandleInput() override;
};