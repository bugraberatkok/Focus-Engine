#pragma once
#include "UISceneBase.h"

class StartScene : public UISceneBase
{
public:
    StartScene();

    void OnEnter() override;
    void OnExit() override;
    void Update() override;
    void Render(SDL_Renderer* renderer) override;
    void HandleInput() override;
};
